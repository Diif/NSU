#include <mpi.h>
#include <string.h>

#include <iostream>

#define MATRIX_DATA_POINTER double*
#define MATRIX_DATA double
#define MPI_MATRIX_DATA MPI_DOUBLE

#define N1 13824
#define N2 6912
#define N3 4608
// #define N1 1200
// #define N2 1200
// #define N3 1800

struct Matrix {
  MATRIX_DATA_POINTER matrix = NULL;
  int rows = 0;
  int columns = 0;
};

Matrix CreateZeroMatrix(int rows, int columns);
Matrix CreateUnfilledMatrix(int rows, int columns);
void FormZeroMatrix(Matrix& mat);
void MultMatrixOnMatrix(Matrix& matrix_for_result, Matrix& matrix_to_mult,
                        Matrix& matrix_on);
void PrintMatrix(Matrix& mat);
void FreeMatrix(Matrix& matrix);
void FormRandMatrix(Matrix& mat);

void PrepareSizes(int* dimx, int* dimy, int* dims, int argc, char** argv,
                  int* mpi_size) {
  MPI_Comm_size(MPI_COMM_WORLD, mpi_size);
  if (argc > 2) {
    *dimx = atoi(argv[1]);
    *dimy = atoi(argv[2]);
  } else {
    if ((*mpi_size) % 2 != 0) {
      fprintf(stderr, "Can't create grid.\n");
      exit(EXIT_FAILURE);
    }
    *dimx = 2;
    *dimy = 2;
  }
  dims[0] = *dimy;
  dims[1] = *dimx;
  if (N1 % (*dimy) != 0 || N3 % (*dimx) != 0) {
    fprintf(stderr, "Incorrect dimensions sizes.\n");
    exit(EXIT_FAILURE);
  }
}

void CreateComms(MPI_Comm* grid, MPI_Comm* subgrid_rows, MPI_Comm* subgrid_cols,
                 int* dims) {
  int periods[2] = {0, 0};
  int reoder = 1;
  int remain_dims[2] = {0, 1};
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reoder, grid);

  MPI_Cart_sub(*grid, remain_dims, subgrid_rows);
  remain_dims[0] = 1;
  remain_dims[1] = 0;
  MPI_Cart_sub(*grid, remain_dims, subgrid_cols);
}

void GetFullCoords(MPI_Comm grid, int* dims, int* x, int* y) {
  int periods[2] = {0, 0};
  int coords[2];
  MPI_Cart_get(grid, 2, dims, periods, coords);
  *y = coords[0];
  *x = coords[1];
}

void GetGridRootRank(int* root_rank, int x, int y, MPI_Comm grid,
                     int world_rank) {
  MPI_Request reqs;
  if (x == 0 && y == 0) {
    MPI_Comm_rank(grid, root_rank);
    MPI_Isend(root_rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &reqs);
  }
  if (world_rank == 0) {
    MPI_Recv(root_rank, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }
  if (x == 0 && y == 0) {
    MPI_Wait(&reqs, MPI_STATUS_IGNORE);
  }
  MPI_Bcast(root_rank, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void CutAmatrix(Matrix A, Matrix local_A, MPI_Comm subgrid_cols) {
  int local_size = local_A.columns * local_A.rows;
  MPI_Scatter(A.matrix, local_size, MPI_MATRIX_DATA, local_A.matrix, local_size,
              MPI_MATRIX_DATA, 0, subgrid_cols);
}

void CutBMatrix(Matrix B, Matrix local_B, MPI_Comm subgrid_rows, int dimx,
                int grid_rank, int grid_root_rank) {
  int local_cols = local_B.columns;
  int local_size = local_cols * local_B.rows;
  MPI_Datatype col_type;

  MPI_Type_vector(N2, local_B.columns, N3, MPI_MATRIX_DATA, &col_type);
  MPI_Type_commit(&col_type);

  int offset = 0;
  if (grid_rank == grid_root_rank) {
    MPI_Request reqs;
    MPI_Isend(B.matrix, 1, col_type, grid_root_rank, 0, subgrid_rows, &reqs);
    MPI_Recv(local_B.matrix, local_size, MPI_MATRIX_DATA, grid_root_rank, 0,
             subgrid_rows, MPI_STATUS_IGNORE);
    MPI_Wait(&reqs, MPI_STATUS_IGNORE);
    offset += local_cols;
  }
  for (int i = 0; i < dimx; i++) {
    if (grid_rank == grid_root_rank && i != grid_root_rank) {
      MPI_Send(B.matrix + offset, 1, col_type, i, 0, subgrid_rows);
      offset += local_cols;
    }
    if (grid_rank == i && grid_rank != grid_root_rank) {
      MPI_Recv(local_B.matrix, local_size, MPI_MATRIX_DATA, grid_root_rank, 0,
               subgrid_rows, MPI_STATUS_IGNORE);
    }
  }

  MPI_Type_free(&col_type);
}

void AllocateMemoryForLocalMatrices(Matrix* local_A, Matrix* local_B, int dimx,
                                    int dimy) {
  int row_count = N1 / dimy;
  *local_A = CreateUnfilledMatrix(row_count, N2);
  int cols_count = N3 / dimx;
  *local_B = CreateUnfilledMatrix(N2, cols_count);
}

void AllocateAndFillMainMatrices(Matrix* A, Matrix* B, Matrix* result) {
  *A = CreateUnfilledMatrix(N1, N2);
  *B = CreateUnfilledMatrix(N2, N3);
  FormRandMatrix(*A);
  FormRandMatrix(*B);
  *result = CreateUnfilledMatrix(N1, N3);
}

void BroadcastLocalMatrices(Matrix local_A, Matrix local_B,
                            MPI_Comm subgrid_rows, MPI_Comm subgrid_cols) {
  MPI_Bcast(local_A.matrix, local_A.columns * local_A.rows, MPI_MATRIX_DATA, 0,
            subgrid_rows);
  MPI_Bcast(local_B.matrix, local_B.columns * local_B.rows, MPI_MATRIX_DATA, 0,
            subgrid_cols);
}

void CollectResultMatrix(Matrix result, Matrix local_result, int dimx, int dimy,
                         int x, int y, int grid_rank, int grid_root_rank,
                         MPI_Comm grid) {
  int local_cols = local_result.columns;
  int local_rows = local_result.rows;
  int total_parts = dimx * dimy;
  int local_total_size = local_cols * local_rows;

  MPI_Datatype matrix_part_type;

  MPI_Type_vector(local_rows, local_cols, result.columns, MPI_MATRIX_DATA,
                  &matrix_part_type);
  MPI_Type_commit(&matrix_part_type);

  if (grid_root_rank == grid_rank) {
    MPI_Request reqs;
    MPI_Isend(local_result.matrix, local_total_size, MPI_MATRIX_DATA,
              grid_root_rank, 0, grid, &reqs);
    int cur_x, cur_y;
    cur_x = x;
    cur_y = y;
    MPI_Recv(
        result.matrix + cur_x * local_cols + cur_y * dimx * local_total_size, 1,
        matrix_part_type, MPI_ANY_SOURCE, 0, grid, MPI_STATUS_IGNORE);
    MPI_Wait(&reqs, MPI_STATUS_IGNORE);
  }

  for (int i = 0; i < total_parts; i++) {
    MPI_Barrier(grid);
    if (grid_rank == i && grid_rank != grid_root_rank) {
      MPI_Send(&x, 1, MPI_INT, grid_root_rank, 1, grid);
      MPI_Send(&y, 1, MPI_INT, grid_root_rank, 2, grid);
      MPI_Send(local_result.matrix, local_total_size, MPI_MATRIX_DATA,
               grid_root_rank, 0, grid);
    }
    if (grid_rank == grid_root_rank && i != grid_root_rank) {
      int cur_x, cur_y;

      MPI_Recv(&cur_x, 1, MPI_INT, MPI_ANY_SOURCE, 1, grid, MPI_STATUS_IGNORE);
      MPI_Recv(&cur_y, 1, MPI_INT, MPI_ANY_SOURCE, 2, grid, MPI_STATUS_IGNORE);
      MPI_Recv(
          result.matrix + cur_x * local_cols + cur_y * dimx * local_total_size,
          1, matrix_part_type, MPI_ANY_SOURCE, 0, grid, MPI_STATUS_IGNORE);
    }
  }

  MPI_Type_free(&matrix_part_type);
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  int world_rank;
  int size;
  int dimx;
  int dimy;
  int dims[2];
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  PrepareSizes(&dimx, &dimy, dims, argc, argv, &size);

  MPI_Comm grid, subgrid_rows, subgrid_cols;
  CreateComms(&grid, &subgrid_rows, &subgrid_cols, dims);

  int x, y;
  GetFullCoords(grid, dims, &x, &y);

  int grid_root_rank;
  int grid_rank;
  MPI_Comm_rank(grid, &grid_rank);
  GetGridRootRank(&grid_root_rank, x, y, grid, world_rank);

  Matrix A;
  Matrix local_A;
  Matrix B;
  Matrix local_B;
  Matrix result;
  if (grid_rank == grid_root_rank) {
    AllocateAndFillMainMatrices(&A, &B, &result);
  }
  AllocateMemoryForLocalMatrices(&local_A, &local_B, dimx, dimy);

  if (x == 0) {
    CutAmatrix(A, local_A, subgrid_cols);
  }
  if (y == 0) {
    CutBMatrix(B, local_B, subgrid_rows, dimx, grid_rank, grid_root_rank);
  }
  BroadcastLocalMatrices(local_A, local_B, subgrid_rows, subgrid_cols);

  Matrix local_result;
  local_result.matrix = NULL;
  MultMatrixOnMatrix(local_result, local_A, local_B);
  CollectResultMatrix(result, local_result, dimx, dimy, x, y, grid_rank,
                      grid_root_rank, grid);

  if (grid_root_rank == grid_rank) {
    // PrintMatrix(result);
    FreeMatrix(A);
    FreeMatrix(B);
    FreeMatrix(result);
  }
  FreeMatrix(local_A);
  FreeMatrix(local_B);
  FreeMatrix(local_result);
  MPI_Finalize();
}

void FormRandMatrix(Matrix& mat) {
  srand(412);
  int size = mat.rows * mat.columns;
  for (int i = 0; i < size; i++) {
    mat.matrix[i] = rand() % 101;
  }
}

Matrix CreateZeroMatrix(int rows, int columns) {
  Matrix mat;
  mat.columns = columns;
  mat.rows = rows;

  mat.matrix = new MATRIX_DATA[rows * columns]();
  return mat;
}

void MultMatrixOnMatrix(Matrix& matrix_for_result, Matrix& matrix_to_mult,
                        Matrix& matrix_on) {
  int m1_rows = matrix_to_mult.rows;
  int m1_columns = matrix_to_mult.columns;
  int m2_columns = matrix_on.columns;
  MATRIX_DATA_POINTER p_matrix_to_mult = matrix_to_mult.matrix;
  MATRIX_DATA_POINTER p_matrix_on = matrix_on.matrix;

  if (matrix_for_result.rows != m1_rows ||
      matrix_for_result.columns != m2_columns) {
    FreeMatrix(matrix_for_result);
    matrix_for_result = CreateZeroMatrix(m1_rows, m2_columns);
  } else {
    FormZeroMatrix(matrix_for_result);
  }

  MATRIX_DATA_POINTER p_result = matrix_for_result.matrix;
  for (int m1_row = 0; m1_row < m1_rows; m1_row++) {
    for (int m1_col = 0; m1_col < m1_columns; m1_col++) {
      MATRIX_DATA mult_koef = p_matrix_to_mult[m1_row * m1_columns + m1_col];
      int place1 = m1_row * m2_columns;
      int place2 = m1_col * m2_columns;
      for (int m2_col = 0; m2_col < m2_columns; m2_col++) {
        p_result[place1 + m2_col] += mult_koef * p_matrix_on[place2 + m2_col];
      }
    }
  }
}

void FreeMatrix(Matrix& matrix) {
  if (&matrix) {
    delete[] matrix.matrix;
  }
}

Matrix CreateUnfilledMatrix(int rows, int columns) {
  Matrix mat;
  mat.columns = columns;
  mat.rows = rows;
  mat.matrix = new MATRIX_DATA[rows * columns];
  return mat;
}

void PrintMatrix(Matrix& mat) {
  MATRIX_DATA_POINTER matrix = mat.matrix;
  const int size = mat.columns * mat.rows;
  const int max_columns = mat.columns;
  int index_for_print = 1;
  for (int cur = 0; cur < size; cur++, index_for_print++) {
    fprintf(stdout, "%0.1f ", matrix[cur]);
    if (index_for_print % max_columns == 0) {
      fprintf(stdout, "\n");
    }
  }
}

void FormZeroMatrix(Matrix& mat) {
  memset(mat.matrix, 0, sizeof(MATRIX_DATA) * mat.columns * mat.rows);
}

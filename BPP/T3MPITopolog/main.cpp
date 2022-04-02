#include <mpi.h>
#include <string.h>

#include <iostream>

#define MATRIX_DATA_POINTER double*
#define MATRIX_DATA double
#define MPI_MATRIX_DATA MPI_DOUBLE

// #define N1 13824
// #define N2 1728
// #define N3 2304
#define N1 12
#define N2 12
#define N3 12

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

void CreateTopologies(MPI_Comm* grid, MPI_Comm* subgrid_rows,
                      MPI_Comm* subgrid_cols, int* dims) {
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

void GetRootWorldRank(int* root_rank, int x, int y, MPI_Comm grid,
                      int world_rank) {
  if (x == 0 && y == 0) {
    MPI_Comm_rank(grid, root_rank);
    MPI_Send(root_rank, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }
  if (world_rank == 0) {
    MPI_Recv(root_rank, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
  }
  MPI_Bcast(root_rank, 1, MPI_INT, 0, MPI_COMM_WORLD);
}

void CutAmatrix(int* o_total_local_A_size, int dimy, Matrix A,
                Matrix* uninit_local_A, MPI_Comm subgrid_cols, int world_rank) {
  int row_count = N1 / dimy;
  *o_total_local_A_size = row_count * N2;
  *uninit_local_A = CreateUnfilledMatrix(row_count, N2);
  int test;
  // MPI_Comm_rank(subgrid_cols, &test);
  // fprintf(stderr, "world rank %d and col %d sizes %d %d\n", world_rank, test,
  //         uninit_local_A->rows, uninit_local_A->columns);
  // if (test == 0) {
  //   PrintMatrix(A);
  // }
  if (world_rank == 0) {
    int sz;
    MPI_Comm_size(subgrid_cols, &sz);
    fprintf(stderr, "size %d\n", sz);
  }
  MPI_Scatter(A.matrix, N1 * N2, MPI_MATRIX_DATA, uninit_local_A->matrix,
              *o_total_local_A_size, MPI_MATRIX_DATA, 0, subgrid_cols);
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

  // if (!world_rank) {
  //   printf("size %d\ndimx %d\ndimy %d\ndims %d %d\n", size, dimx, dimy,
  //   dims[0],
  //          dims[1]);
  // }

  MPI_Comm grid, subgrid_rows, subgrid_cols;
  CreateTopologies(&grid, &subgrid_rows, &subgrid_cols, dims);

  int x, y;
  GetFullCoords(grid, dims, &x, &y);

  int root_rank;
  int grid_rank;
  MPI_Comm_rank(grid, &grid_rank);
  GetRootWorldRank(&root_rank, x, y, grid, world_rank);

  // for (size_t i = 0; i < size; i++) {
  //   MPI_Barrier(MPI_COMM_WORLD);
  //   if (world_rank == i) {
  //     printf("World %d and grid %d, x %d, y %d and root %d\n", world_rank,
  //            grid_rank, x, y, root_rank);
  //   }
  // }

  Matrix A;
  Matrix local_A;
  Matrix B;
  Matrix local_B;

  if (grid_rank == root_rank) {
    A = CreateUnfilledMatrix(N1, N2);
    B = CreateUnfilledMatrix(N2, N3);
    FormRandMatrix(A);
    FormRandMatrix(B);
  }
  int local_A_size;
  // if (!world_rank) {
  //   int t1, t2;
  //   MPI_Comm_size(subgrid_cols, &t2);
  //   MPI_Comm_size(subgrid_rows, &t1);
  //   printf("World %d cols %d rows %d\n", size, t1, t2);
  // }
  // int row_test = -1;
  // MPI_Comm_rank(subgrid_rows, &row_test);
  // if (row_test != -1) {
  //   int sz;
  //   MPI_Comm_size(subgrid_rows, &sz);
  //   for (size_t i = 0; i < sz; i++) {
  //     MPI_Barrier(subgrid_rows);
  //     if (i == row_test) {
  //       fprintf(stderr, "x %d y %d rank %d\n", x, y, row_test);
  //     }
  //   }
  // }
  if (x == 0)
    CutAmatrix(&local_A_size, dimy, A, &local_A, subgrid_cols, world_rank);
  // if (root_rank == grid_rank) {
  //   printf("--------00---------\n");
  //   PrintMatrix(local_A);
  // }
  // if (x == 0 && y == 1) {
  //   printf("--------01---------\n");
  //   PrintMatrix(local_A);
  // }
  // if (root_rank == grid_rank) {
  //   PrintMatrix(A);
  // }

  // if (grid_rank == root_rank) {
  //   FreeMatrix(A);
  //   FreeMatrix(B);
  // }

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
      int m2_row = m1_col;
      int place1 = m1_row * m2_columns;
      int place2 = m2_row * m2_columns;
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
    printf("%0.1f ", matrix[cur]);
    if (index_for_print % max_columns == 0) {
      printf("\n");
    }
  }
}

void FormZeroMatrix(Matrix& mat) {
  memset(mat.matrix, 0, sizeof(MATRIX_DATA) * mat.columns * mat.rows);
}

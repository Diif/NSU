#include <memory.h>
#include <mpi.h>
#include <time.h>

#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>

#define MATRIX_DATA_POINTER double*
#define MATRIX_DATA double
#define MPI_MATRIX_DATA MPI_DOUBLE
#define N 10

struct Matrix {
  MATRIX_DATA_POINTER matrix = NULL;
  int rows = 0;
  int columns = 0;
};

Matrix buffer;
Matrix vector_buffer;

Matrix CreateZeroMatrix(int rows, int columns);
Matrix CreateUnfilledMatrix(int rows, int columns);
Matrix Get_local_Ax(Matrix& vec_b, Matrix& vec_x0, Matrix& local_A_mat);
Matrix Get_r0(Matrix& local_b, Matrix& local_x_n, Matrix& local_A_mat);
Matrix Get_z0(Matrix& r0);
MATRIX_DATA GetNextAlpha(Matrix& r_n, Matrix& local_A_mat, Matrix& z_n);
MATRIX_DATA GetNextBeta(Matrix& r_n, Matrix& r_n_plus1);
void UpdateX(Matrix& x_n, Matrix& z_n, MATRIX_DATA alpha_n_plus1);
void UpdateR(Matrix& r_n, Matrix& local_A_mat, Matrix& z_n,
             MATRIX_DATA alpha_n_plus1);
void UpdateZ(Matrix& z_n, Matrix& r_n_plus1, MATRIX_DATA beta_n_plus1);
void FormAMatrix(Matrix& mat);
void FormRandMatrix(Matrix& mat);
void FormZeroMatrix(Matrix& mat);
void FormOneMatrix(Matrix& mat);
MATRIX_DATA ScalarMult(Matrix& vec1, Matrix& vec2);
MATRIX_DATA GetSqueredNorm(Matrix& vector);
void MultMatrixOnMatrix(Matrix& matrix_for_result, Matrix& matrix_to_mult,
                        Matrix& matrix_on);
void MultMatrixOnScalar(Matrix& result_matrix, Matrix& matrix_to_mult,
                        MATRIX_DATA scalar);
void AddMatrixToMatrix(Matrix& matrix_for_result, Matrix& matrix1,
                       Matrix& matrix2);
void SubMatrixFromMatrix(Matrix& matrix_for_result, Matrix& matrix_from,
                         Matrix& matrix_to);
void CopyMatrixToMatrix(Matrix& matrix_from, Matrix& matrix_to);
void PrintMatrix(Matrix& mat);
void FreeMatrix(Matrix& matrix);

void SpecialMult(Matrix& matrix_for_result, Matrix& mat_to, Matrix& vector_on);
void CalculateSizesAndDisplsForScatter(int num_of_proc, int max_rows,
                                       int max_columns, int** sizes,
                                       int** displs);
void PrepareGlobalVars();

int* sizes_for_scatter;
int* displs;
int num_of_proc, rank;
int local_start_index_in_vec;
int local_end_index_in_vec;
MATRIX_DATA cur_rn_scalar;

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  Matrix A_mat;
  Matrix vec_b;
  Matrix vec_x_n;
  time_t start;
  start = time(NULL);

  if (!rank) {
    A_mat = CreateUnfilledMatrix(N, N);
    FormAMatrix(A_mat);
  }
  CalculateSizesAndDisplsForScatter(num_of_proc, N, N, &sizes_for_scatter,
                                    &displs);
  int local_A_size = sizes_for_scatter[rank];
  int local_rows = local_A_size / N;
  if (!rank) {
    vec_b = CreateUnfilledMatrix(N, 1);
    vec_x_n = CreateZeroMatrix(N, 1);
    FormRandMatrix(vec_b);
  }

  Matrix local_b = CreateUnfilledMatrix(local_rows, 1);
  Matrix local_x_n = CreateUnfilledMatrix(local_rows, 1);
  Matrix local_A_mat = CreateUnfilledMatrix(local_rows, N);
  vector_buffer = CreateUnfilledMatrix(N, 1);

  MPI_Scatterv(A_mat.matrix, sizes_for_scatter, displs, MPI_DOUBLE,
               local_A_mat.matrix, local_A_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  PrepareGlobalVars();
  MPI_Scatterv(vec_b.matrix, sizes_for_scatter, displs, MPI_MATRIX_DATA,
               local_b.matrix, local_rows, MPI_MATRIX_DATA, 0, MPI_COMM_WORLD);
  MPI_Scatterv(vec_x_n.matrix, sizes_for_scatter, displs, MPI_MATRIX_DATA,
               local_x_n.matrix, local_rows, MPI_MATRIX_DATA, 0,
               MPI_COMM_WORLD);

  // for (size_t i = 0; i < num_of_proc; i++) {
  //   MPI_Barrier(MPI_COMM_WORLD);
  //   if (i == 0 && rank == 0) {
  //     // printf("RANK %d SIZE %d DISPLS %d------------------\n", rank,
  //     //  sizes_for_scatter[rank], displs[rank]);
  //     printf("FULL------------------\n");
  //     PrintMatrix(vec_b);
  //     printf("RANK %d------------------\n", rank);
  //     PrintMatrix(local_b);
  //   } else if (rank == i) {
  //     printf("RANK %d------------------\n", rank);
  //     PrintMatrix(local_b);
  //   }
  // }

  Matrix local_r_n = Get_r0(local_b, local_x_n, local_A_mat);
  /*
  Matrix z_n = Get_z0(r_n);
  Matrix r_prev = CreateUnfilledMatrix(r_n.rows, r_n.columns);
  CopyMatrixToMatrix(r_n, r_prev);

  MATRIX_DATA alpha_n;
  MATRIX_DATA beta_n;
  MATRIX_DATA squered_vec_b_norme = GetSqueredNorm(vec_b);
  int streak = 0;
  const MATRIX_DATA epsilon = (1e-5) * (1e-5) * squered_vec_b_norme;
  int counter = 0;

  while (streak != 5) {
    if ((cur_rn_scalar = GetSqueredNorm(r_n)) < epsilon) {
      streak++;
    } else {
      streak = 0;
    }
    counter++;
    alpha_n = GetNextAlpha(r_n, local_A_mat, z_n);
    UpdateX(vec_x_n, z_n, alpha_n);
    UpdateR(r_n, local_A_mat, z_n, alpha_n);
    beta_n = GetNextBeta(r_prev, r_n);
    CopyMatrixToMatrix(r_n, r_prev);
    UpdateZ(z_n, r_n, beta_n);
  }
  if (!rank) {
    printf("%d\n", num_of_proc);
    PrintMatrix(vec_b);
    printf("-----------------\n");
    MultMatrixOnMatrix(buffer, A_mat, vec_x_n);
    PrintMatrix(buffer);
    FreeMatrix(A_mat);
  }
  FreeMatrix(vec_b);
  FreeMatrix(vec_x_n);
  FreeMatrix(r_n);
  FreeMatrix(r_prev);
  FreeMatrix(z_n);
  FreeMatrix(buffer);
  FreeMatrix(vector_buffer);
  free(sizes_for_scatter);
  free(displs);
  if (!rank) {
    time_t end = time(NULL);
    printf("%ld\n", end - start);
  }
  */
  MPI_Finalize();
  return 0;
}

Matrix Get_r0(Matrix& local_b, Matrix& local_x_n, Matrix& local_A_mat) {
  SpecialMult(buffer, local_A_mat, local_b);
  Matrix local_r0 =
      CreateUnfilledMatrix(vector_buffer.rows, vector_buffer.columns);
  FormZeroMatrix(vector_buffer);
  MPI_Reduce(buffer.matrix, vector_buffer.matrix, vector_buffer.columns,
             MPI_MATRIX_DATA, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Scatterv(vector_buffer.matrix, sizes_for_scatter, displs, MPI_MATRIX_DATA,
               local_r0.matrix, sizes_for_scatter[rank], MPI_MATRIX_DATA, 0,
               MPI_COMM_WORLD);

  // MultMatrixOnScalar(vector_buffer, vector_buffer, -1);
  SubMatrixFromMatrix(r0, local_b, local_b);
  return r0;
}

Matrix Get_local_Ax(Matrix& vec_b, Matrix& vec_x0, Matrix& local_A_mat) {
  Matrix local_Az = CreateUnfilledMatrix(local_A_mat.rows, vec_x0.columns);
  MultMatrixOnMatrix(buffer, local_A_mat, vec_x0);
  SubMatrixFromMatrix(local_Az, vec_b, buffer);
  return local_Az;
}

Matrix Get_z0(Matrix& r0) {
  Matrix z0 = CreateUnfilledMatrix(r0.rows, r0.columns);
  CopyMatrixToMatrix(r0, z0);
  return z0;
}

MATRIX_DATA GetNextAlpha(Matrix& r_n, Matrix& local_A_mat, Matrix& z_n) {
  MultMatrixOnMatrix(buffer, local_A_mat, z_n);
  MPI_Allgatherv(buffer.matrix, sizes_for_scatter[rank], MPI_MATRIX_DATA,
                 vector_buffer.matrix, sizes_for_scatter, displs,
                 MPI_MATRIX_DATA, MPI_COMM_WORLD);
  return cur_rn_scalar / ScalarMult(vector_buffer, z_n);
}

MATRIX_DATA GetNextBeta(Matrix& r_n, Matrix& r_n_plus1) {
  return ScalarMult(r_n_plus1, r_n_plus1) / cur_rn_scalar;
}

void UpdateX(Matrix& x_n, Matrix& z_n, MATRIX_DATA alpha_n_plus1) {
  MultMatrixOnScalar(buffer, z_n, alpha_n_plus1);
  AddMatrixToMatrix(x_n, x_n, buffer);
}

void UpdateR(Matrix& r_n, Matrix& local_A_mat, Matrix& z_n,
             MATRIX_DATA alpha_n_plus1) {
  MultMatrixOnMatrix(buffer, local_A_mat, z_n);
  MPI_Allgatherv(buffer.matrix, sizes_for_scatter[rank], MPI_MATRIX_DATA,
                 vector_buffer.matrix, sizes_for_scatter, displs,
                 MPI_MATRIX_DATA, MPI_COMM_WORLD);
  MultMatrixOnScalar(vector_buffer, vector_buffer, alpha_n_plus1);
  SubMatrixFromMatrix(r_n, r_n, vector_buffer);
}

void UpdateZ(Matrix& z_n, Matrix& r_n_plus1, MATRIX_DATA beta_n_plus1) {
  MultMatrixOnScalar(z_n, z_n, beta_n_plus1);
  AddMatrixToMatrix(z_n, z_n, r_n_plus1);
}

MATRIX_DATA GetSqueredNorm(Matrix& vector) {
  if (vector.columns != 1) {
    throw(std::invalid_argument("Can't get norm not from R^n vector."));
  }
  return ScalarMult(vector, vector);
}

void FormRandMatrix(Matrix& mat) {
  srand(412);
  int size = mat.rows * mat.columns;
  for (int i = 0; i < size; i++) {
    mat.matrix[i] = rand() % 101;
  }
}

void FormOneMatrix(Matrix& mat) {
  int size = mat.rows * mat.columns;
  for (int i = 0; i < size; i++) {
    mat.matrix[i] = 1;
  }
}

void FormZeroMatrix(Matrix& mat) {
  memset(mat.matrix, 0, sizeof(MATRIX_DATA) * mat.columns * mat.rows);
}

void FormAMatrix(Matrix& mat) {
  if (mat.columns != mat.rows) {
    throw(std::invalid_argument("Matrix can't be done symmetric."));
  }
  srand(1000);
  int rows = mat.rows;
  int columns = mat.columns;
  MATRIX_DATA_POINTER matrix = mat.matrix;
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column <= row; column++) {
      if (rand() % 2 == 0) {  // TODO
        matrix[row * columns + column] = (rand() % 101) * -1;
      } else {
        matrix[row * columns + column] = (rand() % 101);
      }
      if (row * columns + column == row * columns + row) {  // diagonal * 5
        matrix[row * columns + column] *= 5;
        continue;
      }
      matrix[column * columns + row] =  // fill top triangle
          matrix[row * columns + column];
    }
  }
}

void CopyMatrixToMatrix(Matrix& matrix_from, Matrix& matrix_to) {
  if (matrix_from.rows != matrix_to.rows ||
      matrix_from.columns != matrix_to.columns) {
    throw(std::invalid_argument("Can't copy matrices."));
  }
  int size = matrix_from.rows * matrix_to.columns;
  memcpy(matrix_to.matrix, matrix_from.matrix, sizeof(MATRIX_DATA) * size);
}

Matrix CreateZeroMatrix(int rows, int columns) {
  Matrix mat;
  mat.columns = columns;
  mat.rows = rows;
  if (rows * columns == 0) {
    throw(std::invalid_argument("Invalid matrix size."));
  }
  mat.matrix = new MATRIX_DATA[rows * columns]();
  return mat;
}

Matrix CreateUnfilledMatrix(int rows, int columns) {
  Matrix mat;
  mat.columns = columns;
  mat.rows = rows;
  mat.matrix = new MATRIX_DATA[rows * columns];
  return mat;
}

void MultMatrixOnMatrix(Matrix& matrix_for_result, Matrix& matrix_to_mult,
                        Matrix& matrix_on) {
  int m1_rows = matrix_to_mult.rows;
  int m1_columns = matrix_to_mult.columns;
  int m2_rows = matrix_on.rows;
  int m2_columns = matrix_on.columns;
  MATRIX_DATA_POINTER p_matrix_to_mult = matrix_to_mult.matrix;
  MATRIX_DATA_POINTER p_matrix_on = matrix_on.matrix;
  if (m1_columns != m2_rows) {
    throw(std::invalid_argument("Matrices can't be multiplied"));
  }
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
      for (int m2_col = 0; m2_col < m2_columns; m2_col++) {
        p_result[m1_row * m2_columns + m2_col] +=
            mult_koef * p_matrix_on[m2_row * m2_columns + m2_col];
      }
    }
  }
}

void MultMatrixOnScalar(Matrix& result_matrix, Matrix& matrix_to_mult,
                        MATRIX_DATA scalar) {
  if (result_matrix.rows != matrix_to_mult.rows ||
      result_matrix.columns != matrix_to_mult.columns) {
    FreeMatrix(result_matrix);
    result_matrix =
        CreateUnfilledMatrix(matrix_to_mult.rows, matrix_to_mult.columns);
  }
  MATRIX_DATA_POINTER p_matrix = matrix_to_mult.matrix;
  MATRIX_DATA_POINTER p_result = result_matrix.matrix;
  for (int i = local_start_index_in_vec; i <= local_end_index_in_vec; i++) {
    p_result[i] = p_matrix[i] * scalar;
  }
  MPI_Allgatherv(p_result + local_start_index_in_vec, sizes_for_scatter[rank],
                 MPI_MATRIX_DATA, p_result, sizes_for_scatter, displs,
                 MPI_MATRIX_DATA, MPI_COMM_WORLD);
}

void AddMatrixToMatrix(Matrix& matrix_for_result, Matrix& matrix1,
                       Matrix& matrix2) {
  if (matrix1.rows != matrix2.rows || matrix1.columns != matrix2.columns) {
    throw(std::invalid_argument("Can't add matrices."));
  }
  if (matrix_for_result.rows != matrix1.rows ||
      matrix_for_result.columns != matrix1.columns) {
    FreeMatrix(matrix_for_result);
    matrix_for_result = CreateUnfilledMatrix(matrix1.rows, matrix1.columns);
  }

  MATRIX_DATA_POINTER p_mat1 = matrix1.matrix;
  MATRIX_DATA_POINTER p_mat2 = matrix2.matrix;
  MATRIX_DATA_POINTER p_result = matrix_for_result.matrix;
  for (int i = local_start_index_in_vec; i <= local_end_index_in_vec; i++) {
    p_result[i] = p_mat1[i] + p_mat2[i];
  }
  MPI_Allgatherv(p_result + local_start_index_in_vec, sizes_for_scatter[rank],
                 MPI_MATRIX_DATA, p_result, sizes_for_scatter, displs,
                 MPI_MATRIX_DATA, MPI_COMM_WORLD);
}

void SubMatrixFromMatrix(Matrix& matrix_for_result, Matrix& matrix_from,
                         Matrix& matrix_to) {
  if (matrix_from.rows != matrix_to.rows ||
      matrix_from.columns != matrix_to.columns) {
    throw(std::invalid_argument("Can't add matrices."));
  }
  if (matrix_for_result.rows != matrix_to.rows ||
      matrix_for_result.columns != matrix_to.columns) {
    FreeMatrix(matrix_for_result);
    matrix_for_result = CreateUnfilledMatrix(matrix_to.rows, matrix_to.columns);
  }

  MATRIX_DATA_POINTER p_mat1 = matrix_from.matrix;
  MATRIX_DATA_POINTER p_mat2 = matrix_to.matrix;
  MATRIX_DATA_POINTER p_result = matrix_for_result.matrix;
  for (int i = local_start_index_in_vec; i <= local_end_index_in_vec; i++) {
    p_result[i] = p_mat1[i] - p_mat2[i];
  }
  MPI_Allgatherv(p_result + local_start_index_in_vec, sizes_for_scatter[rank],
                 MPI_MATRIX_DATA, p_result, sizes_for_scatter, displs,
                 MPI_MATRIX_DATA, MPI_COMM_WORLD);
}

MATRIX_DATA ScalarMult(Matrix& vec1, Matrix& vec2) {
  if (1 != vec1.columns || 1 != vec2.columns || vec1.rows != vec2.rows) {
    throw(std::invalid_argument("Can mult only vectors from R^n."));
  }
  MATRIX_DATA result = 0;
  MATRIX_DATA sum = 0;
  MATRIX_DATA_POINTER mat1 = vec1.matrix;
  MATRIX_DATA_POINTER mat2 = vec2.matrix;
  for (int i = local_start_index_in_vec; i <= local_end_index_in_vec; i++) {
    sum += mat1[i] * mat2[i];
  }
  MPI_Allreduce(&sum, &result, 1, MPI_MATRIX_DATA, MPI_SUM, MPI_COMM_WORLD);
  return result;
}

void FreeMatrix(Matrix& matrix) {
  if (&matrix && matrix.matrix) {
    delete[] matrix.matrix;
  }
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

// parallel addon

void CalculateSizesAndDisplsForScatter(int num_of_proc, int max_rows,
                                       int max_columns, int** sizes,
                                       int** displs) {
  int base = max_rows / num_of_proc;
  int remainder = max_rows % num_of_proc;
  *sizes = (int*)malloc(sizeof(int) * num_of_proc);
  *displs = (int*)malloc(sizeof(int) * num_of_proc);
  int* p_sizes = *sizes;
  int* p_dispils = *displs;
  int offset = 0;
  for (int i = 0; i < num_of_proc; i++) {
    p_dispils[i] = offset;  // TODO offset, not 0
    p_sizes[i] = base * max_columns;
    offset += base * max_columns;
    if (remainder) {
      p_sizes[i] += max_columns;
      offset += max_columns;
      remainder--;
    }
  }
}

void PrepareGlobalVars() {
  for (int i = 0; i < num_of_proc; i++) {
    displs[i] /= N;
    sizes_for_scatter[i] /= N;
  }
  local_start_index_in_vec = displs[rank];
  local_end_index_in_vec = displs[rank] + sizes_for_scatter[rank] - 1;
}

void SpecialMult(Matrix& matrix_for_result, Matrix& mat_to, Matrix& vector_on) {
  int mat_rows = mat_to.rows;
  int mat_columns = mat_to.columns;
  int vec_rows = vector_on.rows;
  int vec_columns = vector_on.columns;
  MATRIX_DATA_POINTER p_matrix_to_mult = mat_to.matrix;
  MATRIX_DATA_POINTER p_vec_on = vector_on.matrix;

  if (matrix_for_result.rows != mat_columns || matrix_for_result.columns != 1) {
    FreeMatrix(matrix_for_result);
    matrix_for_result = CreateZeroMatrix(mat_columns, 1);
  } else {
    FormZeroMatrix(matrix_for_result);
  }
  MATRIX_DATA_POINTER p_result = matrix_for_result.matrix;
  for (int cur_mat_row = 0; cur_mat_row < mat_rows; cur_mat_row++) {
    int mult_coef = p_vec_on[cur_mat_row];
    for (int cur_mat_col = 0; cur_mat_col < mat_columns; cur_mat_col++) {
      p_result[cur_mat_col] +=
          mult_coef * p_matrix_to_mult[cur_mat_row * mat_columns + cur_mat_col];
    }
  }
}

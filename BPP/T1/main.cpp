#include <memory.h>
#include <time.h>

#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>

#define MATRIX_DATA_POINTER double*
#define MATRIX_DATA double
#define N 1000

struct Matrix {
  MATRIX_DATA_POINTER matrix = NULL;
  int rows = 0;
  int columns = 0;
};

Matrix buffer;

Matrix CreateZeroMatrix(int rows, int columns);
Matrix Get_r0(Matrix& vec_b, Matrix& vec_x0, Matrix& A_mat);
Matrix Get_z0(Matrix& r0);
MATRIX_DATA GetNextAlpha(Matrix& r_n, Matrix& A, Matrix& z_n);
MATRIX_DATA GetNextBeta(Matrix& r_n, Matrix& r_n_plus1);
void UpdateX(Matrix& x_n, Matrix& z_n, MATRIX_DATA alpha_n_plus1);
void UpdateR(Matrix& r_n, Matrix& A, Matrix& z_n, MATRIX_DATA alpha_n_plus1);
void UpdateZ(Matrix& z_n, Matrix& r_n_plus1, MATRIX_DATA beta_n_plus1);
void FormAMatrix(Matrix& mat);
void FormRandMatrix(Matrix& mat);
void FormZeroMatrix(Matrix& mat);
MATRIX_DATA ScalarMult(Matrix& vec1, Matrix& vec2);
MATRIX_DATA GetNorm(Matrix& vector);
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

int main(int, char**) {
  Matrix A_mat = CreateZeroMatrix(N, N);
  FormAMatrix(A_mat);
  Matrix vec_b = CreateZeroMatrix(N, 1);
  FormRandMatrix(vec_b);
  Matrix vec_x_n = CreateZeroMatrix(N, 1);
  Matrix r_n = Get_r0(vec_b, vec_x_n, A_mat);
  Matrix r_prev = Get_r0(vec_b, vec_x_n, A_mat);
  Matrix z_n = Get_z0(r_n);

  MATRIX_DATA aplha_n;
  MATRIX_DATA beta_n;
  MATRIX_DATA vec_b_norme = GetNorm(vec_b);
  int streak = 0;
  const MATRIX_DATA epsilon = 1e-5;

  while (streak != 5) {
    if (GetNorm(r_n) / vec_b_norme < epsilon) {
      streak++;
    } else {
      streak = 0;
    }
    aplha_n = GetNextAlpha(r_n, A_mat, z_n);
    UpdateX(vec_x_n, z_n, aplha_n);
    UpdateR(r_n, A_mat, z_n, aplha_n);
    beta_n = GetNextBeta(r_prev, r_n);
    UpdateR(r_prev, A_mat, z_n, aplha_n);
    UpdateZ(z_n, r_n, beta_n);
  }

  FreeMatrix(A_mat);
  FreeMatrix(vec_b);
  FreeMatrix(vec_x_n);
  FreeMatrix(r_n);
  FreeMatrix(r_prev);
  FreeMatrix(z_n);
  FreeMatrix(buffer);
}

Matrix Get_r0(Matrix& vec_b, Matrix& vec_x0, Matrix& A_mat) {
  Matrix r0 = CreateZeroMatrix(A_mat.rows, vec_x0.columns);
  MultMatrixOnMatrix(buffer, A_mat, vec_x0);
  SubMatrixFromMatrix(r0, vec_b, buffer);
  return r0;
}
Matrix Get_z0(Matrix& r0) {
  Matrix z0 = CreateZeroMatrix(r0.rows, r0.columns);
  CopyMatrixToMatrix(r0, z0);
  return z0;
}

MATRIX_DATA GetNextAlpha(Matrix& r_n, Matrix& A, Matrix& z_n) {
  MultMatrixOnMatrix(buffer, A, z_n);
  return ScalarMult(r_n, r_n) / ScalarMult(buffer, z_n);
}

MATRIX_DATA GetNextBeta(Matrix& r_n, Matrix& r_n_plus1) {
  return ScalarMult(r_n_plus1, r_n_plus1) / ScalarMult(r_n, r_n);
}

void UpdateX(Matrix& x_n, Matrix& z_n, MATRIX_DATA alpha_n_plus1) {
  MultMatrixOnScalar(buffer, z_n, alpha_n_plus1);
  AddMatrixToMatrix(x_n, x_n, buffer);
}

void UpdateR(Matrix& r_n, Matrix& A, Matrix& z_n, MATRIX_DATA alpha_n_plus1) {
  MultMatrixOnMatrix(buffer, A, z_n);
  MultMatrixOnScalar(buffer, buffer, alpha_n_plus1);
  SubMatrixFromMatrix(r_n, r_n, buffer);
}

void UpdateZ(Matrix& z_n, Matrix& r_n_plus1, MATRIX_DATA beta_n_plus1) {
  MultMatrixOnScalar(z_n, z_n, beta_n_plus1);
  AddMatrixToMatrix(z_n, z_n, r_n_plus1);
}

MATRIX_DATA GetNorm(Matrix& vector) {
  if (vector.columns != 1) {
    throw(std::invalid_argument("Can't get norm not from R^n vector."));
  }
  int size = vector.rows;
  MATRIX_DATA_POINTER p_matrix = vector.matrix;
  double result = 0;
  for (int i = 0; i < size; i++) {
    result += p_matrix[i] * p_matrix[i];
  }
  return sqrt(result);
}

void FormRandMatrix(Matrix& mat) {
  int size = mat.rows * mat.columns;
  for (int i = 0; i < size; i++) {
    mat.matrix[i] = rand() % 101;
  }
}

void FormZeroMatrix(Matrix& mat) {
  memset(mat.matrix, 0, sizeof(MATRIX_DATA) * mat.columns * mat.rows);
}

void FormAMatrix(Matrix& mat) {
  if (mat.columns != mat.rows) {
    throw(std::invalid_argument("Matrix can't be done symmetric."));
  }
  srand(time(NULL));
  int rows = mat.rows;
  int columns = mat.columns;
  MATRIX_DATA_POINTER matrix = mat.matrix;
  for (int row = 0; row < rows; row++) {
    for (int column = 0; column <= row; column++) {
      if (rand() % 2 == 0) {
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
        CreateZeroMatrix(matrix_to_mult.rows, matrix_to_mult.columns);
  }
  int size = matrix_to_mult.rows * matrix_to_mult.columns;
  MATRIX_DATA_POINTER p_matrix = matrix_to_mult.matrix;
  MATRIX_DATA_POINTER p_result = result_matrix.matrix;
  for (int i = 0; i < size; i++) {
    p_result[i] = p_matrix[i] * scalar;
  }
}

void AddMatrixToMatrix(Matrix& matrix_for_result, Matrix& matrix1,
                       Matrix& matrix2) {
  if (matrix1.rows != matrix2.rows || matrix1.columns != matrix2.columns) {
    throw(std::invalid_argument("Can't add matrices."));
  }

  if (matrix_for_result.rows != matrix1.rows ||
      matrix_for_result.columns != matrix1.columns) {
    FreeMatrix(matrix_for_result);
    matrix_for_result = CreateZeroMatrix(matrix1.rows, matrix1.columns);
  }

  int size = matrix1.columns * matrix1.rows;
  MATRIX_DATA_POINTER p_mat1 = matrix1.matrix;
  MATRIX_DATA_POINTER p_mat2 = matrix2.matrix;
  MATRIX_DATA_POINTER p_result = matrix_for_result.matrix;
  for (int i = 0; i < size; i++) {
    p_result[i] = p_mat1[i] + p_mat2[i];
  }
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
    matrix_for_result = CreateZeroMatrix(matrix_to.rows, matrix_to.columns);
  }

  int size = matrix_from.columns * matrix_from.rows;
  MATRIX_DATA_POINTER p_mat1 = matrix_from.matrix;
  MATRIX_DATA_POINTER p_mat2 = matrix_to.matrix;
  MATRIX_DATA_POINTER p_result = matrix_for_result.matrix;
  for (int i = 0; i < size; i++) {
    p_result[i] = p_mat1[i] - p_mat2[i];
  }
}

MATRIX_DATA ScalarMult(Matrix& vec1, Matrix& vec2) {
  if (1 != vec1.columns || 1 != vec2.columns || vec1.rows != vec2.rows) {
    throw(std::invalid_argument("Can mult only vectors from R^n."));
  }
  int size = vec1.rows;
  MATRIX_DATA result = 0;
  MATRIX_DATA_POINTER mat1 = vec1.matrix;
  MATRIX_DATA_POINTER mat2 = vec2.matrix;
  for (int i = 0; i < size; i++) {
    result += mat1[i] * mat2[i];
  }
  return result;
}

void FreeMatrix(Matrix& matrix) {
  if (&matrix) {
    delete[] matrix.matrix;
  }
}

void PrintMatrix(Matrix& mat) {
  MATRIX_DATA_POINTER matrix = mat.matrix;
  const int size = mat.columns * mat.rows;
  const int max_columns = mat.columns;
  int index_for_print = 1;
  for (int cur = 0; cur < size; cur++, index_for_print++) {
    printf("%0.8f ", matrix[cur]);
    if (index_for_print % max_columns == 0) {
      printf("\n");
    }
  }
}

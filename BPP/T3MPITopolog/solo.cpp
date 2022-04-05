#include <string.h>

#include <iostream>

#define MATRIX_DATA_POINTER double*
#define MATRIX_DATA double

#define N1 13824
#define N2 1728
#define N3 2304
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

void AllocateAndFillMainMatrices(Matrix* A, Matrix* B, Matrix* result) {
  *A = CreateUnfilledMatrix(N1, N2);
  *B = CreateUnfilledMatrix(N2, N3);
  FormRandMatrix(*A);
  FormRandMatrix(*B);
  *result = CreateUnfilledMatrix(N1, N3);
}

int main(int argc, char** argv) {
  Matrix A;
  Matrix B;
  Matrix result;

  AllocateAndFillMainMatrices(&A, &B, &result);
  MultMatrixOnMatrix(result, A, B);
  // PrintMatrix(result);
  FreeMatrix(A);
  FreeMatrix(B);
  FreeMatrix(result);
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
    fprintf(stdout, "%0.1f ", matrix[cur]);
    if (index_for_print % max_columns == 0) {
      fprintf(stdout, "\n");
    }
  }
}

void FormZeroMatrix(Matrix& mat) {
  memset(mat.matrix, 0, sizeof(MATRIX_DATA) * mat.columns * mat.rows);
}

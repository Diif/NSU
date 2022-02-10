#include <memory.h>
#include <time.h>

#include <cstdlib>
#include <exception>
#include <iostream>

#define N 5

struct Matrix {
  float* matrix;
  int rows;
  int columns;
};

Matrix CreateZeroMatrix(int rows, int columns);
void FormAMatrix(Matrix& mat);
void MultMatrixOnMatrix(Matrix& matrix_to_mult, Matrix& matrix_on);
void CopyMatrixToMatrix(Matrix& matrix_from, Matrix& matrix_to);
void PrintMatrix(Matrix& mat);
void FreeMatrix(Matrix& matrix);

int main(int, char**) {
  Matrix b_vector = CreateZeroMatrix(N, 1);
  Matrix mat = CreateZeroMatrix(N, N);
  FormAMatrix(mat);

  PrintMatrix(mat);
  FreeMatrix(b_vector);
  FreeMatrix(mat);
}

void MultMatrixOnMatrix(Matrix& matrix_to_mult, Matrix& matrix_on) {
  int m1_rows = matrix_to_mult.rows;
  int m1_columns = matrix_to_mult.columns;
  int m2_rows = matrix_on.rows;
  int m2_columns = matrix_on.columns;
  float* p_matrix_to_mult = matrix_to_mult.matrix;
  float* p_matrix_on = matrix_on.matrix;
  if (m1_columns != m2_rows) {
    throw(std::invalid_argument("Matrices can't be multiplied"));
  }
  Matrix result = CreateZeroMatrix(m1_rows, m2_columns);
  float* p_result = result.matrix;
  for (int m1_row = 0; m1_row < m1_rows; m1_row++) {
    for (int m1_col = 0; m1_col < m1_columns; m1_col++) {
      float mult_koef = p_matrix_to_mult[m1_row * m1_rows + m1_col];
      int m2_row = m1_col;
      for (int m2_col = 0; m2_col < m2_columns; m2_col++) {
        p_result[m1_row * m1_rows + m2_col] +=
            mult_koef * p_matrix_on[m2_row * m2_rows + m2_col];
      }
    }
  }
  CopyMatrixToMatrix(result, matrix_to_mult);
  FreeMatrix(result);
}
void FormAMatrix(Matrix& mat) {
  if (mat.columns != mat.rows) {
    throw(std::invalid_argument("Matrix can't be done symmetric."));
  }
  srand(time(NULL));
  int rows = mat.rows;
  int columns = mat.columns;
  float* matrix = mat.matrix;
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
  memcpy(matrix_to.matrix, matrix_from.matrix, sizeof(float) * size);
}

Matrix CreateZeroMatrix(int rows, int columns) {
  Matrix mat;
  mat.columns = columns;
  mat.rows = rows;
  if (rows * columns == 0) {
    throw(std::invalid_argument("Invalid matrix size."));
  }
  mat.matrix = new float[rows * columns]();
  return mat;
}

void FreeMatrix(Matrix& matrix) {
  if (&matrix) {
    delete[] matrix.matrix;
  }
}

void PrintMatrix(Matrix& mat) {
  float* matrix = mat.matrix;
  const int size = mat.columns * mat.rows;
  const int max_columns = mat.columns;
  int index_for_print = 1;
  for (int cur = 0; cur < size; cur++, index_for_print++) {
    printf("%0.0f ", matrix[cur]);
    if (index_for_print % max_columns == 0) {
      printf("\n");
    }
  }
}
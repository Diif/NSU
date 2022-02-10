#define ACCURACITY 5
#define SIZE 8

#include <cblas.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void TransposeMatrix(int size, float** matrix);
float GetMaxSumFromRows(int size, float** matrix);
float GetMaxSumFromColumns(int size, float** matrix);
int cmpfunc(const void* a, const void* b);
void PrintMatrix(int size, float** matrix);
void FreeMatrix(int size, float** matrix);
float** CreateZeroMatrix(int size);
float** CreateBMatrix(int size, float** Amatrix);
float** CreateRMatrix(int size, float** Amatrix, float** Bmatrix,
                      float** Imatrix);
void FillMatrixWithRandom(int size, float** matrix);
void CopyMatrixToMatrix(int size, float** matrix_from, float** matrix_to);
void AddMatrixToMatrix(int size, float** matrix_origin, float** matrix_to_add);
void DivideMatrixOnFloat(int size, float** matrix, float number);
void SubFromMatrixSecondMatrix(int size, float** matrix_origin,
                               float** matrix_to_sub);
float** CreateIdentityMatrix(int size);
void MultMatrixOnMatrix(int size, float** matrix_to_mult, float** matrix_on);
float** CreateInverseMatrix(int accuracity, int size, float** Imatrix,
                            float** Rmatrix, float** Bmatrix);
float** CreateInverseMatrixOPT(int accuracity, int size, float** Imatrix,
                               float** Rmatrix, float** Bmatrix);
void AddMatrixToMatrixOPT(int size, float** matrix_origin,
                          float** matrix_to_add);
void MultMatrixOnMatrixOPT(int size, float** matrix_to_mult, float** matrix_on);
float* CreateZeroMatrixBlas(int size);
void FreeMatrixBlas(float* matrix);
void CopyMatrixToMatrixBlas(int size, float* matrix_from, float* matrix_to);
float* ConvertMatrixToBlas(int size, float** matrix);
void AddMatrixToMatrixBlas(int size, float* matrix_origin,
                           float* matrix_to_add);
float* CreateInverseMatrixBlas(int accuracity, int size, float* Imatrix,
                               float* Rmatrix, float* Bmatrix, timespec* start,
                               timespec* end);
void PrintMatrixBlas(int size, float* matrix);

int main() {
  struct timespec start, end;
  srand(time(0));
  float** Amatrix = CreateZeroMatrix(SIZE);
  FillMatrixWithRandom(SIZE, Amatrix);
  PrintMatrix(SIZE, Amatrix);
  float** Bmatrix = CreateBMatrix(SIZE, Amatrix);
  printf("---------\n");
  PrintMatrix(SIZE, Bmatrix);
  printf("---------\n");
  float** Imatrix = CreateIdentityMatrix(SIZE);
  float** Rmatrix = CreateRMatrix(SIZE, Amatrix, Bmatrix, Imatrix);
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  float** inverse_matrix =
      CreateInverseMatrix(ACCURACITY, SIZE, Imatrix, Rmatrix, Bmatrix);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  printf(
      "FST Time taken: %lf sec.\n",
      end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
  PrintMatrix(SIZE, inverse_matrix);
  // FreeMatrix(SIZE, inverse_matrix);
  // clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  // inverse_matrix =
  //  CreateInverseMatrixOPT(ACCURACITY, SIZE, Imatrix, Rmatrix, Bmatrix);
  // clock_gettime(CLOCK_MONOTONIC_RAW, &end);
  // printf(
  // "SND Time taken: %lf sec.\n",
  // end.tv_sec - start.tv_sec + 0.000000001 * (end.tv_nsec - start.tv_nsec));
  // PrintMatrix(SIZE, inverse_matrix);
  /* float* Imatrix_blas = ConvertMatrixToBlas(SIZE, Imatrix);
   float* Rmatrix_blas = ConvertMatrixToBlas(SIZE, Rmatrix);
   float* Bmatrix_blas = ConvertMatrixToBlas(SIZE, Bmatrix);
   float* inverse_matrixBlas = CreateInverseMatrixBlas(
       ACCURACITY, SIZE, Imatrix_blas, Rmatrix_blas, Bmatrix_blas, &start,
   &end); printf( "TRD Time taken: %lf sec.\n", end.tv_sec - start.tv_sec +
   0.000000001 * (end.tv_nsec - start.tv_nsec)); PrintMatrixBlas(SIZE,
   inverse_matrixBlas); FreeMatrixBlas(Imatrix_blas);
   FreeMatrixBlas(Rmatrix_blas);
   FreeMatrixBlas(inverse_matrixBlas);*/
  FreeMatrix(SIZE, Amatrix);
  FreeMatrix(SIZE, Bmatrix);
  FreeMatrix(SIZE, Imatrix);
  FreeMatrix(SIZE, Rmatrix);
  FreeMatrix(SIZE, inverse_matrix);
}

float** CreateZeroMatrix(int size) {
  float** matrix = (float**)malloc(sizeof(float*) * size);
  for (int row = 0; row < size; row++) {
    matrix[row] = (float*)calloc(sizeof(float), size);
  }
  return matrix;
}

float* CreateZeroMatrixBlas(int size) {
  float* matrix = (float*)calloc(size * size, sizeof(float*));
  return matrix;
}

float** CreateIdentityMatrix(int size) {
  float** matrix = (float**)malloc(sizeof(float*) * size);
  for (int row = 0; row < size; row++) {
    matrix[row] = (float*)calloc(sizeof(float), size);
    matrix[row][row] = 1;
  }
  return matrix;
}

float** CreateBMatrix(int size, float** Amatrix) {
  float** Bmatrix = CreateZeroMatrix(size);
  CopyMatrixToMatrix(size, Amatrix, Bmatrix);
  TransposeMatrix(size, Bmatrix);
  float num_for_division =
      GetMaxSumFromRows(size, Amatrix) * GetMaxSumFromColumns(size, Amatrix);
  ;
  DivideMatrixOnFloat(size, Bmatrix, num_for_division);
  return Bmatrix;
}

float** CreateRMatrix(int size, float** Amatrix, float** Bmatrix,
                      float** Imatrix) {
  float** result = CreateZeroMatrix(size);
  AddMatrixToMatrix(size, result, Imatrix);
  float** buf = CreateZeroMatrix(size);
  CopyMatrixToMatrix(size, Bmatrix, buf);
  MultMatrixOnMatrix(size, buf, Amatrix);
  SubFromMatrixSecondMatrix(size, result, buf);
  FreeMatrix(size, buf);
  return result;
}

void FillMatrixWithRandom(int size, float** matrix) {
  int counter = 1;
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      // matrix[row][column] = counter;
      // counter++;
      if (row == column) {
        matrix[row][column] = 5;
      } else {
        matrix[row][column] = 2;
      }

      // matrix[row][column] = rand();
      // matrix[row][column] = column;
    }
  }
}
void TransposeMatrix(int size, float** matrix) {
  for (int row = 0; row < size; row++) {
    for (int column = row; column < size; column++) {
      float buf = matrix[row][column];
      matrix[row][column] = matrix[column][row];
      matrix[column][row] = buf;
    }
  }
}

float GetMaxSumFromRows(int size, float** matrix) {
  float* rows = (float*)calloc(sizeof(float), size);
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      rows[row] += matrix[row][column];
    }
  }
  qsort(rows, size, sizeof(float), cmpfunc);
  float max = rows[size - 1];
  free(rows);
  return max;
}

float GetMaxSumFromColumns(int size, float** matrix) {
  float* columns = (float*)calloc(sizeof(float), size);
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      columns[column] += matrix[row][column];
    }
  }
  qsort(columns, size, sizeof(float), cmpfunc);
  float max = columns[size - 1];
  free(columns);
  return max;
}

int cmpfunc(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

void PrintMatrix(int size, float** matrix) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      printf("%0.8f ", matrix[row][column]);
    }
    printf("\n");
  }
}
void PrintMatrixBlas(int size, float* matrix) {
  int index_for_print = 1;
  int max = size * size;
  for (int cur = 0; cur < max; cur++, index_for_print++) {
    printf("%0.8f ", matrix[cur]);
    if (index_for_print % size == 0) {
      printf("\n");
    }
  }
}

void FreeMatrix(int size, float** matrix) {
  for (int row = 0; row < size; row++) {
    free(matrix[row]);
  }
  free(matrix);
}

void FreeMatrixBlas(float* matrix) { free(matrix); }

void CopyMatrixToMatrix(int size, float** matrix_from, float** matrix_to) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      matrix_to[row][column] = matrix_from[row][column];
    }
  }
}

void CopyMatrixToMatrixBlas(int size, float* matrix_from, float* matrix_to) {
  int max = size * size;
  for (int cur = 0; cur < max; cur++) {
    matrix_to[cur] = matrix_from[cur];
  }
}

void AddMatrixToMatrix(int size, float** matrix_origin, float** matrix_to_add) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      matrix_origin[row][column] += matrix_to_add[row][column];
    }
  }
}

void AddMatrixToMatrixBlas(int size, float* matrix_origin,
                           float* matrix_to_add) {
  int max = size * size;
  for (int cur = 0; cur < max; cur++) {
    matrix_origin[cur] += matrix_to_add[cur];
  }
}

void SubFromMatrixSecondMatrix(int size, float** matrix_origin,
                               float** matrix_to_sub) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      matrix_origin[row][column] -= matrix_to_sub[row][column];
    }
  }
}

void DivideMatrixOnFloat(int size, float** matrix, float number) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      matrix[row][column] /= number;
    }
  }
}

float** CreateInverseMatrix(int accuracity, int size, float** Imatrix,
                            float** Rmatrix, float** Bmatrix) {
  float** Rmatrix_in_pow = CreateZeroMatrix(size);
  ;
  float** result = CreateZeroMatrix(size);
  CopyMatrixToMatrix(size, Rmatrix, Rmatrix_in_pow);
  AddMatrixToMatrix(size, result, Imatrix);
  while (accuracity) {
    AddMatrixToMatrix(size, result, Rmatrix_in_pow);
    // MultMatrixOnMatrix(size, Rmatrix_in_pow, Rmatrix);
    MultMatrixOnMatrix(size, Rmatrix_in_pow, Rmatrix);
    accuracity--;
  }
  MultMatrixOnMatrix(size, result, Bmatrix);
  FreeMatrix(size, Rmatrix_in_pow);
  return result;
}

float** CreateInverseMatrixOPT(int accuracity, int size, float** Imatrix,
                               float** Rmatrix, float** Bmatrix) {
  float** Rmatrix_in_pow = CreateZeroMatrix(size);
  ;
  float** result = CreateZeroMatrix(size);
  CopyMatrixToMatrix(size, Rmatrix, Rmatrix_in_pow);
  AddMatrixToMatrix(size, result, Imatrix);
  while (accuracity) {
    AddMatrixToMatrixOPT(size, result, Rmatrix_in_pow);
    MultMatrixOnMatrixOPT(size, Rmatrix_in_pow, Rmatrix);
    accuracity--;
  }
  MultMatrixOnMatrixOPT(size, result, Bmatrix);
  FreeMatrix(size, Rmatrix_in_pow);
  return result;
}

float* CreateInverseMatrixBlas(int accuracity, int size, float* Imatrix,
                               float* Rmatrix, float* Bmatrix, timespec* start,
                               timespec* end) {
  int max = size * size;
  float* Rmatrix_in_pow1 = CreateZeroMatrixBlas(size);
  float* Rmatrix_in_pow2 = CreateZeroMatrixBlas(size);
  float* result = CreateZeroMatrixBlas(size);
  float* result_buf = CreateZeroMatrixBlas(size);
  CopyMatrixToMatrixBlas(size, Rmatrix, Rmatrix_in_pow1);
  CopyMatrixToMatrixBlas(size, Rmatrix, Rmatrix_in_pow2);
  AddMatrixToMatrixBlas(size, result, Imatrix);
  clock_gettime(CLOCK_MONOTONIC_RAW, start);
  while (accuracity) {
    cblas_saxpy(max, 1.0, Rmatrix_in_pow1, 1, result, 1);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size,
                1.0, Rmatrix_in_pow1, size, Rmatrix, size, 0.0, Rmatrix_in_pow2,
                size);
    cblas_saxpy(max, 1.0, Rmatrix_in_pow2, 1, result, 1);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size,
                1.0, Rmatrix_in_pow2, size, Rmatrix, size, 0.0, Rmatrix_in_pow1,
                size);
    // MultMatrixOnMatrix(size, Rmatrix_in_pow, Rmatrix);
    accuracity -= 2;
  }
  cblas_saxpy(max, 1.0, result, 1, result_buf, 1);
  cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, size, size, size, 1.0,
              result_buf, size, Bmatrix, size, 0.0, result, size);
  clock_gettime(CLOCK_MONOTONIC_RAW, end);
  FreeMatrixBlas(result_buf);
  FreeMatrixBlas(Rmatrix_in_pow1);
  FreeMatrixBlas(Rmatrix_in_pow2);
  return result;
}

void AddMatrixToMatrixOPT(int size, float** matrix_origin,
                          float** matrix_to_add) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column += 8) {
      float* pack1 = matrix_origin[row] + column;
      float* pack2 = matrix_to_add[row] + column;
      asm("vmovups (%0), %%ymm0\n\t"
          "vmovups (%1), %%ymm1\n\t"
          "vaddps %%ymm0, %%ymm1, %%ymm1\n\t"
          "vmovups %%ymm1, (%0)\n\t"
          :
          : "r"(pack1), "r"(pack2)
          : "%ymm0", "%ymm1");
    }
  }
}

void MultMatrixOnMatrixOPT(int size, float** matrix_to_mult,
                           float** matrix_on) {
  float** result = CreateZeroMatrix(size);
  for (int row_mat1 = 0; row_mat1 < size; row_mat1++) {
    for (int col_mat1 = 0; col_mat1 < size; col_mat1++) {
      float* mult_koef = matrix_to_mult[row_mat1] + col_mat1;
      for (int col_mat2 = 0; col_mat2 < size; col_mat2 += 8) {
        float* pack1 = result[row_mat1] + col_mat2;
        float* pack2 = matrix_on[col_mat1] + col_mat2;
        // result[row_mat1][col_mat2] += mult_koef *
        // matrix_on[col_mat1][col_mat2];
        asm("vbroadcastss (%2), %%ymm1\n\t"
            "vmovups (%1), %%ymm0\n\t"
            "vmulps %%ymm0, %%ymm1, %%ymm1\n\t"
            "vmovups (%0), %%ymm0\n\t"
            "vaddps %%ymm1, %%ymm0, %%ymm0\n\t"
            "vmovups %%ymm0, (%0)\n\t"
            :
            : "r"(pack1), "r"(pack2), "r"(mult_koef)
            : "%ymm0", "%ymm1");
      }
    }
  }
  CopyMatrixToMatrix(size, result, matrix_to_mult);
  FreeMatrix(size, result);
}

void MultMatrixOnMatrix(int size, float** matrix_to_mult, float** matrix_on) {
  float** result = CreateZeroMatrix(size);
  for (int row_mat1 = 0; row_mat1 < size; row_mat1++) {
    for (int col_mat1 = 0; col_mat1 < size; col_mat1++) {
      float mult_koef = matrix_to_mult[row_mat1][col_mat1];
      for (int col_mat2 = 0; col_mat2 < size; col_mat2++) {
        result[row_mat1][col_mat2] += mult_koef * matrix_on[col_mat1][col_mat2];
      }
    }
  }
  CopyMatrixToMatrix(size, result, matrix_to_mult);
  FreeMatrix(size, result);
}

float* ConvertMatrixToBlas(int size, float** matrix) {
  float* blas_matrix = (float*)malloc(size * size * sizeof(float));
  int counter = 0;
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      blas_matrix[counter] = matrix[row][column];
      counter++;
    }
  }
  return blas_matrix;
}
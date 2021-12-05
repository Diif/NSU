#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <x86intrin.h>

#define OFFSET_IN_INTEGERS 65536
#define MAX_FRAGMENTS 32
#define REPEAT 100000

void TestCache(int offset_in_integers, int max_fragments);
unsigned long long TestMemoryAccessAndGetTicks(int* arr, int max_fragments);
void FillArray(int* arr, int offset_in_integers, int max_fragments);
float** CreateIdentityMatrix(int size);
void FreeMatrix(int size, float** matrix);
void MultMatrixOnMatrix(int size, float** matrix_to_mult, float** matrix_on);
float** CreateZeroMatrix(int size);
void CopyMatrixToMatrix(int size, float** matrix_from, float** matrix_to);

int main() {
  SYSTEM_INFO si;
  GetSystemInfo(&si);

  printf("The page size for this system is %u bytes.\n", si.dwPageSize);
  TestCache(OFFSET_IN_INTEGERS, MAX_FRAGMENTS);
}

void TestCache(int offset_in_integers, int max_fragments) {
  FILE* out = fopen("out_cache.csv", "w");
  int* arr = (int*)malloc(sizeof(int) * offset_in_integers * max_fragments);
  memset(arr, 0, sizeof(int) * offset_in_integers * max_fragments);
  for (int cur_fragments = 1; cur_fragments <= max_fragments; cur_fragments++) {
    FillArray(arr, offset_in_integers, cur_fragments);
    unsigned long long time = TestMemoryAccessAndGetTicks(arr, cur_fragments);
    fprintf(out, "%d,%.02lf\n", cur_fragments,
            (double)time / (cur_fragments * REPEAT));
  }
  free(arr);
  fclose(out);
}

unsigned long long TestMemoryAccessAndGetTicks(int* arr, int max_fragments) {
  float** Imat = CreateIdentityMatrix(100);
  float** Zmat = CreateZeroMatrix(100);
  MultMatrixOnMatrix(100, Imat, Zmat);
  int max = max_fragments * REPEAT;
  int k, i;
  for (i = 0, k = 0; i < max_fragments; i++) k = arr[k];  // warping up
  if (k == -1 || Zmat[0][0] == -1) {
    printf("Gotcha!");
  }
  unsigned long long start = __rdtsc();
  for (i = 0, k = 0; i < max; i++) {
    k = arr[k];
  }
  unsigned long long end = __rdtsc();
  if (k == -1 || Zmat[0][0] == -1) {
    printf("Gotcha!");
  }
  return end - start;
}

void FillArray(int* arr, int offset_in_integers, int max_fragments) {
  for (int i = 1; i <= max_fragments; i++) {
    arr[(i - 1) * offset_in_integers] = offset_in_integers * (i);
  }
  arr[(max_fragments - 1) * offset_in_integers] = 0;
}

void PrintArray(int* arr, int size) {
  for (size_t i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

float** CreateIdentityMatrix(int size) {
  float** matrix = (float**)malloc(sizeof(float*) * size);
  for (int row = 0; row < size; row++) {
    matrix[row] = (float*)calloc(sizeof(float), size);
    matrix[row][row] = 1;
  }
  return matrix;
}

void FreeMatrix(int size, float** matrix) {
  for (int row = 0; row < size; row++) {
    free(matrix[row]);
  }
  free(matrix);
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

float** CreateZeroMatrix(int size) {
  float** matrix = (float**)malloc(sizeof(float*) * size);
  for (int row = 0; row < size; row++) {
    matrix[row] = (float*)calloc(sizeof(float), size);
  }
  return matrix;
}

void CopyMatrixToMatrix(int size, float** matrix_from, float** matrix_to) {
  for (int row = 0; row < size; row++) {
    for (int column = 0; column < size; column++) {
      matrix_to[row][column] = matrix_from[row][column];
    }
  }
}
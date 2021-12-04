#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <x86intrin.h>

#define SIZE 100
#define MAX_SIZE 10000100
#define STEP 1.1
#define REPEAT 4

void FillArrayDirect(int* arr, int size);
void FillArrayBackward(int* arr, int size);
void PrintArray(int* arr, int size);
void FillArrayRandom(int* arr, int size);
void PrintByFilled(int* arr, int size);
unsigned long long TestMemoryAccessAndGetTicks(int size, int* arr);
void RecreateArrayWithNewSize(int** arr, int size);
void TestDirect(int size);
void TestRandom(int size);
void TestBackward(int size);
float** CreateIdentityMatrix(int size);
void FreeMatrix(int size, float** matrix);
void MultMatrixOnMatrix(int size, float** matrix_to_mult, float** matrix_on);
float** CreateZeroMatrix(int size);
void CopyMatrixToMatrix(int size, float** matrix_from, float** matrix_to);

int main() {
  TestDirect(SIZE);
  TestBackward(SIZE);
  TestRandom(SIZE);
}

void TestDirect(int size) {
  FILE* out = fopen("out_direct.csv", "w");
  for (double cur_size = size; cur_size <= MAX_SIZE; cur_size *= STEP) {
    int cur_size_int = (int)floor((double)cur_size);
    int* arr = (int*)malloc(sizeof(int) * cur_size_int);
    FillArrayDirect(arr, cur_size_int);
    unsigned long long time = TestMemoryAccessAndGetTicks(cur_size_int, arr);
    // fprintf(out, "%d,%.2lf\n", cur_size_int,
    // time / ((double)cur_size_int * REPEAT));
    fprintf(out, "%d,%.02lf\n", cur_size_int,
            (double)time / (cur_size_int * REPEAT));
    free(arr);
  }
  fclose(out);
}
void TestRandom(int size) {
  FILE* out = fopen("out_random.csv", "w");
  for (double cur_size = size; cur_size <= MAX_SIZE; cur_size *= STEP) {
    int cur_size_int = (int)floor((double)cur_size);
    int* arr = (int*)malloc(sizeof(int) * cur_size_int);
    FillArrayRandom(arr, cur_size_int);
    unsigned long long time = TestMemoryAccessAndGetTicks(cur_size_int, arr);
    fprintf(out, "%d,%.02lf\n", cur_size_int,
            (double)time / (cur_size_int * REPEAT));
    free(arr);
  }
  fclose(out);
}
void TestBackward(int size) {
  FILE* out = fopen("out_backward.csv", "w");
  for (double cur_size = size; cur_size <= MAX_SIZE; cur_size *= STEP) {
    int cur_size_int = (int)floor((double)cur_size);
    int* arr = (int*)malloc(sizeof(int) * cur_size_int);
    FillArrayBackward(arr, cur_size_int);
    unsigned long long time = TestMemoryAccessAndGetTicks(cur_size_int, arr);
    fprintf(out, "%d,%.02lf\n", cur_size_int,
            (double)time / (cur_size_int * REPEAT));
    free(arr);
  }
  fclose(out);
}

unsigned long long TestMemoryAccessAndGetTicks(int size, int* arr) {
  float** Imat = CreateIdentityMatrix(100);
  float** Zmat = CreateZeroMatrix(100);
  MultMatrixOnMatrix(100, Imat, Zmat);
  int max = size * REPEAT;
  int k, i;
  for (i = 0, k = 0; i < size; i++) k = arr[k];  // warping up
  if (k == -1 || Zmat[0][0] == -1) {
    printf("Gotcha!");
  }
  unsigned long long start = __rdtsc();
  for (i = 0, k = 0; i < max; i++) k = arr[k];
  unsigned long long end = __rdtsc();
  if (k == -1 || Zmat[0][0] == -1) {
    printf("Gotcha!");
  }
  return end - start;
}

void FillArrayDirect(int* arr, int size) {
  int val = 1;
  for (size_t i = 0; i < size; i++, val++) {
    arr[i] = val;
  }
  arr[size - 1] = 0;
}

void FillArrayBackward(int* arr, int size) {
  for (size_t i = size - 1, val = size - 2; i < size; i--, val--) {
    arr[i] = val;
  }
  arr[0] = size - 1;
}

void FillArrayRandom(int* arr, int size) {
  memset(arr, 0, size * sizeof(int));
  int max = size;
  int count = size - 1;
  int count_of_filled = 1;
  srand(time(NULL));
  int zero_coord = rand() % max;
  for (int i = 0, cur = 0; i < count; i++) {
    if (count_of_filled == count) {  // если последний элемент, то зацикливаем
                                     // его на нулевую координату
      arr[cur] = zero_coord;
      continue;
    }
    int buf = (rand() + 1) % max;
    if (buf != zero_coord && arr[buf] == 0 &&
        buf != cur) {  // мы должны указать не на себя, не на нулевую
                       // координату, на неиспользуемое ранее число
      arr[cur] = buf;
      cur = buf;
    } else {  // если не попали, то вручную ищем.
      for (; buf == zero_coord || arr[buf] != 0 || buf == cur || buf == 0;) {
        buf = (buf + 1) % max;
      }
      arr[cur] = buf;
      cur = buf;
    }
    count_of_filled++;
  }
}

void PrintArray(int* arr, int size) {
  for (size_t i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void PrintByFilled(int* arr, int size) {
  for (int i = 0, k = 0; i < size; i++) {
    printf("%d ", k);
    k = arr[k];
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
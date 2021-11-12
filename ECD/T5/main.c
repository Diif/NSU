#define ACCURACITY 2048
#define SIZE 10

#include <stdio.h>
#include <stdlib.h>
int main() {}

float** CreateMatrix(int size) {
  float** matrix = (float**)malloc(sizeof(float**));
  for (size_t row = 0; row < size; row++) {
    matrix[row] = calloc(sizeof(float), size);
    for (size_t column = 0; column < size; column++) {
      matrix[row][column] = column;
    }
  }
}

void TransposeMatrix(int size, float** matrix) {
  for (size_t row = 0; row < size; row++) {
    for (size_t column = 0; column < size; column++) {
      float buf = matrix[row][column];
      matrix[row][column] = matrix[column][row];
      matrix[column][row] = buf;
    }
  }
}

float GetMaxSumFromRows(int size, float** matrix) {
  float* rows = (float*)calloc(sizeof(float), size);
  for (size_t row = 0; row < size; row++) {
    for (size_t column = 0; column < size; column++) {
      rows[row] += matrix[row][column];
    }
  }
  qsort(rows, size, sizeof(float), cmpfunc);
  float max = rows[size - 1];
  free(rows);
  return max;
}

float GetMaxSumFromColumns(int size, float** matrix) {
  float* rows = (float*)calloc(sizeof(float), size);
  for (size_t row = 0; row < size; row++) {
    for (size_t column = 0; column < size; column++) {
      rows[row] += matrix[row][column];
    }
  }
  qsort(rows, size, sizeof(float), cmpfunc);
  float max = rows[size - 1];
  free(rows);
  return max;
}

int cmpfunc(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
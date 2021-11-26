#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10
#define STEP 1.2

void FillArrayDirect(int* arr, int size);
void FillArrayBackward(int* arr, int size);
void PrintArray(int* arr, int size);
void FillArrayRandom(int* arr, int size);

int main() {
  int* arr = (int*)malloc(sizeof(int) * SIZE);
  FillArrayDirect(arr, SIZE);
  PrintArray(arr, SIZE);
  FillArrayBackward(arr, SIZE);
  PrintArray(arr, SIZE);
  FillArrayRandom(arr, SIZE);
  PrintArray(arr, SIZE);
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
  int count_of_filled = 0;
  int zero_coord;
  srand(time(NULL));
  for (size_t i = 0; i < size; i++) {
    arr[i] = rand();
  }
}

void PrintArray(int* arr, int size) {
  for (size_t i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

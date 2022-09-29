#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
#define NUM_STR 4

void *fun(void *arg) {
  for (int i = 0; i < NUM_STR; i++) {
    printf("%s\n", ((char **)(arg))[i]);
  }

  return 0;
}

void freeAll(pthread_t *threads, char **strs) {
  for (int i = 0; i < NUM_THREADS * NUM_STR; i++) {
    free(strs[i]);
  }
  free(threads);
  free(strs);
}

int main() {
  if (NUM_STR <= 0 || NUM_THREADS <= 0) {
    printf("Incorrect values\n");
    return 0;
  }

  pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * NUM_THREADS);
  char **strs = (char **)malloc(sizeof(char *) * NUM_THREADS * NUM_STR);

  for (int i = 0; i < NUM_THREADS; i++) {
    for (int j = 0; j < NUM_STR; j++) {
      char *str =
          (char *)malloc(sizeof("String ") + (int)(ceil(log10(NUM_STR))) +
                         sizeof("thread ") + (int)(ceil(log10(NUM_THREADS))));
      sprintf(str, "String %d thread %d", j, i);
      strs[i * NUM_THREADS + j] = str;
    }
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    int err = pthread_create(threads + i, NULL, fun, strs + (NUM_THREADS * i));
    if (err) {
      printf("NOOOOOOO MY THREAD COLLECTION!!!!");
      freeAll(threads, strs);
      return 0;
    }
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  freeAll(threads, strs);

  return 0;
}
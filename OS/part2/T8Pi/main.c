#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define num_steps 2000000000
#define MAX_THREADS 100

typedef struct ThreadInfoForCalcls {
  long long start_point;
  long long end_point;
  double result;
} ThreadInfoForCalcls;

void* calculateRoutine(void* args) {
  double pi = 0;
  long long i;

  ThreadInfoForCalcls* info = ((ThreadInfoForCalcls*)args);

  for (i = info->start_point; i < info->end_point; i++) {
    pi += 1.0 / (i * 4.0 + 1.0);
    pi -= 1.0 / (i * 4.0 + 3.0);
  }

  info->result = pi;
  return NULL;
}

ThreadInfoForCalcls* getInfoForThreads(long long num_threads) {
  ThreadInfoForCalcls* info =
      (ThreadInfoForCalcls*)malloc(sizeof(ThreadInfoForCalcls) * num_threads);

  long long step_size_for_thread = num_steps / num_threads;
  long long remainder = num_steps % num_threads;
  int addition = 0;

  for (long long i = 0; i < num_threads; i++) {
    if (remainder) {
      info[i].start_point = i * step_size_for_thread + addition;
      info[i].end_point = info[i].start_point + step_size_for_thread + 1;

      addition++;
      remainder--;
    } else {
      info[i].start_point = i * step_size_for_thread + addition;
      info[i].end_point = info[i].start_point + step_size_for_thread;
    }
  }

  return info;
}

int main(int argc, char** argv) {
  // sleep(3);
  if (argc != 2) {
    printf("Wrong args.\n");
    return 1;
  }

  int num_threads;
  num_threads = atoi(argv[1]);
  if (num_threads <= 0 || num_threads > num_steps || num_steps <= 0) {
    printf("Incorrect thread number");
    return 1;
  }

  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * num_threads);
  ThreadInfoForCalcls* info = getInfoForThreads(num_threads);

  for (int i = 0; i < num_threads; i++) {
    if (pthread_create(threads + i, NULL, calculateRoutine,
                       (void*)(info + i))) {
      printf("Can't create thread #%d", i);
    }
  }

  double pi = 0;

  for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i], NULL)) {
      printf("Can't join thread #%d", i);
      continue;
    }
    pi += info[i].result;
  }

  free(info);
  pi = pi * 4.0;
  printf("pi done - %.15g \n", pi);

  return (EXIT_SUCCESS);
}

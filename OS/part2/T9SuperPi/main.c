#include <math.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define MAX_THREADS 100

int created_threads_num;

pthread_mutex_t mtx;
pthread_mutex_t cond_mtx;
pthread_cond_t cond;

int reacted_threads = 0;
int run_flag = 1;
long long max_iters = 0;

typedef struct ThreadInfoForCalcls {
  long long start_point;
  long long step;
  double result;
} ThreadInfoForCalcls;

void* calculateRoutine(void* args) {
  double pi = 0;
  long long i;

  ThreadInfoForCalcls* info = ((ThreadInfoForCalcls*)args);

  for (i = info->start_point; i <= LLONG_MAX && run_flag; i+=info->step) {
    pi += 1.0 / (i * 4.0 + 1.0);
    pi -= 1.0 / (i * 4.0 + 3.0);
  }

  pthread_mutex_lock(&mtx);
  reacted_threads++;
  if(i > max_iters){
    max_iters = i;
  }
  pthread_mutex_lock(&cond_mtx);

  if(reacted_threads == created_threads_num){
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mtx);
    pthread_mutex_unlock(&cond_mtx);
  } else{
    pthread_mutex_unlock(&mtx);
    pthread_cond_wait(&cond, &cond_mtx);
    pthread_mutex_unlock(&cond_mtx);
  }

  for (long long j = i; j < max_iters; j+=info->step) {
    pi += 1.0 / (j * 4.0 + 1.0);
    pi -= 1.0 / (j * 4.0 + 3.0);
  }

  info->result = pi;
  return NULL;
}

ThreadInfoForCalcls* getInfoForThreads(long long num_threads) {
  ThreadInfoForCalcls* info =
      (ThreadInfoForCalcls*)malloc(sizeof(ThreadInfoForCalcls) * num_threads);

  long long step_size_for_thread;
  if(num_threads == 1){
    step_size_for_thread = 1;
  }
  else{
    step_size_for_thread = num_threads;
  }
  
  for (long long i = 0; i < num_threads; i++) {
      info[i].start_point = i;
      info[i].step = step_size_for_thread;
  }

  return info;
}

void sigHandler() {
  run_flag = 0;
}

int setHandler() {
  sigset_t mask;
  sigemptyset(&mask);

  struct sigaction sa;

  sa.sa_handler = sigHandler;
  sa.sa_mask = mask;
  sa.sa_flags = 0;

  return sigaction(SIGINT, &sa, NULL);
}

int unblockSIGINT(){
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);

  return sigprocmask(SIG_SETMASK, &mask, NULL);
}

int setFullMask(){
  sigset_t mask;
  sigemptyset(&mask);
  return sigprocmask(SIG_SETMASK, &mask, NULL);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Wrong args.\n");
    return 1;
  }

  if(setFullMask()){
    printf("Can't set mask :( .");
    return 1;
  }

  int num_threads = atoi(argv[1]);
  if (num_threads <= 0) {
    printf("Incorrect thread number");
    return 1;
  }

  created_threads_num = num_threads;

  pthread_cond_init(&cond, NULL);
  pthread_mutex_init(&mtx, NULL);
  pthread_mutex_init(&cond_mtx, NULL);

  pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * num_threads);
  ThreadInfoForCalcls* info = getInfoForThreads(num_threads);

  for (int i = 0; i < num_threads; i++) {
    if (pthread_create(threads + i, NULL, calculateRoutine,
                       (void*)(info + i))) {
      printf("Can't create thread #%d", i);
    }
  }

  double pi = 0;

  if(unblockSIGINT()){
      printf("Can't unlock SIGINT :( .");
      return 1;
    }

  if(setHandler()){
    printf("Can't set handler :( .");
    return 1;
  }

  for (int i = 0; i < num_threads; i++) {
    if (pthread_join(threads[i], NULL)) {
      printf("Can't join thread #%d", i);
      continue;
    }
    pi += info[i].result;
  }

  free(info);
  pi = pi * 4.0;
  printf("Pi done - %.15g \nSteps per thread: %lld\n", pi, max_iters);

  return (EXIT_SUCCESS);
}

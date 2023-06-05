#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>

#define ROWS_FOR_EACH_THREAD 5
#define SHARE_BETWEEN_THREADS 0
sem_t sem_main;
sem_t sem_second;

void* funnyFun(void* arg) {
  for(int i = 0; i < ROWS_FOR_EACH_THREAD; i ++){
    int err = 1;
    while(err){
      err = sem_wait(&sem_main);
      switch(err){
        case 0:
          break;
        case EINVAL:
          perror("Oh no...\n");
          return 0;
        case EINTR:
          continue;
      }
    }
    printf("String %d\n", 1+2*i);
    if (sem_post(&sem_second)) {
      perror("Oh no...\n");
      return 0;
    }
  }

  return (void*)0;
}

int main() {
  pthread_t custom_thread;
  if(sem_init(&sem_main, SHARE_BETWEEN_THREADS, 0)){
    perror("Oh no...\n");
    return 0;
  }

  if(sem_init(&sem_second, SHARE_BETWEEN_THREADS, 0)){
    perror("Oh no...\n");
    return 0;
  }

  int err = pthread_create(&custom_thread, NULL, funnyFun, NULL);
  if (err) {
    perror("Oh no...\n");
    return 0;
  }
  // оп-оп, минимальное кол-во мьютексов для решения = 3! :)
  int init = 1, swap = 0;
    for(int i = 0; i < ROWS_FOR_EACH_THREAD; i ++){
    printf("String %d\n", 2*i);
    if (sem_post(&sem_main)) {
      perror("Oh no...\n");
      return 0;
    }

    int err = 1;
    while(err){
      err = sem_wait(&sem_second);
      switch(err){
        case 0:
          break;
        case EINVAL:
          perror("Oh no...\n");
          return 0;
        case EINTR:
          continue;
      }
    }
  }

  pthread_join(custom_thread, NULL);

  return 0;
}
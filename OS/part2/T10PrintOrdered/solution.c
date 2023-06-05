#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define ROWS 10

pthread_mutex_t m11 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m12 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m21 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m22 = PTHREAD_MUTEX_INITIALIZER;

int turn = 1;

void* funnyFun(void* arg) {
  int swap = 0;
  pthread_mutex_lock(&m22);

  for(int i = 0; i < ROWS; i ++){
    if(swap)
    {
      usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m12);
      usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m22);
    } else {
      usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m11);
      usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m21);
    }

    usleep((rand() % 1000)*1000);
    printf("String %d\n", 1+2*i);

    if(swap)
    {
      swap = 0;
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m12);
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m21);
    } else {
      swap = 1;
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m11);
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m22);
    }
    
  }

  return (void*)0;
}

int main() {
  pthread_t custom_thread;

  pthread_mutex_lock(&m11);
  pthread_mutex_lock(&m12);

  int err = pthread_create(&custom_thread, NULL, funnyFun, NULL);
  if (err) {
    perror(strerror(err));
    return 0;
  }
  // оп-оп, минимальное кол-во мьютексов для решения = 3! :)
  sleep(2);
  int init = 1, swap = 0;
    for(int i = 0; i < ROWS; i ++){
    if(swap)
    {
      usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m22);
      if(!init){
        usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m11);
      }
    } else {
      usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m21);
      if(!init){
        usleep((rand() % 1000)*1000);
      pthread_mutex_lock(&m12);
      }
    }
    init = 0;
usleep((rand() % 1000)*1000);
    printf("String %d\n", 2*i);

    if(swap)
    {
      swap = 0;
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m12);
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m22);
    } else {
      swap = 1;
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m11);
      usleep((rand() % 1000)*1000);
      pthread_mutex_unlock(&m21);
    }
    
  }

  pthread_join(custom_thread, NULL);

  return 0;
}
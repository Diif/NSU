#include <pthread.h>
#include <stdio.h>
#include <string.h>

int funnyFun() {
  printf("String 1\n");
  printf("String 2\n");
  printf("String 3\n");
  printf("String 4\n");
  printf("String 5\n");

  return 0;
}

int main() {
  pthread_t custom_thread;

  int err = pthread_create(&custom_thread, NULL, funnyFun, NULL);
  if (err) {
    perror(strerror(err));
    return 0;
  }

  pthread_join(custom_thread, NULL);

  printf("String 6\n");
  printf("String 7\n");
  printf("String 8\n");
  printf("String 9\n");
  printf("String 10\n");

  return 0;
}
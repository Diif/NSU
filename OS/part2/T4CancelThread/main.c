#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void* fun() {
  unsigned int i = 0;
  while (1) {
    printf("String %u\n", i);
    i++;
  }

  return 0;
}

int main() {
  pthread_t thread;

  int err = pthread_create(&thread, NULL, fun, NULL);
  if (err) {
    perror(strerror(err));
    return 0;
  }
  nanosleep(2000, NULL);

  err = pthread_cancel(thread);
  if (err) {
    perror(strerror(err));
    return 0;
  }

  printf("So dirty...\n");

  return 0;
}
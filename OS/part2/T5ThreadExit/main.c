#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

FILE* fl;
#define END_MSG_LEN 19

void endMsg() { write(STDOUT_FILENO, "My time has come...", END_MSG_LEN); }

void* fun() {
  pthread_cleanup_push(endMsg, NULL);
  unsigned int i = 0;
  char t[32];
  while (1) {
    int len = sprintf(t, "String %u\n", i);
    write(STDOUT_FILENO, t, len);
    // fprintf(stdout, "String \n");
    i++;
  }
  pthread_cleanup_pop(1);

  return 0;
}

int main() {
  pthread_t thread;
  struct timespec wait_time;
  wait_time.tv_sec = 2;
  wait_time.tv_nsec = 0;

  fl = fopen("ensMsg.txt", "wr");

  int err = pthread_create(&thread, NULL, fun, NULL);
  if (err) {
    fprintf(stderr, "%s\n", "Oh no...");
    return 1;
  }

  nanosleep(&wait_time, NULL);

  err = pthread_cancel(thread);
  if (err) {
    fprintf(stderr, "%s\n", "Oh no... Again.");
    return 1;
  }
  pthread_join(thread, NULL);
  // fflush(stdout);
  // printf("So dirty...%d \n", '\n');

  return 0;
}
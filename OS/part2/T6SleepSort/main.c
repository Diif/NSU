#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINES 100
#define DELAY 1000000
#define MAX_NANOSEC 999999999

typedef struct Line_and_time {
  char* line;
  time_t secs;
  time_t nanosecs;
  size_t len;
} Line_and_time;

void* fun(void* args) {
  Line_and_time* info = ((Line_and_time*)args);

  struct timespec wait_time;
  wait_time.tv_sec = info->secs;
  wait_time.tv_nsec = info->nanosecs;

  struct timespec rem_time;
  rem_time.tv_sec = 0;
  rem_time.tv_nsec = 0;

  while (nanosleep(&wait_time, &rem_time) == -1) {
    wait_time.tv_sec = rem_time.tv_sec;
    wait_time.tv_nsec = rem_time.tv_nsec;
  }

  printf("%s", info->line);

  return 0;
}

int main() {
  Line_and_time info[MAX_LINES];
  char* line = NULL;
  size_t line_len = 0;

  int num_threads = -1;

  for (int i = 0; i < MAX_LINES + 1; i++) {
    size_t read = getline(&line, &line_len, stdin);
    read -= 1;
    if (read == 0 || (long)read == -1) {
      num_threads = i;
      break;
    }
    info[i].line = line;
    time_t delay = read * DELAY;
    info[i].secs = delay / MAX_NANOSEC;
    info[i].nanosecs = delay % MAX_NANOSEC;
    line = NULL;
    line_len = 0;
  }

  printf("RESULT: \n");

  if (num_threads <= 0) {
    fprintf(stderr, "%s\n", "Oh no, too many lines... I'm going out.\n");
    return 1;
  }

  pthread_t threads[num_threads];

  for (int i = 0; i < num_threads; ++i) {
    pthread_create(threads + i, NULL, fun, (void*)(info + i));
  }

  for (int i = 0; i < num_threads; ++i) {
    pthread_join(threads[i], NULL);
    free(info[i].line);
  }

  return 0;
}
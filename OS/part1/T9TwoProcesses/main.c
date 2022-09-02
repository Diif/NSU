#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid == -1) {
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {
    execlp("cat", "cat", "test.txt", NULL);
    exit(EXIT_FAILURE);
  } else {
    int stat, res;
    res = wait(&stat);
    if (res == -1) {
      exit(EXIT_FAILURE);
    }
    printf("Some text for parent process...\n");
  }
  return 0;
}

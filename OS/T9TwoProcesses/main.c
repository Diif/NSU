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
    if (system("cat test.txt") == 1) {
      exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
  } else {
    int stat;
    wait(&stat);
    printf("Some text for parent process...\n");
  }
  return 0;
}

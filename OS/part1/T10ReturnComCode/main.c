#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
  if (argc < 2) {
    exit(EXIT_FAILURE);
  }
  int pid = fork();
  if (pid == -1) {
    exit(EXIT_FAILURE);
  }
  if (pid == 0) {
    execvp(argv[1], argv + 1);
  } else {
    int status;
    int sucess = wait(&status);
    if (sucess == -1) {
      exit(EXIT_FAILURE);
    } else if (WIFEXITED(status)) {
      printf("Child exit code: %d\n", WEXITSTATUS(status));
    }
  }
}

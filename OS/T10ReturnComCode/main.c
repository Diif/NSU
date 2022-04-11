#include <stdio.h>
#include <stdlib.h>
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
    execv(argv[1], argv + 1);
  } else {
  }
}

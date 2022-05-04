#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LEN 40

int main() {
  struct termios term;
  if (!tcgetattr(STDIN_FILENO, &term)) {
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    char buf[_POSIX_MAX_INPUT];

    if (!tcsetattr(STDIN_FILENO, TCSANOW, &term)) {
      char c;
      const char ERASE = term.c_cc[VERASE];
      const char KILL = term.c_cc[VKILL];
      const char CTRL_W = 23;
      const int size = sizeof(char);

      // while (read(STDIN_FILENO, &c, size) > 0) {
      // write(STDIN_FILENO, &c, size);
      while (scanf("%c", &c) > 0) {
        printf("%d\n", c);
      }
      // }
    }
  }
}

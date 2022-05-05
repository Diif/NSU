#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LEN 40

void deleteWordAndSpaces(char* buf, int* line_position) {
  int space_was_found = 0;
  int position = (*line_position) - 1;

  while (1) {
    if (position < 0) {
      *line_position = 0;
      return;
    }
    if (buf[position] == ' ') {
      space_was_found = 1;
      position--;
      continue;
    }
    if (space_was_found) {
      break;
    }
    buf[position] = ' ';
    position--;
    if (position < 0) {
      *line_position = 0;
      return;
    }
  }
  *line_position = position + 1;
}

int main() {
  struct termios term;
  if (!tcgetattr(STDIN_FILENO, &term)) {
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    char buf[MAX_LEN];
    memset(buf, 0, sizeof(char) * MAX_LEN);

    if (!tcsetattr(STDIN_FILENO, TCSANOW, &term)) {
      char c;
      const char ERASE = term.c_cc[VERASE];
      const char KILL = term.c_cc[VKILL];
      const char CTRL_W = 23;
      const char CTRL_D = 4;
      const char NEW_LINE = '\n';
      const char CARRIAGE_RETURN = '\r';
      const char BEL = 7;
      const int size = sizeof(char);
      int line_position = 0;

      while (read(STDIN_FILENO, &c, size) > 0) {
        if (c == ERASE) {
          if (line_position == 0) {
            continue;
          }
          line_position--;
          buf[line_position] = ' ';
          write(STDIN_FILENO, &CARRIAGE_RETURN, size);
          write(STDIN_FILENO, buf, (line_position + 1) * size);
          write(STDIN_FILENO, &CARRIAGE_RETURN, size);
          write(STDIN_FILENO, buf, line_position * size);
        } else if (c == KILL) {
          memset(buf, ' ', sizeof(char) * MAX_LEN);
          write(STDIN_FILENO, &CARRIAGE_RETURN, size);
          write(STDIN_FILENO, &buf, size * MAX_LEN);
          write(STDIN_FILENO, &CARRIAGE_RETURN, size);
          line_position = 0;
        } else if (c == CTRL_W) {
          int o_position = line_position;
          deleteWordAndSpaces(buf, &line_position);
          write(STDIN_FILENO, &CARRIAGE_RETURN, size);
          write(STDIN_FILENO, buf, o_position * size);
          write(STDIN_FILENO, &CARRIAGE_RETURN, size);
          write(STDIN_FILENO, buf, line_position * size);
        } else if (c == CTRL_D) {
          if (line_position == 0) {
            exit(EXIT_SUCCESS);
          }
        } else if ((c < 31 || c > 127) && c != NEW_LINE) {
          write(STDIN_FILENO, &BEL, size);
          continue;
        } else {
          if (line_position < MAX_LEN) {
            write(STDIN_FILENO, &c, size);
            buf[line_position] = c;
            line_position++;
            if (c == NEW_LINE) {
              line_position = 0;
            }
          } else {
            write(STDIN_FILENO, &NEW_LINE, size);
            line_position = 0;
          }
        }
      }
      term.c_lflag |= ICANON;
      term.c_lflag |= ECHO;
      tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
  }
}

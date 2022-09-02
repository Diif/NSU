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
    tcflag_t oflags = term.c_cflag;
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
      const char CLEAR_LINE_SEQ[] = {27, '[', '1', 'K'};
      const int size = sizeof(char);
      int line_position = 0;

      while (read(STDIN_FILENO, &c, size) > 0) {
        if (c == ERASE) {
          if (line_position == 0) {
            continue;
          }
          line_position--;
          if (write(STDIN_FILENO, CLEAR_LINE_SEQ, size * 4) == -1) {
            exit(EXIT_FAILURE);
          }
          if (write(STDIN_FILENO, &CARRIAGE_RETURN, size) == -1) {
            exit(EXIT_FAILURE);
          }
          if (write(STDIN_FILENO, buf, line_position * size) == -1) {
            exit(EXIT_FAILURE);
          }
        } else if (c == KILL) {
          if (write(STDIN_FILENO, CLEAR_LINE_SEQ, size * 4) == -1) {
            exit(EXIT_FAILURE);
          }
          if (write(STDIN_FILENO, &CARRIAGE_RETURN, size) == -1) {
            exit(EXIT_FAILURE);
          }
          line_position = 0;
        } else if (c == CTRL_W) {
          deleteWordAndSpaces(buf, &line_position);
          if (write(STDIN_FILENO, CLEAR_LINE_SEQ, size * 4) == -1) {
            exit(EXIT_FAILURE);
          }
          if (write(STDIN_FILENO, &CARRIAGE_RETURN, size) == -1) {
            exit(EXIT_FAILURE);
          }
          if (write(STDIN_FILENO, buf, line_position * size) == -1) {
            exit(EXIT_FAILURE);
          }
        } else if (c == CTRL_D) {
          if (line_position == 0) {
            term.c_lflag = oflags;
            tcsetattr(STDIN_FILENO, TCSANOW, &term);
            exit(EXIT_SUCCESS);
          }
        } else if ((c <= 31 || c >= 127) && c != NEW_LINE) {
          if (write(STDIN_FILENO, &BEL, size) == -1) {
            exit(EXIT_FAILURE);
          }
          continue;
        } else {
          if (line_position < MAX_LEN) {
            if (write(STDIN_FILENO, &c, size) == -1) {
              exit(EXIT_FAILURE);
            }
            buf[line_position] = c;
            line_position++;
            if (c == NEW_LINE) {
              line_position = 0;
            }
          } else {
            if (write(STDIN_FILENO, &NEW_LINE, size) == -1) {
              exit(EXIT_FAILURE);
            }
            line_position = 0;
          }
        }
      }
      term.c_lflag = oflags;
      if (tcsetattr(STDIN_FILENO, TCSANOW, &term)) {
        exit(EXIT_FAILURE);
      }
    }
  }
}

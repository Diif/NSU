#include "dynamic_input.h"

char dynIn::Input() {
  int res = 0, bytesWaiting;

  if (!initialized) {
    // Use termios to turn off line buffering
    struct termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = 1;
  }
  bytesWaiting = 0;
  if (ioctl(0, FIONREAD, &bytesWaiting) == 0 && bytesWaiting > 0) {
    res = getchar();
    __fpurge(stdin);
  }
  return res;
}
void dynIn::ResetTermios() {
  if (initialized) {
    // Use termios to turn off line buffering
    struct termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN, TCSANOW, &term);
    initialized = 0;
  }
}

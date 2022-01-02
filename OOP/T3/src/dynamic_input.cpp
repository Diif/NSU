#include "dynamic_input.h"

char dynIn::Input() {
  if (!initialized) {
    // Use termios to turn off line buffering
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = 1;
  }
  int bytesWaiting = 0;
  int res = 0;
  if (ioctl(0, FIONREAD, &bytesWaiting) == 0 && bytesWaiting > 0) {
    res = getchar();
    __fpurge(stdin);
  }
  return res;
}
void dynIn::ResetTermios() {
  if (initialized) {
    // Use termios to turn off line buffering
    tcgetattr(STDIN, &term);
    term.c_lflag |= ICANON;
    term.c_lflag |= ECHO;
    tcsetattr(STDIN, TCSANOW, &term);
    initialized = 0;
  }
}

#include <stdio.h>
#include <termios.h>

int main() {
  printf("Y or N ?\n");
  struct termios term;
   const int STDIN = 0;
  tcgetattr(STDIN, &term);
  term.c_lflag &= ~ICANON;
  term.c_cc[VMIN] = 1;
  tcsetattr(STDIN, TCSANOW, &term);
  char c;
  scanf("%c", &c);
  printf("\nAnswer: %c.\n", c);
}

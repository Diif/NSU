#include <stdio.h>
#include <termios.h>

int main() {
  printf("Y or N ?\n");
  struct termios term;
  const int STDIN = 0;
  tcgetattr(STDIN, &term);
  term.c_lflag &= ~ICANON;
  tcsetattr(STDIN, TCSANOW, &term);
  setbuf(stdin, NULL);
  char c;
  scanf("%c", &c);
  printf("\nAnswer: %c.\n", c);
}

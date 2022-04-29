#include <stdio.h>
#include <termios.h>

int main() {
  printf("Y or N ?\n");
  struct termios term;
  const int STDIN = 0;
  
  if(!tcgetattr(STDIN, &term)){
  	term.c_lflag &= ~ICANON;
  	int omin = term.c_cc[VMIN];
  	term.c_cc[VMIN] = 1;
 	if(!tcsetattr(STDIN, TCSANOW, &term)){;
  		char c;
  		scanf("%c", &c);
  		printf("\nAnswer: %c.\n", c);
  		term.c_lflag |= ICANON;
  		term.c_cc[VMIN] = omin;
		tcsetattr(STDIN, TCSANOW, &term);
  	}
  }
}

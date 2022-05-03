#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>

void CreateGame(int max_rows, int max_columns);
int CreateGameField(char **matrix_main, char **matrix_main_loop,
                    char **matrix_next, char **matrix_next_loop, int max_rows,
                    int max_cols);
void GameProcess(char *matrix_main, char *matrix_next, char *matrix_main_loop,
                 char *matrix_next_loop, int max_rows, int max_columns);
void EndOfGame(int loop_found);

char UpdateCellState(char *matrix, int y, int x, int max_rows, int max_columns);
void UpdateLevelState(char *matrix_main, char *matrix_next, int max_rows,
                      int max_columns);
void UpdateLoop(char *matrix_main_loop, char *matrix_next_loop, int max_rows,
                int max_columns);
void UpdateMain(char *matrix_main, char *matrix_next, int max_rows,
                int max_columns);

int CalcNeighbours(char *matrix, int y, int x, int max_rows, int max_columns);
int CheckTop(char *matrix, int y, int x, int max_rows, int max_cols);
int CheckBot(char *matrix, int y, int x, int max_rows, int max_cols);
int CheckLeft(char *matrix, int y, int x, int max_columns);
int CheckRight(char *matrix, int y, int x, int max_columns);
int CheckDiagonalsTopLeft(char *matrix, int y, int x, int max_rows,
                          int max_columns);
int CheckDiagonalsTopRight(char *matrix, int y, int x, int max_rows,
                           int max_columns);
int CheckDiagonalsBotLeft(char *matrix, int y, int x, int max_rows,
                          int max_columns);
int CheckDiagonalsBotRight(char *matrix, int y, int x, int max_rows,
                           int max_columns);
int InitMatrix(char **matrix, int max_rows, int max_columns);
int InputMatrix(char *matrix, int max_rows, int max_columns);
int CheckAndInitMatrix(char **matrix, int max_rows, int max_columns,
                       int no_error);
void CopyMatrixToMatrix(char *source, char *destination, int max_rows,
                        int max_columns);
int CompareMatrices(char *matrix1, char *matrix2, int max_rows,
                    int max_columns);
void PrintMatrix(char *matrix, int max_rows, int max_columns);

int IsCorrectSymbol(char c);
void PrintErrorMessage(char *str);
void PrintEndMessage(char *str);
void Green();
void Red();
void Cyan();
void ResetColor();

int MAX_ROWS;
int MAX_COLUMNS;

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Not enough args.Call with: ./a.out MAX_ROWS MAX_COLUMNS\n");
    exit(EXIT_FAILURE);
  }

  MAX_ROWS = atoi(argv[1]);
  MAX_COLUMNS = atoi(argv[2]);
  if (MAX_ROWS < 100 || MAX_COLUMNS < 100) {
    printf("Field is too small.\n");
    exit(EXIT_FAILURE);
  }
  CreateGame(MAX_ROWS, MAX_COLUMNS);
  return 0;
}

void CreateGame(int max_rows, int max_colums) {
  char *matrix_main, *matrix_next, *matrix_main_loop, *matrix_next_loop;
  int no_memory_overflow;

  no_memory_overflow =
      CreateGameField(&matrix_main, &matrix_main_loop, &matrix_next,
                      &matrix_next_loop, max_rows, max_colums);

  if (no_memory_overflow) {
    int no_input_error;
    no_input_error = InputMatrix(matrix_main, max_rows, max_colums);
    if (no_input_error) {
      GameProcess(matrix_main, matrix_next, matrix_main_loop, matrix_next_loop,
                  max_rows, max_colums);
    } else {
      PrintErrorMessage("Incorrect level input!");
    }
  } else {
    PrintErrorMessage("Can't allocate memory!");
  }
  if (no_memory_overflow) {
    free(matrix_main);
    free(matrix_next);
    free(matrix_main_loop);
    free(matrix_next_loop);
  }
}

int CreateGameField(char **matrix_main, char **matrix_main_loop,
                    char **matrix_next, char **matrix_next_loop, int max_rows,
                    int max_cols) {
  int no_memory_overflow = 1;
  no_memory_overflow &=
      CheckAndInitMatrix(matrix_main, max_rows, max_cols, no_memory_overflow);
  no_memory_overflow &= CheckAndInitMatrix(matrix_main_loop, max_rows, max_cols,
                                           no_memory_overflow);
  no_memory_overflow &=
      CheckAndInitMatrix(matrix_next, max_rows, max_cols, no_memory_overflow);
  no_memory_overflow &= CheckAndInitMatrix(matrix_next_loop, max_rows, max_cols,
                                           no_memory_overflow);
  return no_memory_overflow;
}

void GameProcess(char *matrix_main, char *matrix_next, char *matrix_main_loop,
                 char *matrix_next_loop, int max_rows, int max_columns) {
  int counter = 0;
  int loop_found = 0;

  CopyMatrixToMatrix(matrix_main, matrix_main_loop, max_rows, max_columns);

  while (!loop_found) {
    counter++;
    UpdateMain(matrix_main, matrix_next, max_rows, max_columns);

    UpdateLoop(matrix_main_loop, matrix_next_loop, max_rows, max_columns);

    loop_found =
        CompareMatrices(matrix_main, matrix_main_loop, max_rows, max_columns);
  }
  printf("Counter %d.\n", counter);
  EndOfGame(loop_found);
}

void EndOfGame(int loop_found) {
  if (loop_found) {
    PrintEndMessage("\nLoop was detected! Game over!");
  } else {
    PrintEndMessage("\nForce exit... Okey...............");
  }
}

void UpdateMain(char *matrix_main, char *matrix_next, int max_rows,
                int max_columns) {
  UpdateLevelState(matrix_main, matrix_next, max_rows, max_columns);
  CopyMatrixToMatrix(matrix_next, matrix_main, max_rows, max_columns);
}

void UpdateLoop(char *matrix_main_loop, char *matrix_next_loop, int max_rows,
                int max_columns) {
  UpdateLevelState(matrix_main_loop, matrix_next_loop, max_rows, max_columns);
  CopyMatrixToMatrix(matrix_next_loop, matrix_main_loop, max_rows, max_columns);
  UpdateLevelState(matrix_main_loop, matrix_next_loop, max_rows, max_columns);
  CopyMatrixToMatrix(matrix_next_loop, matrix_main_loop, max_rows, max_columns);
}

void UpdateLevelState(char *matrix_main, char *matrix_next, int max_rows,
                      int max_columns) {
  for (int cur_row = 0; cur_row < max_rows; cur_row++) {
    int shift = cur_row * max_columns;
    for (int cur_column = 0; cur_column < max_columns; cur_column++) {
      matrix_next[shift + cur_column] = UpdateCellState(
          matrix_main, cur_row, cur_column, max_rows, max_columns);
    }
  }
}

char UpdateCellState(char *matrix, int y, int x, int max_rows,
                     int max_columns) {
  int neighbours = CalcNeighbours(matrix, y, x, max_rows, max_columns);
  char cell = matrix[y * max_columns + x];
  char result = cell;

  if ((cell == ' ') && (neighbours == 3)) {
    result = '*';
  } else if (cell == '*' && neighbours != 2 && neighbours != 3) {
    result = ' ';
  }
  return result;
}

int CalcNeighbours(char *matrix, int y, int x, int max_rows, int max_columns) {
  int counter = 0;
  counter += CheckTop(matrix, y, x, max_rows, max_columns);
  counter += CheckBot(matrix, y, x, max_rows, max_columns);
  counter += CheckLeft(matrix, y, x, max_columns);
  counter += CheckRight(matrix, y, x, max_columns);
  counter += CheckDiagonalsTopLeft(matrix, y, x, max_rows, max_columns);
  counter += CheckDiagonalsTopRight(matrix, y, x, max_rows, max_columns);
  counter += CheckDiagonalsBotLeft(matrix, y, x, max_rows, max_columns);
  counter += CheckDiagonalsBotRight(matrix, y, x, max_rows, max_columns);
  return counter;
}

int CheckTop(char *matrix, int y, int x, int max_rows, int max_cols) {
  int count = 0;
  int last_row = max_rows - 1;
  if (y > 0) {
    if (matrix[(y - 1) * max_cols + x] == '*') {
      count++;
    }
  } else if (y == 0) {
    if (matrix[last_row * max_cols + x] == '*') {
      count++;
    }
  }
  return count;
}

int CheckBot(char *matrix, int y, int x, int max_rows, int max_cols) {
  int count = 0;
  int last_row = max_rows - 1;
  if (y < last_row) {
    if (matrix[(y + 1) * max_cols + x] == '*') {
      count++;
    }
  } else if (y == last_row) {
    if (matrix[x] == '*') {
      count++;
    }
  }
  return count;
}

int CheckLeft(char *matrix, int y, int x, int max_columns) {
  int count = 0;
  int last_column = max_columns - 1;
  if (x > 0) {
    if (matrix[y * max_columns + x - 1] == '*') {
      count++;
    }
  } else if (x == 0) {
    if (matrix[y * max_columns + last_column] == '*') {
      count++;
    }
  }
  return count;
}

int CheckRight(char *matrix, int y, int x, int max_columns) {
  int count = 0;
  int last_column = max_columns - 1;
  if (x < last_column) {
    if (matrix[y * max_columns + x + 1] == '*') {
      count++;
    }
  } else if (x == last_column) {
    if (matrix[y * max_columns] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsTopLeft(char *matrix, int y, int x, int max_rows,
                          int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x > 0 && y > 0) {
    if (matrix[(y - 1) * max_columns + x - 1] == '*') {
      count++;
    }
  } else if (x == 0 && y == 0) {
    if (matrix[last_row * max_columns + last_column] == '*') {
      count++;
    }
  } else if (x == 0 && y != 0) {
    if (matrix[(y - 1) * max_columns + last_column] == '*') {
      count++;
    }
  } else if (x != 0 && y == 0) {
    if (matrix[last_row * max_columns + x - 1] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsTopRight(char *matrix, int y, int x, int max_rows,
                           int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x < last_column && y > 0) {
    if (matrix[(y - 1) * max_columns + x + 1] == '*') {
      count++;
    }
  } else if (x == last_column && y == 0) {
    if (matrix[last_row * max_columns] == '*') {
      count++;
    }
  } else if (x == last_column && y != 0) {
    if (matrix[(y - 1) * max_columns] == '*') {
      count++;
    }
  } else if (x != last_column && y == 0) {
    if (matrix[last_row * max_columns + x + 1] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsBotLeft(char *matrix, int y, int x, int max_rows,
                          int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x > 0 && y < last_row) {
    if (matrix[(y + 1) * max_columns + x - 1] == '*') {
      count++;
    }
  } else if (x == 0 && y == last_row) {
    if (matrix[last_column] == '*') {
      count++;
    }
  } else if (x == 0 && y != last_row) {
    if (matrix[(y + 1) * max_columns + last_column] == '*') {
      count++;
    }
  } else if (x != 0 && y == last_row) {
    if (matrix[x - 1] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsBotRight(char *matrix, int y, int x, int max_rows,
                           int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x < last_column && y < last_row) {
    if (matrix[(y + 1) * max_columns + x + 1] == '*') {
      count++;
    }
  } else if (x == last_column && y == last_row) {
    if (matrix[0] == '*') {
      count++;
    }
  } else if (x == last_column && y != last_row) {
    if (matrix[(y + 1) * max_columns] == '*') {
      count++;
    }
  } else if (x != last_column && y == last_row) {
    if (matrix[x + 1] == '*') {
      count++;
    }
  }
  return count;
}

int InitMatrix(char **matrix, int max_rows, int max_columns) {
  int i;
  int enough_memory = 1;
  *matrix = NULL;
  *matrix = (char *)malloc(max_rows * max_columns * sizeof(char));

  if (*matrix == NULL) {
    enough_memory = 0;
  }

  return enough_memory;
}

int InputMatrix(char *matrix, int max_rows, int max_columns) {
  memset(matrix, ' ', max_columns * max_rows * sizeof(char));
  matrix[1] = '*';
  matrix[max_columns + 2] = '*';
  matrix[max_columns * 2] = '*';
  matrix[max_columns * 2 + 1] = '*';
  matrix[max_columns * 2 + 2] = '*';
  return 1;
}

int CheckAndInitMatrix(char **matrix, int max_rows, int max_columns,
                       int no_error) {
  if (no_error) {
    no_error = InitMatrix(matrix, max_rows, max_columns);
  }
  return no_error;
}

void PrintMatrix(char *matrix, int max_rows, int max_columns) {
  // Green();
  for (int y = 0; y < max_rows; y++) {
    int shift = y * max_columns;
    for (int x = 0; x < max_columns; x++) {
      printf("%c", matrix[shift + x]);
    }
    printf("\n");
  }
  // ResetColor();
  printf("\n");
}

void CopyMatrixToMatrix(char *source, char *destination, int max_rows,
                        int max_columns) {
  memcpy(destination, source, max_columns * max_rows);
}

int CompareMatrices(char *matrix1, char *matrix2, int max_rows,
                    int max_columns) {
  int is_equal = 1;

  for (int i = 0; i < max_rows && is_equal; i++) {
    int shift = max_columns * i;
    for (int j = 0; j < max_columns && is_equal; j++) {
      if (matrix1[shift + j] != matrix2[shift + j]) {
        is_equal = 0;
      }
    }
  }
  return is_equal;
}

void FreeMatrix(char *matrix) { free(matrix); }

int IsCorrectSymbol(char c) {
  int is_correct = 1;
  if (c != ' ' && c != '*') {
    is_correct = 0;
  }
  return is_correct;
}

void PrintErrorMessage(char *str) {
  Red();
  fprintf(stderr, "%s\n", str);
  ResetColor();
}

void PrintEndMessage(char *str) {
  Cyan();
  printf("%s\n", str);
  ResetColor();
}

void Green() { printf("\033[0;32m"); }

void Red() { printf("\033[0;31m"); }

void Cyan() { printf("\033[0;36m"); }

void ResetColor() { printf("\033[0m"); }

// int Input() {
//   int res = 0, bytesWaiting;
//   static const int STDIN = 0;
//   static int initialized = 0;

//   if (!initialized) {
//     // Use termios to turn off line buffering
//     struct termios term;
//     tcgetattr(STDIN, &term);
//     term.c_lflag &= ~ICANON;
//     term.c_lflag &= ~ECHO;
//     tcsetattr(STDIN, TCSANOW, &term);
//     initialized = 1;
//   }
//   bytesWaiting = 0;
//   if (ioctl(0, FIONREAD, &bytesWaiting) == 0 && bytesWaiting > 0) {
//     res = getchar();
//     // __fpurge(stdin);
//   }
//   return res;
// }

//   FILE *stream = freopen("/dev/pts/2", "r", stdin);
//   int loop_found = 0, no_life_progress = 0, iRes = 0, speed = 5, counter =
//   0; struct timeval start, stop;

//   gettimeofday(&start, NULL);

//   CopyMatrixToMatrix(matrix_main, matrix_main_loop, max_rows, max_columns);
//   PrintMatrix(matrix_main, max_rows, max_columns);

//   while (iRes != 'e' && !loop_found && !no_life_progress) {
//     iRes = Input();
//     if ((iRes == '=' || iRes == '+') && speed > 1) speed--;
//     if (iRes == '-' && speed < 6) speed++;
//     gettimeofday(&stop, NULL);
//     if ((((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec -
//           start.tv_usec) >= 10000 * speed &&
//          speed < 6) ||
//         (speed == 6 && iRes == 32)) {
//       // functions call placeholder start
//       counter++;
//       no_life_progress =
//           UpdateMain(matrix_main, matrix_next, max_rows, max_columns);

//       UpdateLoop(matrix_main_loop, matrix_next_loop, max_rows,
//       max_columns);

//       loop_found =
//           CompareMatrices(matrix_main, matrix_main_loop, max_rows,
//           max_columns);
//       printf("\e[1;1H\e[2J");
//       // PrintMatrix(matrix_main, max_rows, max_columns);
//       // functions call placeholder end
//       gettimeofday(&start, NULL);
//     }
//     printf("\rSpeed:%-i", (6 - speed));
//   }
//   printf("Counter value: %d.\n", counter);
//   EndOfGame(no_life_progress, loop_found);
// }
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>

#define MAX_ROWS 25
#define MAX_COLUMNS 80
#define GUI_MODE

void CreateGame(int max_rows, int max_columns);
int CreateGameField(char **matrix_main, char **matrix_main_loop,
                    char **matrix_next, char **matrix_next_loop, int max_rows,
                    int max_cols);
void GameProcess(char **matrix_main, char **matrix_next,
                 char **matrix_main_loop, char **matrix_next_loop, int max_rows,
                 int max_columns);
void EndOfGame(int no_life_progress, int loop_found);

char UpdateCellState(char **matrix, int y, int x, int max_rows,
                     int max_columns);
void UpdateLevelState(char **matrix_main, char **matrix_next, int max_rows,
                      int max_columns);
void UpdateLoop(char **matrix_main_loop, char **matrix_next_loop, int max_rows,
                int max_columns);
int UpdateMain(char **matrix_main, char **matrix_next, int max_rows,
               int max_columns);

int CalcNeighbours(char **matrix, int y, int x, int max_rows, int max_columns);
int CheckTop(char **matrix, int y, int x, int max_rows);
int CheckBot(char **matrix, int y, int x, int max_rows);
int CheckLeft(char **matrix, int y, int x, int max_columns);
int CheckRight(char **matrix, int y, int x, int max_columns);
int CheckDiagonalsTopLeft(char **matrix, int y, int x, int max_rows,
                          int max_columns);
int CheckDiagonalsTopRight(char **matrix, int y, int x, int max_rows,
                           int max_columns);
int CheckDiagonalsBotLeft(char **matrix, int y, int x, int max_rows,
                          int max_columns);
int CheckDiagonalsBotRight(char **matrix, int y, int x, int max_rows,
                           int max_columns);
int InitMatrix(char **matrix, int max_rows, int max_columns);
int InputMatrix(char **matrix, int max_rows, int max_columns);
int CheckAndInitMatrix(char **matrix, int max_rows, int max_columns,
                       int no_error);
void CopyMatrixToMatrix(char **source, char **destination, int max_rows,
                        int max_columns);
int CompareMatrices(char **matrix1, char **matrix2, int max_rows,
                    int max_columns);
void FreeMatrix(char **matrix, int max_rows);
void PrintMatrix(char **matrix, int max_rows, int max_columns);

int IsCorrectSymbol(char c);
void PrintErrorMessage(char *str);
void PrintEndMessage(char *str);
void Green();
void Red();
void Cyan();
void ResetColor();

int main() {
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
    FreeMatrix(matrix_main, max_rows);
    FreeMatrix(matrix_next, max_rows);
    FreeMatrix(matrix_main_loop, max_rows);
    FreeMatrix(matrix_next_loop, max_rows);
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

void GameProcess(char **matrix_main, char **matrix_next,
                 char **matrix_main_loop, char **matrix_next_loop, int max_rows,
                 int max_columns) {
  int loop_found = 0, no_life_progress = 0;

  CopyMatrixToMatrix(matrix_main, matrix_main_loop, max_rows, max_columns);

  while (!loop_found && !no_life_progress) {
    no_life_progress =
        UpdateMain(matrix_main, matrix_next, max_rows, max_columns);

    UpdateLoop(matrix_main_loop, matrix_next_loop, max_rows, max_columns);

    loop_found =
        CompareMatrices(matrix_main, matrix_main_loop, max_rows, max_columns);
  }
  EndOfGame(no_life_progress, loop_found);
}

void EndOfGame(int no_life_progress, int loop_found) {
  if (no_life_progress) {
    PrintEndMessage("\nThere are no changes! Game over!");
  } else if (loop_found) {
    PrintEndMessage("\nLoop was detected! Game over!");
  } else {
    PrintEndMessage("\nForce exit... Okey...............");
  }
}

int UpdateMain(char **matrix_main, char **matrix_next, int max_rows,
               int max_columns) {
  int end_of_game = 0;
  UpdateLevelState(matrix_main, matrix_next, max_rows, max_columns);
  end_of_game =
      CompareMatrices(matrix_main, matrix_next, max_rows, max_columns);
  CopyMatrixToMatrix(matrix_next, matrix_main, max_rows, max_columns);
  return end_of_game;
}

void UpdateLoop(char **matrix_main_loop, char **matrix_next_loop, int max_rows,
                int max_columns) {
  UpdateLevelState(matrix_main_loop, matrix_next_loop, max_rows, max_columns);
  CopyMatrixToMatrix(matrix_next_loop, matrix_main_loop, max_rows, max_columns);
  UpdateLevelState(matrix_main_loop, matrix_next_loop, max_rows, max_columns);
  CopyMatrixToMatrix(matrix_next_loop, matrix_main_loop, max_rows, max_columns);
}

void UpdateLevelState(char **matrix_main, char **matrix_next, int max_rows,
                      int max_columns) {
  for (int cur_row = 0; cur_row < max_rows; cur_row++) {
    for (int cur_column = 0; cur_column < max_columns; cur_column++) {
      matrix_next[cur_row][cur_column] = UpdateCellState(
          matrix_main, cur_row, cur_column, max_rows, max_columns);
    }
  }
}

char UpdateCellState(char **matrix, int y, int x, int max_rows,
                     int max_columns) {
  int neighbours = CalcNeighbours(matrix, y, x, max_rows, max_columns);
  char cell = matrix[y][x];
  char result = cell;

  if ((cell == ' ') && (neighbours == 3)) {
    result = '*';
  } else if (cell == '*' && neighbours != 2 && neighbours != 3) {
    result = ' ';
  }
  return result;
}

int CalcNeighbours(char **matrix, int y, int x, int max_rows, int max_columns) {
  int counter = 0;
  counter += CheckTop(matrix, y, x, max_rows);
  counter += CheckBot(matrix, y, x, max_rows);
  counter += CheckLeft(matrix, y, x, max_columns);
  counter += CheckRight(matrix, y, x, max_columns);
  counter += CheckDiagonalsTopLeft(matrix, y, x, max_rows, max_columns);
  counter += CheckDiagonalsTopRight(matrix, y, x, max_rows, max_columns);
  counter += CheckDiagonalsBotLeft(matrix, y, x, max_rows, max_columns);
  counter += CheckDiagonalsBotRight(matrix, y, x, max_rows, max_columns);
  return counter;
}

int CheckTop(char **matrix, int y, int x, int max_rows) {
  int count = 0;
  int last_row = max_rows - 1;
  if (y > 0) {
    if (matrix[y - 1][x] == '*') {
      count++;
    }
  } else if (y == 0) {
    if (matrix[last_row][x] == '*') {
      count++;
    }
  }
  return count;
}

int CheckBot(char **matrix, int y, int x, int max_rows) {
  int count = 0;
  int last_row = max_rows - 1;
  if (y < last_row) {
    if (matrix[y + 1][x] == '*') {
      count++;
    }
  } else if (y == last_row) {
    if (matrix[0][x] == '*') {
      count++;
    }
  }
  return count;
}

int CheckLeft(char **matrix, int y, int x, int max_columns) {
  int count = 0;
  int last_column = max_columns - 1;
  if (x > 0) {
    if (matrix[y][x - 1] == '*') {
      count++;
    }
  } else if (x == 0) {
    if (matrix[y][last_column] == '*') {
      count++;
    }
  }
  return count;
}

int CheckRight(char **matrix, int y, int x, int max_columns) {
  int count = 0;
  int last_column = max_columns - 1;
  if (x < last_column) {
    if (matrix[y][x + 1] == '*') {
      count++;
    }
  } else if (x == last_column) {
    if (matrix[y][0] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsTopLeft(char **matrix, int y, int x, int max_rows,
                          int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x > 0 && y > 0) {
    if (matrix[y - 1][x - 1] == '*') {
      count++;
    }
  } else if (x == 0 && y == 0) {
    if (matrix[last_row][last_column] == '*') {
      count++;
    }
  } else if (x == 0 && y != 0) {
    if (matrix[y - 1][last_column] == '*') {
      count++;
    }
  } else if (x != 0 && y == 0) {
    if (matrix[last_row][x - 1] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsTopRight(char **matrix, int y, int x, int max_rows,
                           int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x < last_column && y > 0) {
    if (matrix[y - 1][x + 1] == '*') {
      count++;
    }
  } else if (x == last_column && y == 0) {
    if (matrix[last_row][0] == '*') {
      count++;
    }
  } else if (x == last_column && y != 0) {
    if (matrix[y - 1][0] == '*') {
      count++;
    }
  } else if (x != last_column && y == 0) {
    if (matrix[last_row][x + 1] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsBotLeft(char **matrix, int y, int x, int max_rows,
                          int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x > 0 && y < last_row) {
    if (matrix[y + 1][x - 1] == '*') {
      count++;
    }
  } else if (x == 0 && y == last_row) {
    if (matrix[0][last_column] == '*') {
      count++;
    }
  } else if (x == 0 && y != last_row) {
    if (matrix[y + 1][last_column] == '*') {
      count++;
    }
  } else if (x != 0 && y == last_row) {
    if (matrix[0][x - 1] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsBotRight(char **matrix, int y, int x, int max_rows,
                           int max_columns) {
  int count = 0;
  int last_row = max_rows - 1;
  int last_column = max_columns - 1;
  if (x < last_column && y < last_row) {
    if (matrix[y + 1][x + 1] == '*') {
      count++;
    }
  } else if (x == last_column && y == last_row) {
    if (matrix[0][0] == '*') {
      count++;
    }
  } else if (x == last_column && y != last_row) {
    if (matrix[y + 1][0] == '*') {
      count++;
    }
  } else if (x != last_column && y == last_row) {
    if (matrix[0][x + 1] == '*') {
      count++;
    }
  }
  return count;
}

int InitMatrix(char **matrix, int max_rows, int max_columns) {
  int i;
  int enough_memory = 1;
  *matrix = NULL;
  *matrix = calloc(max_rows * max_columns, sizeof(char));

  if (*matrix == NULL) {
    enough_memory = 0;
  }

  return enough_memory;
}

int InputMatrix(char **matrix, int max_rows, int max_columns) {
  char c;
  int no_errors = 1;
  for (int cur_row = 0; cur_row < max_rows && no_errors; cur_row++) {
    for (int cur_column = 0; cur_column < max_columns && no_errors;
         cur_column++) {
      if (scanf("%c", &c) > 0) {
        if (c == '\n' && cur_column == 0) {
          cur_column--;
          continue;
        } else if (!IsCorrectSymbol(c)) {
          no_errors = 0;
          continue;
        }
        matrix[cur_row][cur_column] = c;
      } else {
        no_errors = 0;
      }
    }
  }
  if (scanf("%c", &c) > 0) {
    no_errors = 0;
  }
  return no_errors;
}

int CheckAndInitMatrix(char **matrix, int max_rows, int max_columns,
                       int no_error) {
  if (no_error) {
    no_error = InitMatrix(matrix, max_rows, max_columns);
  }
  return no_error;
}

void PrintMatrix(char **matrix, int max_rows, int max_columns) {
  Green();
  for (int y = 0; y < max_rows; y++) {
    for (int x = 0; x < max_columns; x++) {
      printf("%c", matrix[y][x]);
    }
    printf("\n");
  }
  ResetColor();
  printf("\n");
}

void CopyMatrixToMatrix(char **source, char **destination, int max_rows,
                        int max_columns) {
  for (int i = 0; i < max_rows; i++) {
    for (int j = 0; j < max_columns; j++) {
      destination[i][j] = source[i][j];
    }
  }
}

int CompareMatrices(char **matrix1, char **matrix2, int max_rows,
                    int max_columns) {
  int is_equal = 1;

  for (int i = 0; i < max_rows && is_equal; i++) {
    for (int j = 0; j < max_columns && is_equal; j++) {
      if (matrix1[i][j] != matrix2[i][j]) {
        is_equal = 0;
      }
    }
  }
  return is_equal;
}

void FreeMatrix(char **matrix, int max_rows) {
  for (int y = 0; y < max_rows; y++) {
    free(matrix[y]);
  }
  free(matrix);
}

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
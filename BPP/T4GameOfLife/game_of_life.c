#include <mpi.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termios.h>

void CreateGame(int max_rows, int max_columns);
int CreateGameField(char **matrix_main, char **matrix_main_loop,
                    char **matrix_next, char **matrix_next_loop);
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
int InitMatrix(char **matrix, int size);
int InputMatrix(char *matrix, int max_rows, int max_columns);
int CheckAndInitMatrix(char **matrix, int size, int no_error);
void CopyMatrixToMatrixSkipShadowLines(char *source, char *destination,
                                       int max_rows, int max_columns);
int CompareMatricesIgnoreShadow(char *matrix1, char *matrix2, int max_rows,
                                int max_columns);
void PrintMatrix(char *matrix, int max_rows, int max_columns);
void CalculateSizesAndDisplsForScatter(int num_of_proc, int max_rows,
                                       int max_columns, int **sizes,
                                       int **displs);
int IsCorrectSymbol(char c);
void PrintErrorMessage(char *str);
void PrintEndMessage(char *str);
void Green();
void Red();
void Cyan();
void ResetColor();

int MAX_ROWS;
int MAX_COLUMNS;
int num_of_proc, rank;
int *sizes_for_scatter;
int *displs;
int shadow_shift;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &num_of_proc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (argc != 3) {
    if (!rank) {
      printf("Not enough args.Call with: ./a.out MAX_ROWS MAX_COLUMNS\n");
    }
    exit(EXIT_FAILURE);
  }
  MAX_ROWS = atoi(argv[1]);
  MAX_COLUMNS = atoi(argv[2]);
  // if (MAX_ROWS < 100 || MAX_COLUMNS < 100) {
  //   if (!rank) {
  //     printf("Field is too small.\n");
  //   }
  //   exit(EXIT_FAILURE);
  // }

  CreateGame(MAX_ROWS, MAX_COLUMNS);
  MPI_Finalize();
  return 0;
}

void CreateGame(int max_rows, int max_colums) {
  char *matrix_main, *matrix_next, *matrix_main_loop, *matrix_next_loop;
  int no_memory_overflow;
  shadow_shift = max_colums;

  CalculateSizesAndDisplsForScatter(num_of_proc, max_rows, max_colums,
                                    &sizes_for_scatter, &displs);
  no_memory_overflow = CreateGameField(&matrix_main, &matrix_main_loop,
                                       &matrix_next, &matrix_next_loop);
  int num_procs_ok = 0;
  MPI_Allreduce(&no_memory_overflow, &num_procs_ok, 1, MPI_INT, MPI_SUM,
                MPI_COMM_WORLD);
  if (num_procs_ok == num_of_proc) {
    int l_max_rows = sizes_for_scatter[rank] / max_colums;
    InputMatrix(matrix_main, l_max_rows, max_colums);
    GameProcess(matrix_main, matrix_next, matrix_main_loop, matrix_next_loop,
                l_max_rows, max_colums);
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
                    char **matrix_next, char **matrix_next_loop) {
  int no_memory_overflow = 1;
  no_memory_overflow &= CheckAndInitMatrix(matrix_main, sizes_for_scatter[rank],
                                           no_memory_overflow);
  no_memory_overflow &= CheckAndInitMatrix(
      matrix_main_loop, sizes_for_scatter[rank], no_memory_overflow);
  no_memory_overflow &= CheckAndInitMatrix(matrix_next, sizes_for_scatter[rank],
                                           no_memory_overflow);
  no_memory_overflow &= CheckAndInitMatrix(
      matrix_next_loop, sizes_for_scatter[rank], no_memory_overflow);
  return no_memory_overflow;
}

void GameProcess(char *matrix_main, char *matrix_next, char *matrix_main_loop,
                 char *matrix_next_loop, int l_max_rows, int max_columns) {
  int loop_found = 0, counter = 0;
  int total_loops = 0;

  char *total_matrix;
  if (!rank) {
    total_matrix = (char *)malloc(sizeof(char) * MAX_COLUMNS * MAX_ROWS);
  }
  CopyMatrixToMatrixSkipShadowLines(matrix_main, matrix_main_loop, l_max_rows,
                                    max_columns);
  while (!loop_found) {
    counter++;
    UpdateMain(matrix_main, matrix_next, l_max_rows, max_columns);

    UpdateLoop(matrix_main_loop, matrix_next_loop, l_max_rows, max_columns);

    loop_found = CompareMatricesIgnoreShadow(matrix_main, matrix_main_loop,
                                             l_max_rows, max_columns);

    MPI_Allreduce(&loop_found, &total_loops, 1, MPI_INT, MPI_SUM,
                  MPI_COMM_WORLD);
    if (total_loops != num_of_proc) {
      total_loops = 0;
      loop_found = 0;
    }
  }
  if (!rank) {
    printf("Counter %d.\n", counter);
    EndOfGame(loop_found);
  }
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
  CopyMatrixToMatrixSkipShadowLines(matrix_next, matrix_main, max_rows,
                                    max_columns);
}

void UpdateLoop(char *matrix_main_loop, char *matrix_next_loop, int max_rows,
                int max_columns) {
  UpdateLevelState(matrix_main_loop, matrix_next_loop, max_rows, max_columns);
  CopyMatrixToMatrixSkipShadowLines(matrix_next_loop, matrix_main_loop,
                                    max_rows, max_columns);
  UpdateLevelState(matrix_main_loop, matrix_next_loop, max_rows, max_columns);
  CopyMatrixToMatrixSkipShadowLines(matrix_next_loop, matrix_main_loop,
                                    max_rows, max_columns);
}

void UpdateLevelState(char *matrix_main, char *matrix_next, int max_rows,
                      int max_columns) {
  int next_rank = rank + 1;
  int prev_rank = rank - 1;
  if (prev_rank < 0) {
    prev_rank = num_of_proc - 1;
  }
  if (next_rank >= num_of_proc) {
    next_rank = 0;
  }
  MPI_Request send_first, send_last, rec_first, rec_last;

  MPI_Isend(matrix_main + shadow_shift, max_columns, MPI_CHAR, prev_rank, 0,
            MPI_COMM_WORLD, &send_first);
  MPI_Isend(matrix_main + (max_rows * max_columns), max_columns, MPI_CHAR,
            next_rank, 1, MPI_COMM_WORLD, &send_last);
  MPI_Irecv(matrix_main, max_columns, MPI_CHAR, prev_rank, 1, MPI_COMM_WORLD,
            &rec_first);
  MPI_Irecv(matrix_main + (max_rows * max_columns) + shadow_shift, max_columns,
            MPI_CHAR, next_rank, 0, MPI_COMM_WORLD, &rec_last);
  for (int cur_row = 2; cur_row < max_rows; cur_row++) {
    int shift = cur_row * max_columns;
    for (int cur_column = 0; cur_column < max_columns; cur_column++) {
      matrix_next[shift + cur_column] = UpdateCellState(
          matrix_main, cur_row, cur_column, max_rows, max_columns);
    }
  }
  MPI_Wait(&rec_first, MPI_STATUS_IGNORE);
  int cur_row = 1;
  int shift = cur_row * max_columns;
  for (int cur_column = 0; cur_column < max_columns; cur_column++) {
    matrix_next[shift + cur_column] = UpdateCellState(
        matrix_main, cur_row, cur_column, max_rows, max_columns);
  }
  MPI_Wait(&rec_last, MPI_STATUS_IGNORE);
  cur_row = max_rows;
  shift = cur_row * max_columns;
  for (int cur_column = 0; cur_column < max_columns; cur_column++) {
    matrix_next[shift + cur_column] = UpdateCellState(
        matrix_main, cur_row, cur_column, max_rows, max_columns);
  }
  MPI_Wait(&send_first, MPI_STATUS_IGNORE);
  MPI_Wait(&send_last, MPI_STATUS_IGNORE);
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
  int last_row = max_rows;

  if (matrix[(y - 1) * max_cols + x] == '*') {
    count++;
  }

  return count;
}

int CheckBot(char *matrix, int y, int x, int max_rows, int max_cols) {
  int count = 0;
  if (matrix[(y + 1) * max_cols + x] == '*') {
    count++;
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
  int last_row = max_rows;
  int last_column = max_columns - 1;
  if (x > 0 && y >= 1) {
    if (matrix[(y - 1) * max_columns + x - 1] == '*') {
      count++;
    }
  } else if (x == 0) {
    if (matrix[(y - 1) * max_columns + last_column] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsTopRight(char *matrix, int y, int x, int max_rows,
                           int max_columns) {
  int count = 0;
  int last_row = max_rows;
  int last_column = max_columns - 1;
  if (x < last_column && y >= 1) {
    if (matrix[(y - 1) * max_columns + x + 1] == '*') {
      count++;
    }
  } else if (x == last_column) {
    if (matrix[(y - 1) * max_columns] == '*') {
      count++;
    }
  }
  return count;
}

int CheckDiagonalsBotLeft(char *matrix, int y, int x, int max_rows,
                          int max_columns) {
  int count = 0;
  int last_row = max_rows + 1;
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
  int last_row = max_rows + 1;
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

int InitMatrix(char **matrix, int size) {
  int i;
  int enough_memory = 1;
  *matrix = NULL;
  *matrix = (char *)malloc((size + shadow_shift * 2) * sizeof(char));

  if (*matrix == NULL) {
    enough_memory = 0;
  }

  return enough_memory;
}

int InputMatrix(char *matrix, int max_rows, int max_columns) {
  memset(matrix, ' ',
         (max_rows * max_columns + shadow_shift * 2) * sizeof(char));
  if (!rank) {
    matrix[1 + shadow_shift] = '*';
    matrix[max_columns + 2 + shadow_shift] = '*';
    matrix[max_columns * 2 + shadow_shift] = '*';
    matrix[max_columns * 2 + 1 + shadow_shift] = '*';
    matrix[max_columns * 2 + 2 + shadow_shift] = '*';
  }
  return 1;
}

int CheckAndInitMatrix(char **matrix, int size, int no_error) {
  if (no_error) {
    no_error = InitMatrix(matrix, size);
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

void CopyMatrixToMatrixSkipShadowLines(char *source, char *destination,
                                       int max_rows, int max_columns) {
  memcpy(destination + shadow_shift, source + shadow_shift,
         max_columns * max_rows);
}

int CompareMatricesIgnoreShadow(char *matrix1, char *matrix2, int max_rows,
                                int max_columns) {
  int is_equal = 1;
  for (int i = 1; i < max_rows && is_equal; i++) {
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

void CalculateSizesAndDisplsForScatter(int num_of_proc, int max_rows,
                                       int max_columns, int **sizes,
                                       int **displs) {
  int base = max_rows / num_of_proc;
  int remainder = max_rows % num_of_proc;
  *sizes = (int *)malloc(sizeof(int) * num_of_proc);
  *displs = (int *)malloc(sizeof(int) * num_of_proc);
  int *p_sizes = *sizes;
  int *p_dispils = *displs;
  int offset = 0;
  for (int i = 0; i < num_of_proc; i++) {
    p_dispils[i] = offset;
    p_sizes[i] = base * max_columns;
    offset += base * max_columns;
    if (remainder) {
      p_sizes[i] += max_columns;
      offset += max_columns;
      remainder--;
    }
  }
}

// MPI_Gatherv(matrix_main + shadow_shift, sizes_for_scatter[rank], MPI_CHAR,
//             total_matrix, sizes_for_scatter, displs, MPI_CHAR, 0,
//             MPI_COMM_WORLD);
// if (rank == 0) {
//   printf("-------------MAIN--------------\n");
//   PrintMatrix(total_matrix, MAX_ROWS, MAX_COLUMNS);
//   PrintMatrix(matrix_main + shadow_shift, l_max_rows, max_columns);
// }
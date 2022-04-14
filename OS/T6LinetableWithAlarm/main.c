#include <fcntl.h>
#include <malloc.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MIN_TABLE_SIZE 20

static long *offset_table;
static long *len_table;

int Resize(int old_size, int new_size, long **table) {
  if (old_size < 0 || new_size < 0 || !(*table)) {
    return -1;
  }

  long *new_table = (long *)malloc(sizeof(long) * new_size);
  if (new_table == NULL) {
    return -1;
  }
  long bytes_to_copy = sizeof(long) * old_size;
  if (new_size - old_size < 0) {
    bytes_to_copy = new_size;
  }
  memcpy(new_table, *table, bytes_to_copy);
  free(*table);
  *table = new_table;
  return 0;
}

int HasNewLine(char *str, int last_ind) {
  for (size_t i = 0; i <= last_ind; i++) {
    if (str[i] == '\n') return 1;
  }
  return 0;
}

int exec_flag;

int FillTable(int dsc, long *o_total_lines) {
  char c[11];
  exec_flag = 0;
  long len = 0;
  long offset = 0;
  long ind = 0;
  long cur_size = MIN_TABLE_SIZE;
  long lines = 0;
  offset_table = (long *)malloc(sizeof(long) * cur_size);
  len_table = (long *)malloc(sizeof(long) * cur_size);
  if (offset_table == NULL || len_table == NULL) {
    return -1;
  }

  int rec_bytes = 0;
  offset_table[ind] = 0;
  while ((rec_bytes = (read(dsc, &c, 10))) != 0) {
    if (ind + 10 > cur_size) {
      if (Resize(cur_size, cur_size * 1.5, &offset_table) == -1) {
        return -1;
      }
      if (Resize(cur_size, (cur_size *= 1.5), &len_table) == -1) {
        return -1;
      }
    }

    c[rec_bytes] = '\0';
    for (int i = 0; i < rec_bytes; i++) {
      offset++;
      if (c[i] == '\n') {
        offset_table[ind + 1] = offset;
        len_table[ind] = len + 1;
        ind++;
        lines++;
        len = 0;
        continue;
      }
      len++;
    }
  }
  (*o_total_lines) = lines;
  return 0;
}

int PrintLine(int dsc, int line) {
  lseek(dsc, offset_table[line], SEEK_SET);
  long len = len_table[line];
  char *buf = (char *)malloc(sizeof(char) * (len + 1));
  if (buf == NULL || read(dsc, buf, len) < 0) {
    return -1;
  }
  buf[len] = '\0';
  printf("%s", buf);
  free(buf);

  return 0;
}

int dsc;

void sigHandler(int sgn) {
  printf("\n");
  kill(0, SIGPROF);
  lseek(dsc, 0, SEEK_SET);
  int rec_bytes = 0;
  char str[11];
  while ((rec_bytes = (read(dsc, &str, 10))) != 0) {
    str[rec_bytes] = '\0';
    printf("%s", str);
  }
  close(dsc);
  exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGPROF);
  sigprocmask(SIG_BLOCK, &set, NULL);
  signal(SIGALRM, sigHandler);
  char *filename;
  long line = 1;
  long max_lines = 0;
  if (argc == 2) {
    filename = argv[1];
  } else {
    filename = "test.txt";
  }

  if ((dsc = open(filename, O_RDWR)) < 0) {
    fprintf(stderr, "Can't open file %s\n", filename);
    return -1;
  }

  if (FillTable(dsc, &max_lines) < 0) {
    fprintf(stderr, "Can't fill table.\n");
    return -1;
  }

  while (1) {
    fprintf(stderr, "Enter line num: ");
    alarm(5);
    if (scanf("%ld", &line) == 0) {
      printf("Incorrect value.\n");
      return -1;
    }
    if (line > max_lines || line < 0) {
      printf("Line with num %ld does not exists.\n", line);
    }
    if (line == 0) {
      break;
    }
    line--;
    PrintLine(dsc, line);
  }
  close(dsc);
  return 0;
}

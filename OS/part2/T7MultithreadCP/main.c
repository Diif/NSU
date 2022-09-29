#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH_LEN_WITH_NUL 512 + 1
#define MAX_BYTES_TO_RW 100

static int is_main_dir = 1;

void removeWordUntilSlash(char* str);
void* processDir(void* args);
int dirFileCase(char* pathFrom, char* copy_to, struct dirent* file);
void* copyFile(void* args);
int regularFileCase(char* pathFrom, char* copy_to, struct dirent* file);
char* getLastNameInPath(char* path);
int addNameToPathWithSlash(char* path, char* name, int max_len_with_nul);
int addNameToPathWithoutSlash(char* path, char* name, int max_len_with_nul);
char* extendStringToMaxLenAndFreeOld(char* str, int max_len_with_nul);
int addSlashToEnd(char* str, int max_len_with_nul);

int main(int argc, char** argv) {
  if (argc != 3) {
    printf("Not enough args.\n");
    return 1;
  }
  char** args_for_thread = (char**)malloc(sizeof(char*) * 2);
  args_for_thread[0] = argv[1];
  args_for_thread[1] = argv[2];
  processDir(args_for_thread);
  pthread_exit(NULL);
}

void removeWordUntilSlash(char* str) {
  int len = strlen(str);
  for (int i = len - 1; i >= 0 && str[i] != '/'; i--) {
    str[i] = '\0';
  }
}

void* processDir(void* args) {
  char *copy_from, *copy_to, *copy_from_dir_name;
  int can_free = 1;

  if (is_main_dir) {
    can_free = 0;
    is_main_dir = 0;
  }

  copy_from = ((char**)args)[0];
  copy_to = ((char**)args)[1];
  if (strlen(copy_from) >= MAX_PATH_LEN_WITH_NUL) {
    printf("Copy from is too long: %s\n", copy_from);
    free(args);
    if (can_free) {
      free(copy_from);
      free(copy_to);
    }
    pthread_exit(NULL);
  }
  if ((copy_from_dir_name = getLastNameInPath(copy_from)) == NULL) {
    printf("Invalid copy from name: %s\n", copy_from);
    free(args);
    if (can_free) {
      free(copy_from);
      free(copy_to);
    }
    pthread_exit(NULL);
  }

  if (can_free) {
    copy_to = extendStringToMaxLenAndFreeOld(copy_to, MAX_PATH_LEN_WITH_NUL);
  } else {
    char* new_str = (char*)malloc(sizeof(char) * MAX_PATH_LEN_WITH_NUL);
    strcpy(new_str, copy_to);
    copy_to = new_str;
  }

  if (addNameToPathWithSlash(copy_to, copy_from_dir_name,
                             MAX_PATH_LEN_WITH_NUL)) {
    printf("Copy to path is too long: %s\n", copy_to);
    free(args);
    free(copy_from_dir_name);
    if (can_free) {
      free(copy_from);
      free(copy_to);
    }
    pthread_exit(NULL);
  }

  if (mkdir(copy_to, S_IRWXU)) {
    printf("Can't create dir: %s\n", copy_to);
    free(args);
    free(copy_from_dir_name);
    if (can_free) {
      free(copy_from);
      free(copy_to);
    }
    pthread_exit(NULL);
  }
  DIR* dir = opendir(copy_from);
  if (NULL == dir) {
    printf("Invalid path: %s\n", copy_from);
    free(args);
    free(copy_from_dir_name);
    if (can_free) {
      free(copy_from);
      free(copy_to);
    }
    pthread_exit(NULL);
  }

  char* pathFrom = (char*)malloc(sizeof(char) * MAX_PATH_LEN_WITH_NUL);
  strcpy(pathFrom, copy_from);
  if (addSlashToEnd(pathFrom, MAX_PATH_LEN_WITH_NUL)) {
    printf("Copy from is too long: %s\n", copy_from);
    free(args);
    free(copy_from_dir_name);
    if (can_free) {
      free(copy_from);
      free(copy_to);
    }
    free(pathFrom);
    closedir(dir);
    pthread_exit(NULL);
  }

  struct stat sts;

  errno = 0;
  while (1) {
    struct dirent* file = readdir(dir);
    if (NULL == file) {
      if (errno != 0) {
        errno = 0;
        printf("Can't get dir entry. Skip.\n");
      } else {
        break;
      }
    }

    if (addNameToPathWithoutSlash(pathFrom, file->d_name,
                                  MAX_PATH_LEN_WITH_NUL)) {
      printf("Entry name is too long. Skip.\n");
      continue;
    }

    if (stat(pathFrom, &sts) == -1) {
      errno = 0;
      printf("Can't cast stat() on entry. Skip.\n");
      removeWordUntilSlash(pathFrom);
      continue;
    }

    switch (sts.st_mode & S_IFMT) {
      case S_IFREG:
        printf("Req: %s\n", pathFrom);
        regularFileCase(pathFrom, copy_to, file);
        break;
      case S_IFDIR:
        printf("Dir: %s\n", pathFrom);
        dirFileCase(pathFrom, copy_to, file);
        break;
      default:
        break;
    }

    removeWordUntilSlash(pathFrom);
  }
  free(copy_from_dir_name);
  free(pathFrom);
  if (can_free) {
    free(copy_from);
    free(copy_to);
  }
  free(args);
  closedir(dir);
  return NULL;
}

int regularFileCase(char* pathFrom, char* copy_to, struct dirent* file) {
  {
    char* file_path_from = (char*)malloc(sizeof(char) * MAX_PATH_LEN_WITH_NUL);
    strcpy(file_path_from, pathFrom);

    char* file_path_to = (char*)malloc(sizeof(char) * MAX_PATH_LEN_WITH_NUL);
    strcpy(file_path_to, copy_to);
    if (addNameToPathWithSlash(file_path_to, file->d_name,
                               MAX_PATH_LEN_WITH_NUL)) {
      printf("Copyto path is too long.Can't create new thread.\n");
      free(file_path_from);
      free(file_path_to);
      return -1;
    }

    char** args_for_thread = (char**)malloc(2 * sizeof(char*));
    args_for_thread[0] = file_path_from;
    args_for_thread[1] = file_path_to;

    pthread_attr_t attr;
    pthread_t thread;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    printf("\t\t\tWANT CREATE A THREAD FOR %s\n", file_path_from);
    while (1) {
      int err = pthread_create(&thread, &attr, copyFile, args_for_thread);
      if (err == EAGAIN) {
        sleep(2);
      } else if (err == 0) {
        printf("THREAD FILE CREATED\n");
        break;
      } else {
        printf("Can't create thread(idk why)\n");
        free(file_path_from);
        free(file_path_to);
        free(args_for_thread);
        pthread_attr_destroy(&attr);
        return -1;
      }
    }

    pthread_attr_destroy(&attr);
    return 0;
  }
}

int dirFileCase(char* pathFrom, char* copy_to, struct dirent* file) {
  if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
    printf("\tDrop dir: %s\n", pathFrom);
    return 0;
  }

  char* dir_path_from = (char*)malloc(sizeof(char) * MAX_PATH_LEN_WITH_NUL);
  strcpy(dir_path_from, pathFrom);

  char* dir_path_to = (char*)malloc(sizeof(char) * MAX_PATH_LEN_WITH_NUL);
  strcpy(dir_path_to, copy_to);

  char** args_for_thread = (char**)malloc(2 * sizeof(char*));
  args_for_thread[0] = dir_path_from;
  args_for_thread[1] = dir_path_to;

  pthread_attr_t attr;
  pthread_t thread;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  printf("\t\t\tWANT CREATE A THREAD FOR %s\n", dir_path_from);
  while (1) {
    int err = pthread_create(&thread, &attr, processDir, args_for_thread);
    if (err == EAGAIN) {
      sleep(2);
    } else if (err == 0) {
      printf("THREAD DIR CREATED\n");
      break;
    } else {
      printf("Can't create thread(idk why)\n");
      free(dir_path_from);
      free(dir_path_to);
      free(args_for_thread);
      pthread_attr_destroy(&attr);
      return -1;
    }
  }
  pthread_attr_destroy(&attr);
  return 0;
}

void* copyFile(void* args) {
  char* filePath = ((char**)args)[0];
  char* copyToWithFileName = ((char**)args)[1];
  int file_from;
  struct stat sts;
  while (1) {
    file_from = open(filePath, O_RDONLY);
    if (file_from == -1) {
      if (errno == EMFILE) {
        sleep(2);
        continue;
      }
      printf("Can't open file to read.\n");
      free(filePath);
      free(copyToWithFileName);
      free(args);
      pthread_exit(NULL);
    }
    break;
  }
  if (fstat(file_from, &sts) == -1) {
    printf("Can't get open file stat.\n");
    free(filePath);
    free(copyToWithFileName);
    free(args);
    pthread_exit(NULL);
  }

  int file_to;
  while (1) {
    file_to = open(copyToWithFileName, O_CREAT | O_EXCL | O_WRONLY,
                   sts.st_mode & 0777);
    if (file_to == -1) {
      if (errno == EMFILE) {
        sleep(2);
        continue;
      }
      printf("Can't create file to write.\n");
      close(file_from);
      free(filePath);
      free(copyToWithFileName);
      free(args);
      pthread_exit(NULL);
    }
    break;
  }

  int read_bytes = 0;
  char* buf = (char*)malloc(sizeof(char) * MAX_BYTES_TO_RW);
  do {
    // todo error handle
    read_bytes = read(file_from, buf, MAX_BYTES_TO_RW);
    if (read_bytes == -1) {
      printf("Can't read.\n");
      break;
    }
    if (write(file_to, buf, read_bytes) == -1) {
      printf("Can't write.\n");
      break;
    }
  } while (read_bytes > 0);

  close(file_from);
  close(file_to);
  free(filePath);
  free(copyToWithFileName);
  free(args);
  free(buf);

  pthread_exit(NULL);
}

char* getLastNameInPath(char* path) {
  int str_len = strlen(path);
  int slashInd = str_len - 1;
  while (path[slashInd] != '/' && slashInd >= 0) {
    slashInd--;
  }
  if (slashInd < 0) {
    return NULL;
  }
  char* name = (char*)malloc(sizeof(char) * str_len - slashInd + 1);
  strcpy(name, path + slashInd + 1);
  return name;
}

int addNameToPathWithSlash(char* path, char* name, int max_len_with_nul) {
  if (strlen(path) + 1 + strlen(name) >= max_len_with_nul) {
    return -1;
  }
  strcat(path, "/");
  strcat(path, name);
  return 0;
}

int addNameToPathWithoutSlash(char* path, char* name, int max_len_with_nul) {
  if (strlen(path) + strlen(name) >= max_len_with_nul) {
    return -1;
  }
  strcat(path, name);
  return 0;
}

char* extendStringToMaxLenAndFreeOld(char* str, int max_len_with_nul) {
  char* new_str = (char*)malloc(sizeof(char) * max_len_with_nul);
  strcpy(new_str, str);
  free(str);
  return new_str;
}

int addSlashToEnd(char* str, int max_len_with_nul) {
  if (strlen(str) + 1 >= max_len_with_nul) {
    return -1;
  }
  strcat(str, "/");
  return 0;
}

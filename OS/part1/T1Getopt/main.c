#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <unistd.h>

#define BUF_SIZE 100

extern char** environ;

char** GetReverseArgv(char** argv, int argc);
void PrintLimit();
void PrintIds();
void SetLeader();
void PrintProcessIds();
void PrintCoreSize();
void PrintCwd();
void PrintEnviron();
void SetCoreLimit(char* limit);
void SetLimit(char* limit);
void ParseEnvVar(char* arg, char* o_name, char* o_val, int max_name_size,
                 int max_val_size);
int IsDigit(char* word);

int main(int argc, char** argv) {
  const char options[] = "ispuU:cC:dvV:"; /* valid options */
  char** reversed_argv = GetReverseArgv(argv, argc);
  char opt;
  while ((opt = getopt(argc, reversed_argv, options)) != EOF) {
    switch (opt) {
      case 'i':
        PrintIds();
        break;
      case 's':
        SetLeader();
        break;
      case 'p':
        PrintProcessIds();
        break;
      case 'u':
        PrintLimit();
        break;
      case 'U':
        if (!IsDigit(optarg)) {
          fprintf(stderr, "Wrong value for ulimit");
        } else {
          SetLimit(optarg);
        }
        break;
      case 'c':
        PrintCoreSize();
        break;
      case 'C':
        if (!IsDigit(optarg)) {
          fprintf(stderr, "Wrong value for ulimit");
        } else {
          SetCoreLimit(optarg);
        }
        break;
      case 'd':
        PrintCwd();
        break;
      case 'v':
        PrintEnviron();
        break;
      case 'V': {
        char name[BUF_SIZE];
        char val[BUF_SIZE];
        ParseEnvVar(optarg, name, val, BUF_SIZE, BUF_SIZE);
        if (setenv(name, val, 1) != 0) {
          fprintf(stderr, "Set env var.\n");
          exit(1);
        }
      } break;

      default:
        fprintf(stderr, "Incorrect options.\n");
        free(reversed_argv);
        exit(1);
    }
  }
  free(reversed_argv);
  return 0;
}

char** GetReverseArgv(char** argv, int argc) {
  char** reversed_argv = (char**)malloc(sizeof(char*) * argc);
  argc--;
  reversed_argv[0] = argv[0];
  for (int i = 0; i < argc; i++) {
    reversed_argv[i + 1] = argv[argc - i];
  }
  return reversed_argv;
}

void PrintLimit() {
  struct rlimit file_lim;
  if (getrlimit(RLIMIT_FSIZE, &file_lim) == 0) {
    printf("\tMaximum process file size: %lu\n", file_lim.rlim_max);
  } else {
    fprintf(stderr, "Can't get file limit.\n");
    exit(1);
  }
}

void PrintIds() {
  printf(
      "\tReal user id: %d\n\tReal group id: %d\n\tEffective user id: "
      "%d\n\tEffective group id: %d\n",
      getuid(), getgid(), geteuid(), geteuid());
}

void SetLeader() { setpgid(0, getpgrp()); }

void PrintProcessIds() {
  printf(
      "\tReal user id: %d\n\tReal group id: %d\n\tEffective user id: "
      "%d\n\tEffective group id: %d\n\tProcess id: %d\n\tParent process id: "
      "%d\n\tProcess group id: "
      "%d\n",
      getuid(), getgid(), getegid(), geteuid(), getpid(), getppid(),
      getpgid(getpid()));
}

void PrintCoreSize() {
  struct rlimit core_lim;
  if (getrlimit(RLIMIT_CORE, &core_lim) == 0) {
    printf("\tProcess core file size: %lu\n", core_lim.rlim_cur);
  } else {
    fprintf(stderr, "Can't get core limit.\n");
    exit(1);
  }
}

void PrintCwd() {
  char* cwd = getcwd(NULL, 100);
  if (cwd) {
    printf("\t%s\n", cwd);
    free(cwd);
  } else {
    fprintf(stderr, "Can't print cwd.\n");
    exit(1);
  }
}

void PrintEnviron() {
  for (int i = 0; environ[i]; i++) {
    printf("%s\n", environ[i]);
  }
}

void SetCoreLimit(char* limit) {
  struct rlimit core_lim;
  if (getrlimit(RLIMIT_CORE, &core_lim) == 0) {
    core_lim.rlim_cur = atol(limit);
    if (setrlimit(RLIMIT_CORE, &core_lim) != 0) {
      fprintf(stderr, "Can't set core limit.\n");
      exit(1);
    }
  } else {
    fprintf(stderr, "Can't get core limit.\n");
    exit(1);
  }
}

void SetLimit(char* limit) {
  struct rlimit file_lim;
  if (getrlimit(RLIMIT_FSIZE, &file_lim) == 0) {
    file_lim.rlim_cur = atol(limit);
    if (setrlimit(RLIMIT_FSIZE, &file_lim) != 0) {
      fprintf(stderr, "Can't set fsize limit.\n");
      exit(1);
    }
  } else {
    fprintf(stderr, "Can't get fsize limit.\n");
    exit(1);
  }
}

int IsDigit(char* word) {
  char* p = word;
  while (*p != '\0') {
    if (*p < '0' || *p > '9') {
      if (*p != '\0') {
        printf("WRONG CHAR %c\n", *p);
        return 0;
      }
    }
    p++;
  }
  return 1;
}

void ParseEnvVar(char* arg, char* o_name, char* o_val, int max_name_size,
                 int max_val_size) {
  int i;
  for (i = 0; arg[i] != '=' && arg[i] != '\0'; i++) {
  }
  if (arg[i] == '\0') {
    fprintf(stderr, "Incorrect env var format. Try \"name=val\".\n");
    exit(1);
  }
  arg[i] = '\0';
  int name_size = strlen(arg);
  int val_size = strlen(arg + i + 1);
  if (name_size >= max_name_size || val_size >= max_val_size) {
    fprintf(stderr, "Env var name (or val) is too long\n");
    exit(1);
  }
  strcpy(o_name, arg);
  strcpy(o_val, arg + i + 1);
}
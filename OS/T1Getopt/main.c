#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <unistd.h>

extern char** environ;

char** GetReverseArgv(char** argv, int argc);
void PrintLimit();
void PrintIds();
void SetLeader();
void PrintProcessIds();
void PrintCoreSize();
void PrintCwd();
void PrintEnviron();
void SetCoreLimit();
int IsDigit(char* word);

int main(int argc, char* argv[]) {
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
        }
        break;
      case 'c':
        PrintCoreSize();
        break;
      case 'C':
        if (!IsDigit(optarg)) {
          fprintf(stderr, "Wrong value for ulimit");
        }
        SetCoreLimit(optarg);
        break;
      case 'd':
        PrintCwd();
        break;
      case 'v':
        PrintEnviron();
        break;
      case 'V':

        break;

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
    printf("\tMaximum process file size: %lu\n", file_lim.rlim_cur);
  } else {
    fprintf(stderr, "Can't get file limit.\n");
    exit(1);
  }
}

void PrintIds() {
  printf(
      "\tReal user id: %d\n\tReal group id: %d\n\tEffective user id: "
      "%d\n\tEffective group id: %d\n",
      getuid(), getgid(), getegid(), geteuid());
}

void SetLeader() {
  setpgid(0, getpgrp());
}

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

void SetCoreLimit(char* new_lim) {
  struct rlimit core_lim;
  if (getrlimit(RLIMIT_CORE, &core_lim) == 0) {
  } else {
    fprintf(stderr, "Can't get core limit.\n");
    exit(1);
  }
}

int IsDigit(char* word) {
  char* p = word;
  while (*p != '\0') {
    if (*p <= '0' || *p >= '9') {
      return 0;
    }
    p++;
  }
  return 1;
}

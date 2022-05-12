#include <grp.h>
#include <libgen.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void PrintType(struct stat file_stat) {
  if (S_ISREG(file_stat.st_mode)) {
    printf("%s", "-");
  } else if (S_ISDIR(file_stat.st_mode)) {
    printf("%s", "d");
  } else {
    printf("%s", "?");
  }
}

void PrintRights(struct stat file_stat) {
  if (S_IRUSR & file_stat.st_mode) {
    printf("%s", "r");
  } else {
    printf("%s", "-");
  }
  if (S_IWUSR & file_stat.st_mode) {
    printf("%s", "w");
  } else {
    printf("%s", "-");
  }
  if (S_IXUSR & file_stat.st_mode) {
    printf("%s", "x");
  } else {
    printf("%s", "-");
  }

  if (S_IRGRP & file_stat.st_mode) {
    printf("%s", "r");
  } else {
    printf("%s", "-");
  }
  if (S_IWGRP & file_stat.st_mode) {
    printf("%s", "w");
  } else {
    printf("%s", "-");
  }
  if (S_IXGRP & file_stat.st_mode) {
    printf("%s", "x");
  } else {
    printf("%s", "-");
  }

  if (S_IROTH & file_stat.st_mode) {
    printf("%s", "r");
  } else {
    printf("%s", "-");
  }
  if (S_IWOTH & file_stat.st_mode) {
    printf("%s", "w");
  } else {
    printf("%s", "-");
  }
  if (S_IXOTH & file_stat.st_mode) {
    printf("%s", "x");
  } else {
    printf("%s", "-");
  }
}

void PrintUser(struct stat file_stat) {
  struct passwd *usr = getpwuid(file_stat.st_uid);
  if (usr == NULL) {
    printf("ERROR");
    return;
  }
  printf("%s", usr->pw_name);
}

void PrintGroup(struct stat file_stat) {
  struct group *grp = getgrgid(file_stat.st_gid);
  if (grp == NULL) {
    printf("ERROR");
    return;
  }
  printf("%s", grp->gr_name);
}

void PrintSize(struct stat file_stat) {
  if (S_ISREG(file_stat.st_mode)) {
    printf("%ld", file_stat.st_size);
  } else {
    printf("%c", '\t');
  }
}

void PrintTime(struct stat file_stat) {
  char *name = ctime(&(file_stat.st_mtim.tv_sec));
  if (name == NULL) {
    printf("%s", "ERROR");
    return;
  }
  int index = strlen(name) - 1;
  name[index] = '\0';
  printf("%s", name);
}

void PrintName(char *path) { printf("%s", basename(path)); }

int main(int argc, char **argv) {
  struct stat file_stat;
  for (int i = 1; i < argc; i++) {
    if (stat(argv[i], &file_stat) == -1) {
      continue;
    }
    PrintType(file_stat);
    PrintRights(file_stat);
    printf("%c", ' ');
    PrintUser(file_stat);
    printf("%c", ' ');
    PrintGroup(file_stat);
    printf("%c", ' ');
    PrintSize(file_stat);
    printf("%c", ' ');
    PrintTime(file_stat);
    printf("%c", ' ');
    PrintName(argv[i]);
    printf("%c", '\n');
  }
}

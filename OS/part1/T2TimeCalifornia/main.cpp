#include <stdio.h>
#include <stdlib.h>
#include <time.h>
extern char *tzname[];

main() {
  time_t now;
  struct tm *sp;
  setenv("TZ", "America/Tijuana", 1);
  (void)time(&now);

  printf("%s", ctime(&now));

  sp = localtime(&now);
  printf("%d/%d/%02d %d:%02d %s\n", sp->tm_mon + 1, sp->tm_mday,
         sp->tm_year + 1900, sp->tm_hour, sp->tm_min, tzname[sp->tm_isdst]);
  exit(0);
}
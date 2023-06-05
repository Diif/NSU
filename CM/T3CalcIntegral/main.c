#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long double calculateFun(long double x) { return expl(x); }

long double TrapezoidalMethod(long double a, long double b, int n,
                              long double (*fun)(long double)) {
  int sign = 1;
  if (b < a) {
    sign = -1;
    long double buf = a;
    a = b;
    b = buf;
  }
  long double sum = 0;
  long double step = (b - a) / (n - 1);
  long double coef = step / 2;
  long double x1 = a, x2 = a + step;
  for (int i = 1; i < n; i++) {
    sum += (fun(x1) + fun(x2));
    x1 = x2;
    x2 += step;
  }
  return sum * sign * coef;
}

long double SimpsonMethod(long double a, long double b, int n,
                          long double (*fun)(long double)) {
  int sign = 1;
  if (b < a) {
    sign = -1;
    long double buf = a;
    a = b;
    b = buf;
  }
  long double sum = 0;
  long double step = (b - a) / (n - 1);
  long double coef = step / 6;
  long double x1 = a, x2 = x1 + step;
  for (int i = 1; i < n; i++) {
    sum += fun(x1) + 4 * fun((x1 + x2) / 2) + fun(x2);
    x1 = x2;
    x2 += step;
  }
  return sum * sign * coef;
}

void printK(long double a, long double b, int n1, int n2) {
  printf("\nFun e^x from %Lf to %Lf\n", a, b);
  long double I = expl(b) - expl(a);
  long double part11 = TrapezoidalMethod(a, b, n1, expl) - I;
  long double part12 = TrapezoidalMethod(a, b, n1 * 2 - 1, expl) - I;

  long double part21 = TrapezoidalMethod(a, b, n2, expl) - I;
  long double part22 = TrapezoidalMethod(a, b, n2 * 2 - 1, expl) - I;

  printf("Trapezoidal miss: %Lf(0.5n=%d), %Lf(0.5n=%d)\n",
         log2l(fabs(part11 / part12)), n1, log2l(fabs(part21 / part22)), n2);

  part11 = SimpsonMethod(a, b, n1, expl) - I;
  part12 = SimpsonMethod(a, b, n1 * 2 - 1, expl) - I;

  part21 = SimpsonMethod(a, b, n2, expl) - I;
  part22 = SimpsonMethod(a, b, n2 * 2 - 1, expl) - I;

  printf("Simpson miss: %Lf(0.5n=%d), %Lf(0.5n=%d)\n",
         log2l(fabs(part11 / part12)), n1, log2l(fabs(part21 / part22)), n2);
}

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("Meh. Enter a,b,n.\n");
    return 1;
  }

  long double a = strtod(argv[1], NULL);
  long double b = strtod(argv[2], NULL);
  int n = atoi(argv[3]);

  printf("Args: a:%Lf, b:%Lf, n:%d\nSimpson: %Lf\nTrapezoidal: %Lf\n", a, b, n,
         SimpsonMethod(a, b, n, calculateFun),
         TrapezoidalMethod(a, b, n, calculateFun));

  printK(3, 4, 51, 101);
  printK(3, 4, 101, 201);
}
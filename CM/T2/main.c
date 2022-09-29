#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double calculateFun(double x) { return x * x - 5; }

double calculateDerivative(double x) { return 2 * x; }

double getNextXNewton(double x) {
  return x - (calculateFun(x) / calculateDerivative(x));
}

double getNextXOneTangent(double x, double x0) {
  return x - (calculateFun(x) / calculateDerivative(x0));
}

double getNextXSecant(double x, double x_prev) {
  return x - calculateFun(x) *
                 ((x - x_prev) / (calculateFun(x) - calculateFun(x_prev)));
}

int main() {
  double x0 = 3;
  double x_newton = x0;
  double x_one = x0;
  double x_sec;
  double x_prev = x0;
  int first_loop = 1;

  double answer = sqrt(5);
  printf("Sqrt(5): %lf, x0: %lf\n", answer, x0);
  for (int i = 0; i < 3; i++) {
    printf("\n\t###Iter %d\n", i + 1);
    x_newton = getNextXNewton(x_newton);
    if (first_loop == 1) {
      x_sec = x_newton;
      first_loop = 0;
    }
    x_one = getNextXOneTangent(x_one, x0);
    printf("Secant: %lf\n\tDiff: %lf\n", x_sec, fabs(answer - x_sec));
    if (i < 2) {
      double buf = x_sec;
      x_sec = getNextXSecant(x_sec, x_prev);
      x_prev = buf;
    }
    printf("Newton: %lf\n\tDiff: %lf\n", x_newton, fabs(answer - x_newton));
    printf("OneTangent: %lf\n\tDiff: %lf\n", x_one, fabs(answer - x_one));
  }
}
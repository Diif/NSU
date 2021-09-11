#include <sys/times.h>
#include <unistd.h>

#include <cmath>
#include <iostream>

using namespace std;

double MathFunction(double x);
double CalculateIntegral(int num_of_interval);

int main(int, char**) {
  struct tms start, end;
  long clocks_per_sec = sysconf(_SC_CLK_TCK);
  long clocks;
  cout.precision(20);

  times(&start);
  cout << CalculateIntegral(100000000) << endl;
  times(&end);

  clocks = end.tms_utime - start.tms_utime;
  cout << "sec: " << (double)clocks / clocks_per_sec << endl;
  return 0;
}

double CalculateIntegral(int num_of_interval) {
  double a = 0;
  double b = M_PI;
  double x = a;
  double step = M_PI / num_of_interval;
  double sum = 0;
  double len_coeff = (b - a) / num_of_interval;
  for (int i = 0; i < num_of_interval; i++) {
    sum += (MathFunction(x) + MathFunction(x + step)) / 2;
    x += step;
  }
  return sum * len_coeff;
}

double MathFunction(double x) { return sin(x) * exp(x); }

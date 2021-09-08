#include <cmath>
#include <iostream>

double MathFunction(double x);
double CalculateIntegral(int num_of_interval);

int main(int, char**) { std::cout << CalculateIntegral(10); }

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

// #########################
// Goofy integral calculator
// #########################

#include <cmath>
#include <iomanip>
#include <iostream>

// e^x
double f(const double &x) { return std::exp(x); }

// This function returns calculated definite integral of e^x
//	using trapezoidal rule
double TrapezoidalRule(const double &a, const double &b, const double &step) {
  double definite_integral = 0;

  for (double x = a; x < b; x += step) {
    // Bounds of the trapeze
    double x1 = x;
    double x2 = x + step;

    // Area of the trapeze
    double step_trapeze = step * (f(x1) + f(x2)) / 2;

    definite_integral += step_trapeze;
  }

  return definite_integral;
}

// This function returns calculated definite integral of e^x
//	using Simpson's rule
double SimpsonsRule(const double &a, const double &b, const double &step) {
  double definite_integral = 0;

  for (double x = a; x < b; x += step) {
    // Bounds of the segment
    double x1 = x;
    double x2 = x + step;

    // Area of that segment
    double step_segment = step * (f(x1) + 4 * f((x1 + x2) / 2) + f(x2)) / 6;

    definite_integral += step_segment;
  }

  return definite_integral;
}

double get_trapeze_error_power(const double &a, const double &b,
                               const double &step) {
  double true_integral = f(b) - f(a);

  double full_step_integral = TrapezoidalRule(a, b, step);
  double half_step_integral = TrapezoidalRule(a, b, step / 2);

  double full_step_error = full_step_integral - true_integral;
  double half_step_error = half_step_integral - true_integral;

  return std::log2(full_step_error / half_step_error);
}

double get_simpson_error_power(const double &a, const double &b,
                               const double &step) {
  double true_integral = f(b) - f(a);

  double full_step_integral = SimpsonsRule(a, b, step);
  double half_step_integral = SimpsonsRule(a, b, step / 2);

  double full_step_error = std::abs(full_step_integral - true_integral);
  double half_step_error = std::abs(half_step_integral - true_integral);

  return std::log2(full_step_error / half_step_error);
}

int main() {
  double a = 0;
  double b = 1;

  double h1 = 0.005;
  double h2 = 1e-3;

  // Set precision of the output
  std::cout << std::fixed << std::setprecision(9);

  std::cout << "True integral:\n\t" << f(b) - f(a) << "\n";

  std::cout << "Integration from " << a << " to " << b
            << " with step = 0.01:\n";

  std::cout << "\tTrapeze: " << TrapezoidalRule(a, b, h1) << "\n";
  std::cout << "\tSimpson: " << SimpsonsRule(a, b, h1) << "\n";

  std::cout << "Integration from " << a << " to " << b
            << " with step = 0.001:\n";

  std::cout << "\tTrapeze: " << TrapezoidalRule(a, b, h2) << "\n";
  std::cout << "\tSimpson: " << SimpsonsRule(a, b, h2) << "\n";

  // Integration steps are changed fro error's power computation.
  // Because "double" is too imprecise for these calculations.

  // Trapezoidal rule error
  std::cout
      << "Power of the trapezoidal rule error with integration step = 0.1:\n";
  std::cout << "\t" << get_trapeze_error_power(a, b, 0.005) << "\n";
  std::cout
      << "Power of the trapezoidal rule error with integration step = 0.01:\n";
  std::cout << "\t" << get_trapeze_error_power(a, b, 0.0025) << "\n";

  // Simpson's rule error
  std::cout
      << "Power of the Simpson's rule error with integration step = 0.1:\n";
  std::cout << "\t" << get_simpson_error_power(a, b, 0.005) << "\n";
  std::cout
      << "Power of the Simpson's rule error with integration step = 0.01:\n";
  std::cout << "\t" << get_simpson_error_power(a, b, 0.0025) << "\n";

  return 0;
}
#include <sys/times.h>
#include <unistd.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

double MathFunction(double x);
double CalculateIntegral(long long num_of_intervals);
void MakeNMeasurementsAndPrint(int count_of_measurements, int num_of_intervals);
double MakeMeasurementAndGetTimeSec(long long num_of_intervals);
const int kNFor40Secs = 600000000;

int main(int argc, char** argv) {
  MakeNMeasurementsAndPrint(1, kNFor40Secs);

  return 0;
}

void MakeNMeasurementsAndPrint(int count_of_measurements,
                               int num_of_intervals) {
  double step;
  double cur_stage;
  double edge;
  step = 1;
  cur_stage = step;
  edge = 1 + (step / 2);
  for (double coeff = cur_stage; coeff <= edge; coeff += step) {
    double time = MakeMeasurementAndGetTimeSec(num_of_intervals * coeff);
    cout << "time: " << time << endl;
  }
}

double MakeMeasurementAndGetTimeSec(long long num_of_intervals) {
  struct tms start, end;
  long long clocks_per_sec = sysconf(_SC_CLK_TCK);
  long long clocks;
  double result;
  cout << "Num of intervals: " << num_of_intervals << endl << "res:  ";
  times(&start);
  result = CalculateIntegral(num_of_intervals);
  times(&end);
  cout.precision(5);
  cout << result << endl;
  clocks = end.tms_utime - start.tms_utime;
  return (double)clocks / clocks_per_sec;
}

double CalculateIntegral(long long num_of_intervals) {
  double a = 0;
  double b = M_PI;
  double x = a;
  double step = M_PI / num_of_intervals;
  double sum = 0;
  double len_coeff = (b - a) / num_of_intervals;
  for (int i = 0; i < num_of_intervals; i++) {
    sum += (MathFunction(x) + MathFunction(x + step)) / 2;
    x += step;
  }
  return sum * len_coeff;
}

double MathFunction(double x) { return sin(x) * exp(x); }

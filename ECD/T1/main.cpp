#include <sys/times.h>
#include <unistd.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

double MathFunction(double x);
double CalculateIntegral(long long num_of_intervals);
void MakeNMeasurementsAndPrintToFile(int count_of_measurements,
                                     int num_of_intervals);
double MakeMeasurementAndGetTimeSec(long long num_of_intervals);
void WriteDoubleToTable(double data, string file_name);
void WriteNewRowToTable(string file_name);
void WriteTestedValuesToFile(int count_of_measurements, string file_name);
const string kOutFile = "outtime.csv";
const string kOutFileValues = "outval.csv";
const int kNFor40Secs = 600000000;

int main(int argc, char** argv) {
  int num_of_intervals;
  int print_tested_value = 0;

  if (argc >= 2) {
    num_of_intervals = stoi(argv[1]);
    if (num_of_intervals == 0) {
      num_of_intervals = kNFor40Secs;
    }
  } else {
    num_of_intervals = kNFor40Secs;
  }

  if (argc >= 4) {
    print_tested_value = 1;
  }

  if (argc >= 3) {
    int count_of_measurements = stoi(argv[2]);
    if (print_tested_value) {
      WriteTestedValuesToFile(count_of_measurements, kOutFile);
    }
    MakeNMeasurementsAndPrintToFile(count_of_measurements, num_of_intervals);
  } else {
    MakeNMeasurementsAndPrintToFile(1, num_of_intervals);
  }

  return 0;
}

void WriteTestedValuesToFile(int count_of_measurements, string out_file) {
  double step;
  double cur_stage;
  double edge;
  if (count_of_measurements > 1) {
    step = (double)2 / (double)count_of_measurements;
    cur_stage = step;
    edge = 2 + (step / 2);
  } else {
    step = 1;
    cur_stage = step;
    edge = 1 + (step / 2);
  }
  for (double i = cur_stage; i <= edge; i += step) {
    WriteDoubleToTable(i, out_file);
  }
  WriteNewRowToTable(out_file);
}

void MakeNMeasurementsAndPrintToFile(int count_of_measurements,
                                     int num_of_intervals) {
  double step;
  double cur_stage;
  double edge;
  if (count_of_measurements > 1) {
    step = (double)2 / (double)count_of_measurements;
    cur_stage = step;
    edge = 2 + (step / 2);
  } else {
    step = 1;
    cur_stage = step;
    edge = 1 + (step / 2);
  }
  for (double coeff = cur_stage; coeff <= edge; coeff += step) {
    double time = MakeMeasurementAndGetTimeSec(num_of_intervals * coeff);
    WriteDoubleToTable(time, kOutFile);
  }
  WriteNewRowToTable(kOutFile);
}

double MakeMeasurementAndGetTimeSec(long long num_of_intervals) {
  struct tms start, end;
  long long clocks_per_sec = sysconf(_SC_CLK_TCK);
  long long clocks;
  double result;
  cout << num_of_intervals << "    res:  ";
  times(&start);
  result = CalculateIntegral(num_of_intervals);
  times(&end);
  WriteDoubleToTable(result, kOutFileValues);
  cout.precision(5);
  cout << result << endl;
  clocks = end.tms_utime - start.tms_utime;
  return (double)clocks / clocks_per_sec;
}

void WriteDoubleToTable(double data, string file_name) {
  ofstream out_file;
  out_file.open(file_name, ios::app);
  if (file_name == kOutFileValues) {
    out_file << std::fixed << std::setprecision(8) << data << ',';
  } else {
    out_file << std::fixed << std::setprecision(3) << data << ',';
  }
  out_file.close();
}
void WriteNewRowToTable(string file_name) {
  ofstream out_file;
  out_file.open(file_name, ios::app);
  out_file << endl;
  out_file.close();
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

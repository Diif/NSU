#include <ctime>
#include <iostream>

#include "opencv2/opencv.hpp"

static bool was_start = 0;
static bool was_end = 0;

int main(int, char**) {
  std::string WindowName{"Webcam"};
  cv::VideoCapture camera(0);
  if (!camera.isOpened()) {
    std::cerr << "ERROR: Could not open camera" << std::endl;
    return 1;
  }

  cv::namedWindow(WindowName);
  cv::Mat frame;

  size_t counter = 0;
  clock_t start, end, prog_start, prog_end;
  double result = 0;
  prog_start = clock();
  while (1) {
    start = clock();
    counter++;

    camera.read(frame);
    frame.convertTo(frame, -1, 0.5, 0);
    erode(frame, frame,
          cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
    cv::imshow("Webcam", frame);

    end = clock();
    result += (static_cast<double>(end) - start) / CLOCKS_PER_SEC;
    if (cv::waitKey(10) >= 0) break;
  }
  prog_end = clock();
  double total_time =
      (static_cast<double>(prog_end) - prog_start) / CLOCKS_PER_SEC;
  std::cout << "Frames:" << counter << std::endl
            << "Frames per sec:" << counter / total_time << std::endl
            << "Time in secs (without waiting) to process 1 frame: "
            << result / counter << std::endl
            << "Total work time: " << total_time << std::endl
            << "Lost time: " << result << std::endl;
  return 0;
}
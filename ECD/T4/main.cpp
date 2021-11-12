#include <ctime>
#include <iostream>

#include "lusb0_usb.h"
#include "opencv2/opencv.hpp"

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
  clock_t start, end;
  double time_to_read = 0;
  double time_to_display = 0;
  double time_to_process = 0;
  double total_time = 0;
  while (1) {
    counter++;  // total frames

    start = clock();
    camera.read(frame);
    end = clock();
    time_to_read += (static_cast<double>(end) - start) / CLOCKS_PER_SEC;

    /*start = clock();
    frame.convertTo(frame, -1, 0.5, 0);
    frame.convertTo(frame, -1, 1.5, 0);
    frame.convertTo(frame, -1, 0.5, 0);
    frame.convertTo(frame, -1, 2, 0);
    frame.convertTo(frame, -1, 0.5, 0);
    frame.convertTo(frame, -1, 2, 0);
    frame.convertTo(frame, -1, 0.5, 0);
    frame.convertTo(frame, -1, 2, 0);
    erode(frame, frame,
          cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
    end = clock();*/
    time_to_process += (static_cast<double>(end) - start) / CLOCKS_PER_SEC;

    start = clock();
    cv::imshow("Webcam", frame);
    end = clock();
    time_to_display += (static_cast<double>(end) - start) / CLOCKS_PER_SEC;
    if (cv::waitKey(10) >= 0) break;
  }
  total_time = time_to_read + time_to_process + time_to_display;

  std::cout << "Frames:" << counter << std::endl
            << "Frames per sec:" << counter / total_time << std::endl
            << "Total time: " << total_time << " - 100%" << std::endl
            << "READ time: " << time_to_read << " - "
            << time_to_read / total_time * 100 << "%" << std::endl
            << "PROCESS time: " << time_to_process << " - "
            << time_to_process / total_time * 100 << "%" << std::endl
            << "DISPLAY time: " << time_to_display << " - "
            << time_to_display / total_time * 100 << "%" << std::endl;
  return 0;
}
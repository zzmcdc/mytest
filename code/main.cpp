//
// Created by zhao on 18-11-17.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <random>
#include <cmath>
#include"omp.h"
#include "process.h"
#define PI 3.14159265
#include "process.h"
using namespace std;
using namespace Vison;

//#define DEBUG false


int main()
{
    string file_path = R"(E:\project\circle\0-2.bmp)";
    cv::Mat img = cv::imread(file_path);
	Vison::ImgProcess process;
	process.set_image(img);
	process.compute();
	cv::Mat result = process.get_view_image();
	cv::imshow("img", result);
	cv::waitKey(0);
}

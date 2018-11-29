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
#define PI 3.14159265
#include "process.h"
using namespace std;
using namespace Vison;

//#define DEBUG false








int main()
{
    string file_path = R"(E:\project\JieGuoBMP\01.bmp)";
    cv::Mat img = cv::imread(file_path);
    cv::Size size = img.size();
    cv::Mat img_gray(size,CV_8UC1);
    cv::cvtColor(img,img_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(img_gray, img_gray,cv::Size(17,17),1.4,1.4);
    cv::Mat img_binary;
    cv::threshold(img_gray, img_binary, 0, 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);
    cv::Mat img_blur;
    cv::medianBlur(img_binary,img_blur,15);
#ifdef DEBUG
    show_image("img_blur", img_blur);
#endif
//    cv::Mat img_canny;
//    cv::Canny(img_blur,img_canny,30,100);
//#ifdef DEBUG
//    show("canny",img_canny);
//#endif


    vector<vector<cv::Point>> contours;

    cv::findContours(img_blur, contours, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    vector<std::pair<int, double> > area;
    for(int i =0; i<contours.size(); ++i)
        area.emplace_back(pair<int,double>(i,cv::contourArea(contours[i])));
    sort(area.begin(), area.end(),[](pair<int,double> a, pair<int,double> b) -> bool { return a.second > b.second;});
    for(int i = 0;i<area.size();++i) {
      cout << area[i].first << "  " << area[i].second << "  " << contours[area[i].first].size() << endl;
    }

      vector<LineInfo> result = cal_nearst(img, contours[2],contours[3]);
      double dis = result[0].distance;
      int index = 0;
      for(int i = 1;i< result.size();++i)
      {
        if(result[i].distance > dis)
        {
          dis = result[i].distance;
          index = i;
        }
      }

        cv::circle(img,result[index].start,4,cv::Scalar(255,0,0));
      cv::circle(img,result[index].end, 4,cv::Scalar(0,0,255));
      cv::line(img,result[index].start,result[index].end,cv::Scalar(0,0,255),4);
      show_image("img",img);
//    for(auto item:result)
//    {
//      cv::circle(img,item.start,2,cv::Scalar(255,0,0));
//      cv::circle(img,item.end, 2,cv::Scalar(0,0,255));
//      cv::line(img,item.start,item.end,cv::Scalar(0,0,255),2);
//      show_image("img",img);
//    }
}

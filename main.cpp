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

using namespace std;

//#define DEBUG false

void show_image(const string &name, const cv::InputArray &img)
{
  cv::namedWindow(name);
  cv::imshow(name,img);
  int z = cv::waitKey();
  if (z==27)
    cv::destroyAllWindows();
}

int choice(size_t range)
{
  return int(random()%range);
}

struct LineInfo
{
  cv::Point start;
  cv::Point end;
  double distance;
  double angle;
};

struct Direction
{
  double x;
  double y;
  Direction() = default;
  Direction(const cv::Point &start, const cv::Point &end)
  {
    x = end.x - start.x;
    y = end.y - start.y;
  }
  double operator*(const Direction &in)
  {
    return x*in.x + y*in.y;
  }
  void set(const cv::Point &start, const cv::Point &end)
  {
    this->x = end.x - start.x;
    this->y = end.y - start.y;
  }

};

int  find_pair(cv::Mat img, const cv::Point &point, const Direction &orig, const vector<cv::Point> &point_set) {
  cv::Point left_point, right_point;
  // search right point
  int size = point_set.size();
  int index = 0;
  int left_index, right_index;
  double flag = 100;
  do {
    left_index = choice(size);
    flag = Direction(point, point_set[left_index]) * orig;
  } while (flag > 0);

  flag = -100;
  do {
    right_index = choice(size);
    flag = Direction(point, point_set[right_index]) * orig;

  } while (flag < 0);
  int mid  ;
  while ((abs((right_index - left_index) - size)%size) > 1) {
#ifdef DEBUG
    cv::Mat dst ;
    img.copyTo(dst);
#endif



    int mid_a = ((right_index + left_index) / 2) % size;
    int mid_b = ((right_index + left_index + size) / 2) % size;
    int len_a = (point_set[mid_a].x - point.x) * (point_set[mid_a].x - point.x) + \
    (point_set[mid_a].y - point.y) * (point_set[mid_a].y - point.y);
    int len_b = (point_set[mid_b].x - point.x) * (point_set[mid_b].x - point.x) + \
    (point_set[mid_b].y - point.y) * (point_set[mid_b].y - point.y);
    if (len_a > len_b) {
      mid = mid_b;
    }
    else
    {
      mid = mid_a;
    }
#ifdef DEBUG
    cout<<"left: "<<left_index<<" right:"<<right_index<<endl;
    cv::line(dst,point,point_set[left_index],cv::Scalar(0,0,255),2);
    cv::line(dst,point,point_set[right_index],cv::Scalar(255,0,0),2);
    cv::circle(dst,point_set[mid_a],4,cv::Scalar(0,0,255));
    cv::circle(dst, point_set[mid_b],4, cv::Scalar(0,0,255));
    show_image("img",dst);
#endif
    flag = Direction(point, point_set[mid]) * orig;
    if (flag < 0)
      left_index = mid;
    else
      right_index = mid;
  }
  return mid;
}

vector<LineInfo> cal_nearst(cv::Mat img ,const vector<cv::Point> &outer, const vector<cv::Point> &inner)
{
  size_t size = outer.size();
  vector<LineInfo> result;

//#pragma omp parallel for num_threads(4)
  for(size_t i = 0; i< size; i=i+5)
  {
    // back 5 points
    int smooth_start_x = 0 ;

    int smooth_start_y = 0;

    int smooth_end_x = 0;

    int smooth_end_y = 0;

    for(int c=1; c<=40;c++)
    {
      smooth_start_x += outer[(i+size -c)%size].x;
      smooth_start_y += outer[(i+size -c)%size].y ;
      smooth_end_x += outer[(i+size +c)%size].x  ;
      smooth_end_y += outer[(i+size +c)%size].y ;
    }


    Direction orig(cv::Point(smooth_start_x/40, smooth_start_y/40), cv::Point(smooth_end_x/40, smooth_end_y/40));
    int index = find_pair(img, outer[i],orig,inner);
    LineInfo info;
    info.start=outer[i];
    info.end = inner[index];
    double distance = (outer[i].x - inner[index].x)*((outer[i].x - inner[index].x)) +
                      (outer[i].y - inner[index].y)*((outer[i].y - inner[index].y)) ;
    info.distance = sqrt(distance);
    if((outer[i].x - inner[index].x) ==0)
      info.angle = 90;
    else
      info.angle = atan((outer[i].y - inner[index].y)/(outer[i].x - inner[index].x)) *180/PI;
    result.push_back(info);
  }
  return  result;

}



int main()
{
    string file_path = string("/home/zhao/work/JieGuoBMP/01.bmp");
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

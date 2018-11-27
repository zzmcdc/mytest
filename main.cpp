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
using namespace std;

#define DEBUG true

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
  double angle;
};

struct Direction
{
  int x;
  int y;
  Direction() = default;
  Direction(const cv::Point &start, const cv::Point &end)
  {
    x = end.x - start.x;
    y = end.y - start.y;
  }
  int operator*(const Direction &in)
  {
    return x*in.x + y*in.y;
  }
  void set(const cv::Point &start, const cv::Point &end)
  {
    this->x = end.x - start.x;
    this->y = end.y - start.y;
  }

};

int  find_pair(cv::Mat img,const cv::Point &point, const cv::Point &next_point, const vector<cv::Point> &point_set) {
  cv::Point left_point, right_point;
  Direction orig(point, next_point);
  cout<<'x:'<<orig.x<<" y:"<< orig.y<<endl;
  // search right point
  int size = point_set.size();
  int index = 0;
  int left_index, right_index;
  int flag = 100;
  do {
    left_index = choice(size);
    flag = Direction(point, point_set[left_index]) * orig;
    cout<<"left direction:"<<flag<<endl;
  } while (flag > 0);

  flag = -100;
  do {
    right_index = choice(size);
    flag = Direction(point, point_set[right_index]) * orig;
    cout<<"right direction:"<<flag<<endl;

  } while (flag < 0);
  int mid  ;
  while (abs(right_index - left_index) > 1) {
    cv::Mat dst ;
    img.copyTo(dst);


    cout<<"left:"<<left_index<<"  "<<"right:"<<right_index;
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
//    cv::line(dst,point,point_set[left_index],cv::Scalar(0,0,255),2);
//    cv::line(dst,point,point_set[right_index],cv::Scalar(255,0,0),2);
//    cv::circle(dst,point_set[mid_a],4,cv::Scalar(0,0,255));
//    cv::circle(dst, point_set[mid_b],4, cv::Scalar(0,0,255));
//    show_image("img",dst);

    flag = Direction(point, point_set[mid]) * orig;
    cout<<"  flag: "<<flag<<endl;
    if (flag < 0)
      left_index = mid;
    else
      right_index = mid;
  }
  return mid;
}




int main()
{
    string file_path = string("/home/zhao/work/JieGuoBMP/0-2.bmp");
    cv::Mat img = cv::imread(file_path);
    cv::Size size = img.size();
    cv::Mat img_gray(size,CV_8UC1);
    cv::cvtColor(img,img_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(img_gray, img_gray,cv::Size(17,17),1.4,1.4);
    cv::Mat img_binary;
    cv::threshold(img_gray, img_binary, 0, 255, cv::THRESH_BINARY_INV+cv::THRESH_OTSU);
    cv::Mat img_blur;
    cv::medianBlur(img_binary,img_blur,15);
//#ifdef DEBUG
//    show_image("img_blur", img_blur);
//#endif
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

    size_t it = contours[2].size();
    for(size_t i=0;i<it;i=i+4)
    {
      cv::Point point_next((contours[2][(i+1)%it].x + contours[2][(i+2)%it].x + contours[2][(i+3)%it].x +
      contours[2][(i+4)%it].x + contours[2][(i+5)%it].x)/5,
                           (contours[2][(i+1)%it].y + contours[2][(i+2)%it].y + contours[2][(i+3)%it].y +
      contours[2][(i+4)%it].y + contours[2][(i+5)%it].y)/5);
      int index = find_pair(img, contours[2][i],point_next, contours[3]);
      cout<<"index"<<index<<endl;
      cv::line(img,contours[2][i],contours[3][index],cv::Scalar(0,0,255),1);
      show_image("img",img);
    }
}

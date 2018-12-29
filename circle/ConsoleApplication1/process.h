#pragma once
#ifndef PROCESS__H__
#define PROCESS__H__
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <opencv4/opencv2/opencv.hpp>
#include <random>
#include <cmath>
#include"omp.h"
#define PI 3.14159265

namespace Vison
{
	using namespace std;
	void show_image(const string &name, const cv::InputArray &img);
	int choice(size_t range);

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



	class ImgProcess
	{
	private:

		cv::Mat orig_image;  //保存原始图
		cv::Mat view_image;  //保存最终绘制的图片
		vector<vector<LineInfo>> line_info; //线条信息
		vector<vector<cv::Point>> contours; //轮廓信息
		vector<vector<LineInfo>> radiation; // 6条辐线信息
	public:
		ImgProcess() = default;
		void set_image(cv::Mat &img);
		void get_contours();	
		void draw_result() ;
		cv::Mat get_view_image() ;
		int  find_pair(const cv::Point &point, const Direction &orig, const vector<cv::Point> &point_set) const ; // 找点集中最近点index
		vector<LineInfo> cal_nearst(const vector<cv::Point> &outer, const vector<cv::Point> &inner) const ;  // 计算两条轮廓中所有点的信息。
		vector<LineInfo> find_radiation(const vector<LineInfo> &info);
		void compute() ;
		vector<vector<LineInfo>> get_radiation()
		{
			return radiation;
		}
	};


}

#ifndef PROCESS__H__
#define PROCESS__H__
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <random>
#include <cmath>
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

extern "C" struct Distance
	{
		double data[18];
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

		cv::Mat orig_image;  //����ԭʼͼ
		cv::Mat view_image;  //�������ջ��Ƶ�ͼƬ
		vector<vector<LineInfo>> line_info; //������Ϣ
		vector<vector<cv::Point>> contours; //������Ϣ
		vector<vector<LineInfo>> radiation; // 6��������Ϣ
	public:
		ImgProcess() = default;
		void set_image(cv::Mat &img);
		void get_contours();	
		void draw_result() ;
		cv::Mat get_view_image() ;
		int  find_pair(const cv::Point &point, const Direction &orig, const vector<cv::Point> &point_set) const ; // �ҵ㼯�������index
		vector<LineInfo> cal_nearst(const vector<cv::Point> &outer, const vector<cv::Point> &inner) const ;  // �����������������е����Ϣ��
		vector<LineInfo> find_radiation(const vector<LineInfo> &info);
		void compute() ;
		vector<vector<LineInfo>> get_radiation()
		{
			return radiation;
		}
	};


}

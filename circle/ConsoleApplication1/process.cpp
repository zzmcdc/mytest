#include "process.h"

namespace Vison
{
	void show_image(const string &name, const cv::InputArray &img)
	{
		cv::namedWindow(name);
		cv::imshow(name, img);
		int z = cv::waitKey();
		if (z == 27)
			cv::destroyAllWindows();
	}


	int choice(size_t range)
	{
		return int(rand() % range);
	}

	int  ImgProcess::find_pair(cv::Mat img, const cv::Point &point, const Direction &orig, const vector<cv::Point> &point_set) const 
	{
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
		int mid;
		while ((abs((right_index - left_index) - size) % size) > 1) {
#ifdef DEBUG
			cv::Mat dst;
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
			cout << "left: " << left_index << " right:" << right_index << endl;
			cv::line(dst, point, point_set[left_index], cv::Scalar(0, 0, 255), 2);
			cv::line(dst, point, point_set[right_index], cv::Scalar(255, 0, 0), 2);
			cv::circle(dst, point_set[mid_a], 4, cv::Scalar(0, 0, 255));
			cv::circle(dst, point_set[mid_b], 4, cv::Scalar(0, 0, 255));
			show_image("img", dst);
#endif
			flag = Direction(point, point_set[mid]) * orig;
			if (flag < 0)
				left_index = mid;
			else
				right_index = mid;
		}
		return mid;
	}

	vector<LineInfo> ImgProcess::cal_nearst(cv::Mat img, const vector<cv::Point> &outer, const vector<cv::Point> &inner) const 
	{
		size_t size = outer.size();
		vector<LineInfo> result;

		//#pragma omp parallel for num_threads(4)
		for (size_t i = 0; i< size; i = i + 5)
		{
			// back 5 points
			int smooth_start_x = 0;

			int smooth_start_y = 0;

			int smooth_end_x = 0;

			int smooth_end_y = 0;

			for (int c = 1; c <= 40;c++)
			{
				smooth_start_x += outer[(i + size - c) % size].x;
				smooth_start_y += outer[(i + size - c) % size].y;
				smooth_end_x += outer[(i + size + c) % size].x;
				smooth_end_y += outer[(i + size + c) % size].y;
			}


			Direction orig(cv::Point(smooth_start_x / 40, smooth_start_y / 40), cv::Point(smooth_end_x / 40, smooth_end_y / 40));
			int index = find_pair(img, outer[i], orig, inner);
			LineInfo info;
			info.start = outer[i];
			info.end = inner[index];
			double distance = (outer[i].x - inner[index].x)*((outer[i].x - inner[index].x)) +
				(outer[i].y - inner[index].y)*((outer[i].y - inner[index].y));
			info.distance = sqrt(distance);
			if ((outer[i].x - inner[index].x) == 0)
				info.angle = 90;
			else
				info.angle = atan((outer[i].y - inner[index].y) / (outer[i].x - inner[index].x)) * 180 / PI;
			result.push_back(info);
		}
		return  result;

	}
	vector<vector<LineInfo>> ImgProcess::find_radiation(const vector<vector<LineInfo>>& info)
	{
		return vector<vector<LineInfo>>();
	}
}
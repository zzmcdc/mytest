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

	void ImgProcess::set_image(cv::Mat & img)
	{
		img.copyTo(orig_image);
		line_info.clear();
		contours.clear();
		radiation.clear();
	}

	void ImgProcess::get_contours()
	{
		cv::Size size = orig_image.size();
		cv::Mat img_gray(size, CV_8UC1);
		cv::cvtColor(orig_image, img_gray, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(img_gray, img_gray, cv::Size(17, 17), 1.4, 1.4);
		cv::Mat img_binary;
		cv::threshold(img_gray, img_binary, 0, 255, cv::THRESH_BINARY_INV + cv::THRESH_OTSU);
		cv::Mat img_blur;
		cv::medianBlur(img_binary, img_blur, 15);
		cv::findContours(img_blur, contours, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
	}

	void ImgProcess::draw_result()
	{
		orig_image.copyTo(view_image);
		for (auto &result : radiation)
		{
			for (auto &item : result)
			{
				cv::line(view_image, item.start, item.end, cv::Scalar(0, 0, 255), 2);
			}
		}
	}

	cv::Mat ImgProcess::get_view_image()
	{
		return view_image;
	}

	int  ImgProcess::find_pair(const cv::Point &point, const Direction &orig, const vector<cv::Point> &point_set) const
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

			flag = Direction(point, point_set[mid]) * orig;
			if (flag < 0)
				left_index = mid;
			else
				right_index = mid;
		}
		return mid;
	}

	vector<LineInfo> ImgProcess::cal_nearst(const vector<cv::Point> &outer, const vector<cv::Point> &inner) const 
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
			int index = find_pair(outer[i], orig, inner);
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
	vector<LineInfo> ImgProcess::find_radiation(const vector<LineInfo> &info)
	{
		vector<LineInfo> six_line;
		size_t size = info.size();
		size_t part = size / 6;
		double dis = info[0].distance;
		int index = 0;
		for (int i = 1;i< info.size();++i)
		{
			if (info[i].distance > dis)
			{
				dis = info[i].distance;
				index = i;
			}
		}

		for (int i = 0; i < 6; ++i)
		{
			six_line.push_back(info[(index + i*part) % size]);
		}
		return six_line;
	}

	void ImgProcess::compute()
	{
		get_contours();
		vector<vector<cv::Point >> contours_temp = contours;
		sort(contours_temp.begin(), contours_temp.end(), [](vector<cv::Point> a, vector<cv::Point> b) -> bool { return cv::contourArea(a) > cv::contourArea(b);});
		for (int i = 0; i < 3; ++i)
		{
			line_info.push_back(cal_nearst(contours_temp[i], contours_temp[i + 1]));
		}

		for (int i = 0; i < line_info.size(); ++i)
		{
			radiation.push_back(find_radiation(line_info[i]));
		}
		draw_result();
		
	}
}
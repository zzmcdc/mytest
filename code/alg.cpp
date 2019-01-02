#include "process.h"
#ifdef _WIN32
# define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
#include <opencv2/opencv.hpp>
#include <vector>
using namespace Vison;
using namespace std;
using namespace cv;

extern "C" DLL_EXPORT ImgProcess *get_process()
{
	return new Vison::ImgProcess();
}

extern "C" DLL_EXPORT void Release(ImgProcess *self)
{
	delete self;
}

extern "C" DLL_EXPORT void set_image(ImgProcess *self, string path)
{
	cv::Mat image = cv::imread(path);
	self->set_image(image);
}	

extern "C" DLL_EXPORT void compute(ImgProcess *self)
{
	self->compute();
}

extern "C" DLL_EXPORT void get_draw(ImgProcess *self, char **ptr)
{
	*ptr  =  self->get_view_image().data;
}

extern  "C" DLL_EXPORT Distance get_result(ImgProcess *self)
{
	vector<vector<LineInfo>> result = self->get_radiation();
	Distance res;
	for(int i=0; i<3;++i)
		for(int j = 0 ; j<6; ++j)
			res.data[i*6+j] = result[i][j].distance;
	return res;
}


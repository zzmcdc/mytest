#include "include/process.h"
#ifdef _WIN32
# define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
#include <opencv2/opencv.hpp>
using namespace Vison;
using namespace std;
using namespace cv;

extern "C" DLL_EXPORT ImgProcess *get_process()
{
	return new Vison::ImgProcess();
}

extern "C" DLL_EXPORT void set_image(ImgProcess *self, char *bytes)
{
	cv::Mat image = cv::imdecode(bytes);
	self->set_image(image);
}	

extern "C" DLL_EXPORT void compute(ImgProcess *self)
{
	self->compute();
}

extern "C" DLL_EXPORT unsigned char * get_draw(ImgProcess *self)
{
	return self->get_view_image().data;
}

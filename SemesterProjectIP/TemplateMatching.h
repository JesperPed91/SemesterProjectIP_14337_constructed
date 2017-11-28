#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


class TemplateMatching
{
public:
	Mat im;
	TemplateMatching();
	TemplateMatching(Mat image);
	~TemplateMatching();
};


#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
using namespace cv;
using namespace std;

class blobDetection
{
public:
	Mat im1;
	blobDetection();
	blobDetection(Mat image);
	~blobDetection();
};


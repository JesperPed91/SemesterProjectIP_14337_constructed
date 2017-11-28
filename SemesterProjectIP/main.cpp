#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "blobDetection.h"
#include "TemplateMatching.h"

using namespace cv;
using namespace std;

extern Mat im;
Mat im2;
Mat im3;
int value;

int main(int, char)
{
	VideoCapture stream1(0); //0 is the id of video device.0 if you have only one

	if (!stream1.isOpened()) { //check if video device has been initialised
		cout << "cannot open camera";
	}
	stream1.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // valueX = your wanted width 
	stream1.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // valueY = your wanted heigth
	//unconditional loop
	while (true) {
		stream1.read(im2);

		flip(im2, im2, 0);
		cvtColor(im2, im3, CV_BGR2GRAY);
		GaussianBlur(im3, im, Size(15, 15), 3, 3);

		if (im.data && !im.empty()){
			for (size_t y = 0; y < im.rows; ++y) {
				for (size_t x = 0; x < im.cols; ++x){
					value = im.at<unsigned char>(y, x);
					if (value >= 70){
						im.at<unsigned char>(y, x) = 0;
					}
					else{
						im.at<unsigned char>(y, x) = 255;
					}
				}
			}
		}
		blobDetection blobDetect = blobDetection(im, 100, 100, 1280, 720);
		TemplateMatching tempMatch = TemplateMatching(im);

		if (waitKey(30) >= 0)
			break;
	}
}
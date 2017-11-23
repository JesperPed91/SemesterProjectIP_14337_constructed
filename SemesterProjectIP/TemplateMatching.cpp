#include "TemplateMatching.h"
#include "blobDetection.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat im;

TemplateMatching::TemplateMatching(Mat image)
{
	Mat im= image;
}
TemplateMatching::~TemplateMatching()
{
}

//temp matching function 
void fastMatchTemplate(cv::Mat& srca,  // The reference image
	cv::Mat& srcb,  // The template image
	cv::Mat& dst,   // Template matching result
	int maxlevel)   // Number of levels
{
	std::vector<cv::Mat> refs, tpls, results;

	// Build Gaussian pyramid
	cv::buildPyramid(srca, refs, maxlevel);
	cv::buildPyramid(srcb, tpls, maxlevel);

	cv::Mat ref, tpl, res;

	// Process each level
	for (int level = maxlevel; level >= 0; level--)
	{
		ref = refs[level];
		tpl = tpls[level];
		res = cv::Mat::zeros(ref.size() + cv::Size(1, 1) - tpl.size(), CV_32FC1);

		if (level == maxlevel)
		{
			// On the smallest level, just perform regular template matching
			cv::matchTemplate(ref, tpl, res, CV_TM_CCORR_NORMED);
		}
		else
		{
			// On the next layers, template matching is performed on pre-defined 
			// ROI areas.  We define the ROI using the template matching result 
			// from the previous layer.

			cv::Mat mask;
			cv::pyrUp(results.back(), mask);

			cv::Mat mask8u;
			mask.convertTo(mask8u, CV_8U);

			// Find matches from previous layer
			std::vector<std::vector<cv::Point> > contours;
			cv::findContours(mask8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

			// Use the contours to define region of interest and 
			// perform template matching on the areas
			for (int i = 0; i < contours.size(); i++)
			{
				cv::Rect r = cv::boundingRect(contours[i]);
				cv::matchTemplate(
					ref(r + (tpl.size() - cv::Size(1, 1))),
					tpl,
					res(r),
					CV_TM_CCORR_NORMED
					);
			}
		}

		// Only keep good matches
		cv::threshold(res, res, 0.8, 1., CV_THRESH_TOZERO);
		results.push_back(res);
	}

	res.copyTo(dst);
}

void templateMatching(){
	//template matching 
	cv::Mat ref = im;
	cv::Mat tpl1 = cv::imread("C:/Users/Tobia/Desktop/rod/t6.png");
	cv::Mat tpl2 = cv::imread("C:/Users/Tobia/Desktop/rod/t7.png");

	cv::Mat tpl_gray1, tpl_gray2;
	cv::cvtColor(tpl1, tpl_gray1, CV_BGR2GRAY);
	cv::cvtColor(tpl2, tpl_gray2, CV_BGR2GRAY);

	vector<Mat> List_Template_Img;
	List_Template_Img.push_back(tpl_gray1);
	List_Template_Img.push_back(tpl_gray2);

	bool temp[2] = { 0, 1 };
	temp[0] = false;
	temp[1] = false;

	for (int i = 0; i < List_Template_Img.size(); i++)
	{
		cv::Mat dst;
		fastMatchTemplate(ref, List_Template_Img[i], dst, 2);
		while (true)
		{
			double minval, maxval;
			cv::Point minloc, maxloc;
			cv::minMaxLoc(dst, &minval, &maxval, &minloc, &maxloc);

			if (maxval >= 0.9)
			{
				cv::rectangle(
					ref, maxloc,
					cv::Point(maxloc.x + List_Template_Img[i].cols, maxloc.y + List_Template_Img[i].rows),
					CV_RGB(0, 255, 0), 2
					);

				cv::floodFill(
					dst, maxloc,
					cv::Scalar(0), 0,
					cv::Scalar(.1),
					cv::Scalar(1.)
					);
				temp[i] = true;
			}
			else
			{
				break;
			}
		}
	}

	//can maybe use while loop, if it only changes variables. 
	if (temp[0] == true){
		cout << "temp1 found" << endl;
	}
	else if (temp[0] == false){ cout << "temp1  not found" << endl;
	}

	if (temp[1] == true){
		cout << "temp2 found" << endl;
	}
	else if (temp[1] == false){ cout << "temp2  not found" << endl; }
}
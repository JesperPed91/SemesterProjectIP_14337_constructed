#include "blobDetection.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat im1; 
Mat im_with_keypoints;
vector<KeyPoint> keypoints;


blobDetection::blobDetection(Mat image, float x1, float y1, float x2, float y2)
{
	im1 = image;
	dilate(im1, im1, Mat(), Point(-1, -1), 2, 1, 1);
	erode(im1, im1, Mat(), Point(-1, -1), 2, 1, 1);

	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 90;
	params.maxThreshold = 200;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 100;
	params.maxArea = 600;

	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.1;

	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.87;

	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;

	// Filter by color 
	params.filterByColor = 1;
	params.blobColor = 255;


	// Storage for blobs
	vector<KeyPoint> keypoints;


	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// Detect blobs
	detector->detect(im1, keypoints);
	keypoints.resize(90);
	if (keypoints[0].pt.x >= x1 && keypoints[0].pt.y >= y1 && keypoints[0].pt.x <= x2 && keypoints[0].pt.y <= y2){
		cout << "Ja:" << keypoints[0].pt << endl;
	}

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
	// the size of the circle corresponds to the size of blob

	Mat im_with_keypoints;
	drawKeypoints(im1, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	Mat ref = im1;
	// Show blobs
	namedWindow("keypoints", WINDOW_NORMAL);
	imshow("keypoints", im_with_keypoints);
	//cv::imshow("result", ref);

}

blobDetection::~blobDetection()
{
}



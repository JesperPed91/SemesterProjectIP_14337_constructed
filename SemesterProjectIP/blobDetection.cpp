#include "blobDetection.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

Mat im1; 
Mat im_with_keypoints;
vector<KeyPoint> keypoints;


blobDetection::blobDetection(Mat image)
{
	im1 = image;
	// Setup SimpleBlobDetector parameters.
	SimpleBlobDetector::Params params;

	// Change thresholds
	params.minThreshold = 50;
	//params.maxThreshold = 200;

	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 100;
	params.maxArea = 2000;

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

	// Set up detector with params
	Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

	// Detect blobs
	detector->detect(im1, keypoints);

	// Draw detected blobs as red circles.
	// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
	// the size of the circle corresponds to the size of blob
	drawKeypoints(im1, keypoints, im_with_keypoints, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("keypoints", im_with_keypoints);
}

blobDetection::~blobDetection()
{
}



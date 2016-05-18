//
// Created by piotrek on 17.05.16.
//

#include "SimplePatchExtractor.h"
#include "../Helpers.h"
#include <limits>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void SimplePatchExtractor::extract(cv::Mat &image, cv::KeyPoint& kpoint, double *patch, int size)
{
	for(int i = 0; i < size; ++i)
		for( int j = 0; j < size; ++j)
		{
			patch[ i*size + j ] = std::numeric_limits<double>::infinity();
		}
	cv::Rect patchBound( kpoint.pt.x - size/2, kpoint.pt.y-size/2, size, size);
	cv::Mat patchMat(image,patchBound);
	cv::Mat patchMatGray;
	cv::cvtColor(patchMat, patchMatGray, CV_BGR2GRAY);
	matToArray(patchMatGray,patch);

//	std::vector<cv::KeyPoint> kp1;
//	kp1.push_back( kpoint );
//	cv::Mat img;
//	cv::drawKeypoints( image, kp1, img, cv::Scalar(0,256,256), cv::DrawMatchesFlags::DEFAULT );
//
//	imshow("Keypoint", img );
//	imshow("Patch", patchMatGray );
//	cv::waitKey(0);

}

const char *SimplePatchExtractor::getName()
{
	this->extractor_name;
}


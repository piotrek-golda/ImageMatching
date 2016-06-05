//
// Created by piotrek on 17.05.16.
//

#include "SimplePatchExtractor.h"
#include "../Helpers.h"
#include <limits>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void unpackSIFTOctave(const cv::KeyPoint& kpt, int& octave, int& layer, float& scale)
{
	octave = kpt.octave & 255;
	layer = (kpt.octave >> 8) & 255;
	octave = octave < 128 ? octave : (-128 | octave);
	scale = octave >= 0 ? 1.f/(1 << octave) : (float)(1 << -octave);
}

void rotateAndCrop(cv::Mat& patchBigGray, cv::Mat& outPatch, double angle, int size)
{
	cv::Mat rotationMat = cv::getRotationMatrix2D(cv::Point2f(size,size),angle,1.);
	cv::Mat tmp;
	cv::warpAffine(patchBigGray,tmp,rotationMat, patchBigGray.size());

	cv::Rect patchBound = cv::Rect( tmp.cols/2 -size/2, tmp.rows/2 -size/2 , size, size);
	outPatch = cv::Mat(tmp,patchBound);
}

void SimplePatchExtractor::extract(cv::Mat &image, cv::KeyPoint& kpoint, double *patch, int size, bool shouldScale, bool shouldRotate)
{

//	cv::Rect patchBound( kpoint.pt.x - size/2, kpoint.pt.y-size/2, size, size);
//	patchBound = patchBound & cv::Rect(0, 0, image.cols, image.rows);
//	cv::Mat patchMat(image,patchBound);
//	cv::Mat patchMatGray;
//	cv::cvtColor(patchMat, patchMatGray, CV_BGR2GRAY);
//	matToArray(patchMatGray,patch);

	int kpsize = cvCeil(kpoint.size);
	if(!shouldScale)
		kpsize = size;
	cv::Rect patchBound( kpoint.pt.x - kpsize, kpoint.pt.y-kpsize, 2*kpsize, 2*kpsize);
	patchBound = patchBound & cv::Rect(0, 0, image.cols, image.rows);
	cv::Mat patchMat;
	cv::Mat patchMatScaled(image,patchBound);
	if(shouldRotate)
		rotateAndCrop(patchMatScaled,patchMat,kpoint.angle,kpsize);
	else
		rotateAndCrop(patchMatScaled,patchMat,0,kpsize);
	cv::resize(patchMat,patchMatScaled, {size,size} );
	cv::Mat patchMatGray;
	cv::cvtColor(patchMatScaled, patchMatGray, CV_BGR2GRAY);
	matToArray(patchMatGray,patch);


//	std::cout << kpoint.size << ' ' << kpoint.octave<< std::endl;


//	int o,l;float s;
//	unpackSIFTOctave(kpoint,o,l,s);
//	std::cout<< kpoint.size << ' '<< kpoint.angle << ' '<< (int)(kpoint.octave ) << ' ' << kpoint.response << ' ' << o << ' ' << l << ' ' << s <<std::endl;


//	std::vector<cv::KeyPoint> kp1;
//	kp1.push_back( kpoint );
//	cv::Mat img;
//	cv::drawKeypoints( image, kp1, img, cv::Scalar(0,256,256), /*cv::DrawMatchesFlags::DEFAULT*/ cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
//
//	imshow("Keypoint", img );
//	imshow("Patch", patchMatGray );
////	imshow("PatchBig", patchMatBig );
//	cv::waitKey(0);

}

const char *SimplePatchExtractor::getName()
{
	return this->extractor_name;
}


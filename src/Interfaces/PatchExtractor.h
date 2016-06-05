//
// Created by piotrek on 17.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_PATCHEXTRACTOR_H
#define DESCRIPTORDETECTOR_TESTER_PATCHEXTRACTOR_H


#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

class PatchExtractor
{
public:
	virtual const char* getName() = 0;

	virtual void extract(cv::Mat& image, cv::KeyPoint& kpoint, double* patch, int size, bool shouldScale, bool shouldRotate) = 0;
};


#endif //DESCRIPTORDETECTOR_TESTER_PATCHEXTRACTOR_H

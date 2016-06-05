//
// Created by piotrek on 17.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SIMPLEPATCHEXTRACTOR_H
#define DESCRIPTORDETECTOR_TESTER_SIMPLEPATCHEXTRACTOR_H


#include "../Interfaces/PatchExtractor.h"

class SimplePatchExtractor : public PatchExtractor
{
private:
	const char* extractor_name = "SimpleExtractor";

public:
	virtual const char *getName();

	virtual void extract(cv::Mat &image, cv::KeyPoint& kpoint, double *patch, int size, bool shouldScale, bool shouldRotate);

};


#endif //DESCRIPTORDETECTOR_TESTER_SIMPLEPATCHEXTRACTOR_H

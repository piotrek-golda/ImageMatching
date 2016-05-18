//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_DETECTOR_H

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "DetectorOptions.h"


class Detector
{
public:

public:

	virtual const char* getName() = 0;

	virtual void detect( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						 DetectorOptions& options ) = 0;


};


#endif //DESCRIPTORDETECTOR_TESTER_DETECTOR_H

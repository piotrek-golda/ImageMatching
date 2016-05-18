//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_DESCRIPTOR_H

#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include "DescriptorOptions.h"


class Descriptor
{
public:

public:

	virtual const char* getName() = 0;

	virtual void describe( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						 cv::Mat& descriptions, DescriptorOptions& options ) = 0;

};


#endif //DESCRIPTORDETECTOR_TESTER_DESCRIPTOR_H

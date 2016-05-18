//
// Created by piotrek on 13.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_HOMOGRAPHYGETTER_H
#define DESCRIPTORDETECTOR_TESTER_HOMOGRAPHYGETTER_H


#include <opencv2/core/core.hpp>

class HomographyGetter
{

private:

	cv::Mat homography;

public:

	cv::Mat get();

	void set( cv::Mat );
};


#endif //DESCRIPTORDETECTOR_TESTER_HOMOGRAPHYGETTER_H

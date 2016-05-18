//
// Created by piotrek on 13.05.16.
//

#include "HomographyGetter.h"

cv::Mat HomographyGetter::get()
{
	return this->homography;
}

void HomographyGetter::set( cv::Mat homography )
{
	this->homography = homography;
}

//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_PROGRAMFLOWFACADE_H
#define DESCRIPTORDETECTOR_TESTER_PROGRAMFLOWFACADE_H

#include <vector>

#include <opencv2/opencv.hpp>

#include "Interfaces/Detector.h"
#include "Interfaces/Descriptor.h"
#include "Interfaces/DetectorOptions.h"
#include "Interfaces/DescriptorOptions.h"
#include "HomographyGetter.h"
#include "Interfaces/KeysMatcher.h"
#include "Interfaces/DescriptionsMatcher.h"

class ProgramFlowFacade
{
public:

private:

	DetectorOptions* detectorOptions_ = NULL;
	Detector* detector_ = NULL;
	DescriptorOptions* descriptorOptions_ = NULL;
	Descriptor* descriptor_ = NULL;
	HomographyGetter* homographyGetter_ = NULL;
	KeysMatcherOptions* keysMatcherOptions_ = NULL;
	KeysMatcher * keysMatcher_ = NULL;
	DescriptionsMatcherOptions* descMatcherOptions_ = NULL;
	DescriptionsMatcher* descMatcher_ = NULL;
	int keyPointsLimit = 0;


	std::vector< cv::KeyPoint > key_points1;
	std::vector< cv::KeyPoint > key_points2;
	std::vector< cv::Point2f > key_points_transformed;
	cv::Mat descriptions1;
	cv::Mat descriptions2;
	std::vector< std::pair<int,int> > true_matches;
	std::vector< std::pair<int,int> > descriptions_matches;

	cv::Mat homography;

	int matches_found;

public:


	ProgramFlowFacade(DetectorOptions *detectorOptions_, Detector *detector_, DescriptorOptions *descriptorOptions_,
					  Descriptor *descriptor_, HomographyGetter *homographyGetter_,
					  KeysMatcherOptions *keysMatcherOptions_, KeysMatcher *keysMatcher_,
					  DescriptionsMatcherOptions *descMatcherOptions_, DescriptionsMatcher *descMatcher_, int kpointsLimit)
			: detectorOptions_(detectorOptions_), detector_(detector_), descriptorOptions_(descriptorOptions_),
			  descriptor_(descriptor_), homographyGetter_(homographyGetter_), keysMatcherOptions_(keysMatcherOptions_),
			  keysMatcher_(keysMatcher_), descMatcherOptions_(descMatcherOptions_), descMatcher_(descMatcher_), keyPointsLimit(kpointsLimit) { }

	int compute( cv::Mat& image1, cv::Mat& image2, cv::Mat homographyMat = cv::Mat() );

	~ProgramFlowFacade();

private:
	ProgramFlowFacade();

};


#endif //DESCRIPTORDETECTOR_TESTER_PROGRAMFLOWFACADE_H

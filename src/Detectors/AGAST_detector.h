//
// Created by piotrek on 12.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_AGAST_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_AGAST_DETECTOR_H


#include "../Interfaces/DetectorOptions.h"
#include "../Interfaces/Detector.h"
#include "AGAST/agast_wrapper.hpp"

class AGAST_detectorOptions : public DetectorOptions
{
public:
	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);

	int threshold=10;
	bool nonmaxSuppression=true;
	int type = AgastFeatureDetector::OAST_9_16;
};

class AGAST_detector : public Detector
{
private:
	const char* detector_name = "AGASTDetector";

public:
	virtual const char *getName();

	virtual void detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_AGAST_DETECTOR_H

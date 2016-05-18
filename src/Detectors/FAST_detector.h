//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_FAST_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_FAST_DETECTOR_H


#include "../Interfaces/Detector.h"


class FAST_detectorOptions : public DetectorOptions
{
public:
	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);

	int threshold=10;
	bool nonmaxSuppression=true;
};


class FAST_detector : public Detector
{
private:
	const char* detector_name = "FASTDetector";

public:
	virtual const char* getName();

	virtual void detect( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						 DetectorOptions& options );


};


#endif //DESCRIPTORDETECTOR_TESTER_FAST_DETECTOR_H

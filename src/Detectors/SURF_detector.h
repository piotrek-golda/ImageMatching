//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SURF_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_SURF_DETECTOR_H


#include "../Interfaces/Detector.h"

class SURF_detectorOptions : public DetectorOptions
{
public:
	double hessianThreshold = 400.;
	int nOctaves=4;
	int nOctaveLayers=2;
	bool extended=true;
	bool upright=false;

	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);
};


class SURF_detector : public Detector
{
public:

	const char* detector_name = "SURFDetector";

public:

	virtual const char *getName() override;

	virtual void detect( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						 DetectorOptions& options ) override;
};


#endif //DESCRIPTORDETECTOR_TESTER_SURF_DETECTOR_H

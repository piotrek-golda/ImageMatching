//
// Created by piotrek on 14.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SIFT_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_SIFT_DETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "../Interfaces/DetectorOptions.h"
#include "../Interfaces/Detector.h"

class SIFT_detectorOptions : public DetectorOptions
{
public:
	int nfeatures=0;
	int nOctaveLayers=3;
	double contrastThreshold=0.04;
	double edgeThreshold=10;
	double sigma=1.6;

	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class SIFT_detector : public Detector
{
private:

	const char* detector_name = "SIFTDetector";

public:

	virtual const char *getName() override;

	virtual void detect( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						 DetectorOptions& options ) override;
};


#endif //DESCRIPTORDETECTOR_TESTER_SIFT_DETECTOR_H

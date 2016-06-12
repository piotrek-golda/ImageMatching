//
// Created by piotrek on 11.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_HARRIS_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_HARRIS_DETECTOR_H

#include "../Interfaces/DetectorOptions.h"
#include "../Interfaces/Detector.h"

class HARRIS_detectorOptions : public DetectorOptions
{
public:
	int nfeatures = 1000;
	double k = 0.04;
	double minDistance = 1.;
	double qualityLevel = 0.01;

	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class HARRIS_detector : public Detector
{
private:
	const char* detector_name = "HarrisDetector";

public:
	virtual const char *getName();

	virtual void detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_HARRIS_DETECTOR_H

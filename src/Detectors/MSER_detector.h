//
// Created by piotrek on 11.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_MSER_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_MSER_DETECTOR_H

#include "../Interfaces/DetectorOptions.h"
#include "../Interfaces/Detector.h"

class MSER_detectorOptions : public DetectorOptions
{
public:
	int delta = 5;
	int minArea = 60;
	int maxArea = 14400;
	float maxVariation = 0.25;
	float minDiversity = 0.2;
	int maxEvolution = 200;
	double areaThreshold = 1.01;
	double minMargin = 0.003;
	int edgeBlurSize = 5;

	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class MSER_detector : public Detector
{
private:
	const char* detector_name = "MSERDetector";

public:
	virtual const char *getName();

	virtual void detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_MSER_DETECTOR_H

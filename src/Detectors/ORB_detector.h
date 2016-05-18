//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_ORB_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_ORB_DETECTOR_H

#include "../Interfaces/Detector.h"
#include "../Interfaces/DetectorOptions.h"


class ORB_detectorOptions : public DetectorOptions
{
public:
	int nfeatures=500;
	float scaleFactor=1.2f;
	int nlevels=8;
	int edgeThreshold=31;
	int firstLevel = 0;
	int WTA_K=2;
	int scoreType=cv::ORB::HARRIS_SCORE;
	int patchSize=31;

	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);
};


class ORB_detector : public Detector
{
private:
	const char* detector_name = "ORBDetector";

public:

	virtual const char *getName() override;

	virtual void detect( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						  DetectorOptions& options ) override;


};


#endif //DESCRIPTORDETECTOR_TESTER_ORB_DETECTOR_H

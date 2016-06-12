//
// Created by piotrek on 12.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_ASIFT_DETECTOR_H
#define DESCRIPTORDETECTOR_TESTER_ASIFT_DETECTOR_H

#include "../Interfaces/DetectorOptions.h"
#include "../Interfaces/Detector.h"
#include "ASIFT/demo_lib_sift.h"
#include "../Interfaces/DescriptorOptions.h"
#include "../Interfaces/Descriptor.h"

class ASIFT_detectorOptions : public DetectorOptions
{
public:

	//ordinary sift params
	int OctaveMax=100000;
	int DoubleImSize = 0;
	int order = 3;
	float InitSigma = 1.6;
	int BorderDist = 5;
	int Scales = 3;
	float PeakThresh = 255.0 * 0.04 / 3.0;
	float EdgeThresh = 0.06;
	float EdgeThresh1 = 0.08;
	int OriBins  = 36;
	float OriSigma = 1.5;
	float OriHistThresh = 0.8;
	float MaxIndexVal = 0.2;
	int MagFactor  = 3;
	float IndexSigma  = 1.0;
	int IgnoreGradSign = 0;
	float MatchRatio = 0.73;
	float MatchXradius = 1000000.0f;
	float MatchYradius = 1000000.0f;

	int noncorrectlylocalized = 0;

	//asift params
	int num_of_tilts=1;

	//global params
	int nfeatures = 500;

	virtual DetectorOptions *getConfiguration(INIReader cfgFile, std::string section);

	siftPar getSiftParams() const;

};

class ASIFT_descriptorOptions : public DescriptorOptions
{
public:
	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class ASIFT_detector_descriptor : public Detector, public Descriptor
{
private:

	const char* detector_name = "ASIFTDetectorDescriptor";
	const char* descriptor_name = "ASIFTDetectorDescriptor";

	keypointslist keysCopy;

public:
	virtual const char *getName();

	virtual void detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options);


	virtual void describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
						  DescriptorOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_ASIFT_DETECTOR_H

//
// Created by piotrek on 17.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_PI_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_PI_DESCRIPTOR_H

#include <opencv2/features2d/features2d.hpp>
#include "../Interfaces/DescriptorOptions.h"
#include "../Interfaces/Descriptor.h"
#include "PI_features/features_Persistant_Image.h"
#include <limits>

class PI_descriptorOptions : public DescriptorOptions
{
public:
	PI::NormType normType = PI::NONE;
	bool ignoreOutliers = false;
	double minDiagramLimits = std::numeric_limits<double>::infinity();
	double maxDiagramLimits = -std::numeric_limits<double>::infinity();
	double sigma = 0.001;
	unsigned int resolution = 16;
	bool weighting = false;

	int patchSize = 41;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);

};



class PI_descriptor : public Descriptor
{

private:

	const char* descriptor_name = "PIDescriptor";

public:
	virtual const char *getName();

	virtual void describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
						  DescriptorOptions &options);

private:

	void filterBoundKeyPoints(std::vector<cv::KeyPoint>& kpoints, int patchSize, int imgCols, int imgRows);
};


#endif //DESCRIPTORDETECTOR_TESTER_PI_DESCRIPTOR_H

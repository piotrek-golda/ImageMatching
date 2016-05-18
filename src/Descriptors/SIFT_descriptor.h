//
// Created by piotrek on 14.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SIFT_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_SIFT_DESCRIPTOR_H


#include "../Interfaces/Descriptor.h"
#include "../Interfaces/DescriptorOptions.h"


class SIFT_descriptorOptions : public DescriptorOptions
{
public:
	int nfeatures=0;
	int nOctaveLayers=3;
	double contrastThreshold=0.04;
	double edgeThreshold=10;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);

	double sigma=1.6;
};


class SIFT_descriptor : public Descriptor
{
private:

	const char* descriptor_name = "SIFTDescriptor";

public:

	virtual const char *getName();

	virtual void describe( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						   cv::Mat& descriptions, DescriptorOptions& options );

};


#endif //DESCRIPTORDETECTOR_TESTER_SIFT_DESCRIPTOR_H

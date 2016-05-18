//
// Created by piotrek on 14.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SURF_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_SURF_DESCRIPTOR_H

#include <iostream>
#include <opencv2/nonfree/features2d.hpp>

#include "../Interfaces/Descriptor.h"


class SURF_descriptorOptions : public DescriptorOptions
{
public:
	double hessianThreshold = 400.;
	int nOctaves=4;
	int nOctaveLayers=2;
	bool extended=true;
	bool upright=false;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);
};



class SURF_descriptor : public Descriptor
{
private:

	const char* descriptor_name = "SURFDescriptor";

public:

	virtual const char *getName();

	virtual void describe( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						   cv::Mat& descriptions, DescriptorOptions& options );

};


#endif //DESCRIPTORDETECTOR_TESTER_SURF_DESCRIPTOR_H

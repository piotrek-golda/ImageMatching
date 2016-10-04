//
// Created by piotrek on 11.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_FREAK_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_FREAK_DESCRIPTOR_H

#include "../Interfaces/DescriptorOptions.h"
#include "../Interfaces/Descriptor.h"

class FREAK_descriptorOptions : public DescriptorOptions
{
public:

	bool orientationNormalized=true;
	bool scaleNormalized=true;
	float patternScale=22.0f;
	int nOctaves=4;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);
};
class FREAK_descriptor : public Descriptor
{
private:
	const char* descriptor_name = "FREAKDescriptor";

public:
	virtual const char *getName();

	virtual void describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
						  DescriptorOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_FREAK_DESCRIPTOR_H

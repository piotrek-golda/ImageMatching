//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_BRIEF_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_BRIEF_DESCRIPTOR_H


#include "../Interfaces/Descriptor.h"

class BRIEF_descriptorOptions : public DescriptorOptions
{
public:
	int bytes = 32;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);
};


class BRIEF_descriptor : public Descriptor
{
private:

	const char* descriptor_name = "BRIEFDescriptor";

public:

	virtual const char* getName();

	virtual void describe( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						   cv::Mat& descriptions, DescriptorOptions& options );


};


#endif //DESCRIPTORDETECTOR_TESTER_BRIEF_DESCRIPTOR_H

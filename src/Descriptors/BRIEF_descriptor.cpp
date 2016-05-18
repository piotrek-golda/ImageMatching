//
// Created by piotrek on 15.05.16.
//

#include <typeinfo>
#include "BRIEF_descriptor.h"
#include "../Helpers.h"

void BRIEF_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points,
								cv::Mat &descriptions, DescriptorOptions &options)
{
	BRIEF_descriptorOptions opts;
	try
	{
		opts = static_cast< BRIEF_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}


//	cv::Mat descriptionsMat;

	cv::BriefDescriptorExtractor descriptor(opts.bytes);
	descriptor.compute(image,key_points,descriptions);
//	matToVector(descriptionsMat,descriptions);
}

DescriptorOptions *BRIEF_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	BRIEF_descriptorOptions* opts = new BRIEF_descriptorOptions();

	opts->bytes = cfgFile.GetInteger(section, "bytes",opts->bytes);

	return opts;
}

const char* BRIEF_descriptor::getName()
{
	return this->descriptor_name;
}

//
// Created by piotrek on 14.05.16.
//

#include <typeinfo>

#include <opencv2/nonfree/features2d.hpp>

#include "SIFT_descriptor.h"
#include "../Helpers.h"

void SIFT_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points,
							   cv::Mat &descriptions, DescriptorOptions &options)
{
	SIFT_descriptorOptions opts;
	try
	{
		opts = static_cast< SIFT_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}

	cv::SiftDescriptorExtractor descriptor(opts.nfeatures,opts.nOctaveLayers,opts.contrastThreshold,opts.edgeThreshold,opts.sigma);
	descriptor.compute(image,key_points,descriptions);

}

DescriptorOptions *SIFT_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	SIFT_descriptorOptions* opts = new SIFT_descriptorOptions();

	opts->nfeatures = cfgFile.GetInteger(section, "nfeatures",opts->nfeatures);
	opts->nOctaveLayers = cfgFile.GetInteger(section, "nOctaveLayers",opts->nOctaveLayers);
	opts->contrastThreshold = (float)cfgFile.GetReal(section, "contrastThreshold",opts->contrastThreshold);
	opts->edgeThreshold = (float)cfgFile.GetReal(section, "edgeThreshold",opts->edgeThreshold);
	opts->sigma = (float)cfgFile.GetReal(section, "sigma",opts->sigma);

	return opts;
}

const char *SIFT_descriptor::getName()
{
	return this->descriptor_name;
}

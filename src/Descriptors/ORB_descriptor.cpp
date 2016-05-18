//
// Created by piotrek on 08.05.16.
//

#include <typeinfo>
#include "ORB_descriptor.h"
#include "../Helpers.h"

void ORB_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points,
							  cv::Mat &descriptions, DescriptorOptions &options)
{
	ORB_descriptorOptions opts;
	try
	{
		opts = static_cast< ORB_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}



	cv::OrbDescriptorExtractor descriptor(opts.nfeatures,opts.scaleFactor,opts.nlevels,opts.edgeThreshold,opts.firstLevel,opts.WTA_K,opts.scoreType,opts.patchSize);
	descriptor.compute(image,key_points,descriptions);

}

DescriptorOptions *ORB_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	ORB_descriptorOptions* opts = new ORB_descriptorOptions();

	opts->edgeThreshold = cfgFile.GetInteger(section, "edgeThreshold",opts->edgeThreshold);
	opts->firstLevel = cfgFile.GetInteger(section, "firstLevel",opts->firstLevel);
	opts->nfeatures = cfgFile.GetInteger(section, "nfeatures",opts->nfeatures);
	opts->nlevels = cfgFile.GetInteger(section, "nlevels",opts->nlevels);
	opts->patchSize = cfgFile.GetInteger(section, "patchSize",opts->patchSize);
	opts->scoreType = cfgFile.GetInteger(section, "scoreType",opts->scoreType);
	opts->WTA_K = cfgFile.GetInteger(section, "WTA_K",opts->WTA_K);
	opts->scaleFactor = (float)cfgFile.GetReal(section, "scaleFactor",opts->scaleFactor);

	return opts;
}

const char *ORB_descriptor::getName()
{
	return this->descriptor_name;
}

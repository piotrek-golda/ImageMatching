//
// Created by piotrek on 14.05.16.
//

#include <typeinfo>
#include "SURF_descriptor.h"
#include "../Helpers.h"

void SURF_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points,
							   cv::Mat &descriptions, DescriptorOptions &options)
{
	SURF_descriptorOptions opts;
	try
	{
		opts = static_cast< SURF_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}


	cv::SurfDescriptorExtractor descriptor(opts.hessianThreshold,opts.nOctaves,opts.nOctaveLayers,opts.extended,opts.upright);
	descriptor.compute(image,key_points,descriptions);

}

DescriptorOptions *SURF_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{

	SURF_descriptorOptions* opts = new SURF_descriptorOptions();

	opts->nOctaves = cfgFile.GetInteger(section, "nOctaves",opts->nOctaves);
	opts->nOctaveLayers = cfgFile.GetInteger(section, "nOctaveLayers",opts->nOctaveLayers);
	opts->hessianThreshold = (float)cfgFile.GetReal(section, "hessianThreshold",opts->hessianThreshold);
	opts->extended = cfgFile.GetBoolean(section, "extended",opts->extended);
	opts->upright = cfgFile.GetBoolean(section, "upright",opts->upright);

	return opts;
}

const char *SURF_descriptor::getName()
{
	return this->descriptor_name;
}

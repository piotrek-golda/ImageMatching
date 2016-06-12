//
// Created by piotrek on 11.06.16.
//

#include <typeinfo>
#include "FREAK_descriptor.h"


void FREAK_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
								DescriptorOptions &options)
{
	FREAK_descriptorOptions opts;
	try
	{
		opts = static_cast< FREAK_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}


	cv::Ptr<cv::DescriptorExtractor> descriptor = cv::DescriptorExtractor::create("FREAK");

	descriptor->set("orientationNormalized",opts.orientationNormalized);
	descriptor->set("scaleNormalized",opts.scaleNormalized);
	descriptor->set("patternScale",opts.patternScale);
	descriptor->set("nbOctave",opts.nOctaves);

	descriptor->compute(image,key_points,descriptions);

}

const char *FREAK_descriptor::getName()
{
	return this->descriptor_name;
}

DescriptorOptions *FREAK_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	FREAK_descriptorOptions* opts = new FREAK_descriptorOptions();

	opts->orientationNormalized = cfgFile.GetBoolean(section, "orientationNormalized",opts->orientationNormalized);
	opts->scaleNormalized = cfgFile.GetBoolean(section, "scaleNormalized",opts->scaleNormalized);
	opts->patternScale = (float)cfgFile.GetReal(section, "patternScale",opts->patternScale);
	opts->nOctaves = cfgFile.GetInteger(section, "nOctaves",opts->nOctaves);

	return opts;
}

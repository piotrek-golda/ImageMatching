//
// Created by piotrek on 15.05.16.
//

#include <typeinfo>
#include <opencv2/nonfree/features2d.hpp>
#include "SURF_detector.h"

void SURF_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	SURF_detectorOptions opts;
	try
	{
		opts = static_cast< SURF_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}


	cv::SurfFeatureDetector detector(opts.hessianThreshold,opts.nOctaves,opts.nOctaveLayers,opts.extended,opts.upright);
	detector.detect(image, key_points, cv::Mat() );
}

DetectorOptions *SURF_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	SURF_detectorOptions* opts = new SURF_detectorOptions();

	opts->nOctaves = cfgFile.GetInteger(section, "nOctaves",opts->nOctaves);
	opts->nOctaveLayers = cfgFile.GetInteger(section, "nOctaveLayers",opts->nOctaveLayers);
	opts->hessianThreshold = (float)cfgFile.GetReal(section, "hessianThreshold",opts->hessianThreshold);
	opts->extended = cfgFile.GetBoolean(section, "extended",opts->extended);
	opts->upright = cfgFile.GetBoolean(section, "upright",opts->upright);

	return opts;
}

const char *SURF_detector::getName()
{
	return this->detector_name;
}

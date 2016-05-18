//
// Created by piotrek on 08.05.16.
//

#include <exception>
#include <typeinfo>

#include "ORB_detector.h"

void ORB_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions& options)
{
	ORB_detectorOptions opts;
	try
	{
		opts = static_cast< ORB_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}

	cv::OrbFeatureDetector detector(opts.nfeatures,opts.scaleFactor,opts.nlevels,opts.edgeThreshold,opts.firstLevel,opts.WTA_K,opts.scoreType,opts.patchSize);

	detector.detect(image, key_points, cv::Mat() );

}

DetectorOptions *ORB_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	ORB_detectorOptions* opts = new ORB_detectorOptions();

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

const char *ORB_detector::getName()
{
	return this->detector_name;
}

//
// Created by piotrek on 14.05.16.
//

#include <typeinfo>
#include <iostream>
#include <opencv2/nonfree/features2d.hpp>
#include "SIFT_detector.h"

void SIFT_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	SIFT_detectorOptions opts;
	try
	{
		opts = static_cast< SIFT_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}


	cv::SiftFeatureDetector detector(opts.nfeatures,opts.nOctaveLayers,opts.contrastThreshold,opts.edgeThreshold,opts.sigma);
	detector.detect(image, key_points, cv::Mat() );

}

DetectorOptions *SIFT_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	SIFT_detectorOptions* opts = new SIFT_detectorOptions();

	opts->nfeatures = cfgFile.GetInteger(section, "nfeatures",opts->nfeatures);
	opts->nOctaveLayers = cfgFile.GetInteger(section, "nOctaveLayers",opts->nOctaveLayers);
	opts->contrastThreshold = (float)cfgFile.GetReal(section, "contrastThreshold",opts->contrastThreshold);
	opts->edgeThreshold = (float)cfgFile.GetReal(section, "edgeThreshold",opts->edgeThreshold);
	opts->sigma = (float)cfgFile.GetReal(section, "sigma",opts->sigma);

	return opts;
}

const char *SIFT_detector::getName()
{
	return this->detector_name;
}

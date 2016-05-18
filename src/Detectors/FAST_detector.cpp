//
// Created by piotrek on 15.05.16.
//

#include <typeinfo>
#include "FAST_detector.h"

void FAST_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	FAST_detectorOptions opts;
	try
	{
		opts = static_cast< FAST_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}

	cv::FastFeatureDetector detector(opts.threshold,opts.nonmaxSuppression);

	detector.detect(image, key_points, cv::Mat() );
}

DetectorOptions *FAST_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	FAST_detectorOptions* opts = new FAST_detectorOptions();

	opts->threshold = cfgFile.GetInteger(section, "threshold",opts->threshold);
	opts->nonmaxSuppression = cfgFile.GetBoolean(section, "nonmaxSuppression",opts->nonmaxSuppression);

	return opts;
}

const char* FAST_detector::getName()
{
	return this->detector_name;
}

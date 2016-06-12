//
// Created by piotrek on 12.06.16.
//

#include <typeinfo>
#include "AGAST_detector.h"

const char *AGAST_detector::getName()
{
	return this->detector_name;
}

void AGAST_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	AGAST_detectorOptions opts;
	try
	{
		opts = static_cast< AGAST_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}

	cv::Ptr<AgastFeatureDetector> detector = AgastFeatureDetector::create(opts.threshold,opts.nonmaxSuppression, opts.type);
	detector->detect(image, key_points, cv::Mat() );
}

DetectorOptions *AGAST_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	AGAST_detectorOptions* opts = new AGAST_detectorOptions();

	opts->threshold = cfgFile.GetInteger(section, "threshold",opts->threshold);
	opts->nonmaxSuppression = cfgFile.GetBoolean(section, "nonmaxSuppression",opts->nonmaxSuppression);
	opts->type = cfgFile.GetInteger(section, "type",opts->type);

	return opts;
}

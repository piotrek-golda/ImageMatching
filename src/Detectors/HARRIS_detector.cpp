//
// Created by piotrek on 11.06.16.
//

#include <typeinfo>
#include "HARRIS_detector.h"

const char *HARRIS_detector::getName()
{
	return this->detector_name;
}

void HARRIS_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	HARRIS_detectorOptions opts;
	try
	{
		opts = static_cast< HARRIS_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}

	cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create("HARRIS");

	detector->set("k", opts.k);
	detector->set("minDistance", opts.minDistance);
	detector->set("qualityLevel", opts.qualityLevel);
	detector->set("nfeatures", opts.nfeatures);


	detector->detect(image, key_points, cv::Mat() );

}

DetectorOptions *HARRIS_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	HARRIS_detectorOptions* opts = new HARRIS_detectorOptions();

	opts->k = cfgFile.GetReal(section, "k",opts->k);
	opts->minDistance = cfgFile.GetReal(section, "minDistance",opts->minDistance);
	opts->qualityLevel = cfgFile.GetReal(section, "qualityLevel",opts->qualityLevel);
	opts->nfeatures = cfgFile.GetInteger(section, "nfeatures",opts->nfeatures);

	return opts;
}

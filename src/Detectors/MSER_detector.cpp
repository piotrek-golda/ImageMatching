//
// Created by piotrek on 11.06.16.
//

#include <typeinfo>
#include "MSER_detector.h"

DetectorOptions *MSER_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	MSER_detectorOptions* opts = new MSER_detectorOptions();

	opts->delta = cfgFile.GetInteger(section, "delta",opts->delta);
	opts->minArea = cfgFile.GetInteger(section, "minArea",opts->minArea);
	opts->maxArea = cfgFile.GetInteger(section, "maxArea",opts->maxArea);
	opts->edgeBlurSize = cfgFile.GetInteger(section, "edgeBlurSize",opts->edgeBlurSize);
	opts->maxEvolution = cfgFile.GetInteger(section, "maxEvolution",opts->maxEvolution);
	opts->maxVariation = (float)cfgFile.GetReal(section, "maxVariation",opts->maxVariation);
	opts->minDiversity = (float)cfgFile.GetReal(section, "minDiversity",opts->minDiversity);
	opts->areaThreshold = cfgFile.GetReal(section, "areaThreshold",opts->areaThreshold);
	opts->minMargin = cfgFile.GetReal(section, "minMargin",opts->minMargin);

	return opts;
}

const char *MSER_detector::getName()
{
	return this->detector_name;
}

void MSER_detector::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	MSER_detectorOptions opts;
	try
	{
		opts = static_cast< MSER_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}

	cv::Ptr<cv::FeatureDetector> detector = cv::FeatureDetector::create("MSER");
	detector->set("delta", opts.delta);
	detector->set("minArea", opts.minArea);
	detector->set("maxArea", opts.maxArea);
	detector->set("maxVariation", opts.maxVariation);
	detector->set("minDiversity", opts.minDiversity);
	detector->set("maxEvolution", opts.maxEvolution);
	detector->set("areaThreshold", opts.areaThreshold);
	detector->set("minMargin", opts.minMargin);
	detector->set("edgeBlurSize", opts.edgeBlurSize);
	detector->detect(image, key_points, cv::Mat() );

}

//
// Created by piotrek on 15.05.16.
//

#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <typeinfo>
#include "BruteForceDescriptionsMatcher.h"


void BruteForceDescriptionsMatcher::match(cv::Mat& descriptions1, cv::Mat &descriptions2,
										  std::vector<std::pair<int, int> > &matches, DescriptionsMatcherOptions &options)
{
	BruteForceDescriptionsMatcherOptions opts;
	try
	{
		opts = static_cast< BruteForceDescriptionsMatcherOptions & >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->matcher_name << "!\n";
		exit(1);
	}

	if( ( opts.normType == cv::NORM_HAMMING || opts.normType == cv::NORM_HAMMING2 )&& descriptions1.type() != CV_8U )
	{

		std::cerr<< "DETECTION:\t" << "Wrong settings, use other norm for this descriptor!\n";
		exit(1);
	}

	cv::DescriptorMatcher* matcher = new cv::BFMatcher(opts.normType, opts.crossCheck);
	std::vector< cv::DMatch > matchesCV;

	matcher->match( descriptions1 , descriptions2 , matchesCV );
	delete matcher;
	for(int i = 0; i < matchesCV.size(); ++i)
	{
		matches.push_back( std::pair<int,int>(matchesCV[i].queryIdx,matchesCV[i].trainIdx) );
	}
}

DescriptionsMatcherOptions *BruteForceDescriptionsMatcherOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	BruteForceDescriptionsMatcherOptions * opts = new BruteForceDescriptionsMatcherOptions();

	opts->normType = cfgFile.GetInteger(section, "normType",opts->normType);
	opts->crossCheck = cfgFile.GetBoolean(section, "crossCheck",opts->crossCheck);

	return opts;
}

const char *BruteForceDescriptionsMatcher::getName()
{
	return this->matcher_name;
}

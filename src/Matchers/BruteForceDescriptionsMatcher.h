//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_BFMATCHER_H
#define DESCRIPTORDETECTOR_TESTER_BFMATCHER_H


#include "../Interfaces/DescriptionsMatcher.h"

class BruteForceDescriptionsMatcherOptions : public DescriptionsMatcherOptions
{
public:
	int normType=cv::NORM_L2; //2 = NORM_L1, 4 = NORM_L2, 6 = NORM_HAMMING, 7 = NORM_HAMMING2
	bool crossCheck=false;

	virtual DescriptionsMatcherOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class BruteForceDescriptionsMatcher : public DescriptionsMatcher
{
private:
	const char* matcher_name = "BruteForceDescriptionsMatcher";

public:
	virtual const char *getName();

	virtual void match(cv::Mat& descriptions1, cv::Mat &descriptions2,
					   std::vector<std::pair<int, int> > &matches, DescriptionsMatcherOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_BFMATCHER_H

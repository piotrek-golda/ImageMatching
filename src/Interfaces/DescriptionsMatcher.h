//
// Created by piotrek on 13.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_DESCRIPTIONSMATCHER_H
#define DESCRIPTORDETECTOR_TESTER_DESCRIPTIONSMATCHER_H

#include <string>
#include <vector>
#include "../INIReader/INIReader.h"

class DescriptionsMatcherOptions
{
public:
	virtual DescriptionsMatcherOptions* getConfiguration(INIReader cfgFile, std::string section ) = 0;
};

class DescriptionsMatcher
{

public:

	virtual const char* getName() = 0;

	virtual void match(cv::Mat& descriptions1, cv::Mat& descriptions2,
					   std::vector<std::pair<int,int> >&matches, DescriptionsMatcherOptions& options) = 0;


};


#endif //DESCRIPTORDETECTOR_TESTER_DESCRIPTIONSMATCHER_H

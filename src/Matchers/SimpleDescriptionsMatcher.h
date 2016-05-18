//
// Created by piotrek on 14.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SIMPLEDESCRIPTIONSMATCHER_H
#define DESCRIPTORDETECTOR_TESTER_SIMPLEDESCRIPTIONSMATCHER_H

#include <string>
#include "../Interfaces/DescriptionsMatcher.h"

double euclidean_distance( std::vector<float>& lhs, std::vector<float>& rhs);

class SimpleDescriptionsMatcherOptions : public DescriptionsMatcherOptions
{
public:

	virtual DescriptionsMatcherOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class SimpleDescriptionsMatcher : public DescriptionsMatcher
{
private:
	const char* matcher_name = "SimpleDescriptionsMatcher";

public:

	virtual const char *getName();

	virtual void match( cv::Mat &descriptions1, cv::Mat &descriptions2,
					   std::vector<std::pair<int, int> > &matches, DescriptionsMatcherOptions &options);
};


#endif //DESCRIPTORDETECTOR_TESTER_SIMPLEDESCRIPTIONSMATCHER_H

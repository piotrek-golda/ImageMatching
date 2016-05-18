//
// Created by piotrek on 14.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SIMPLEKEYSMATCHER_H
#define DESCRIPTORDETECTOR_TESTER_SIMPLEKEYSMATCHER_H


#include "../Interfaces/KeysMatcher.h"

class SimpleKeysMatcherOptions : public KeysMatcherOptions
{
public:
	float epsilon = 1.;

	virtual KeysMatcherOptions *getConfiguration(INIReader cfgFile, std::string section);
};


class SimpleKeysMatcher : public KeysMatcher
{
private:
	const char* matcher_name = "SimpleKeysMatcher";

public:
	virtual const char *getName();

	virtual void match(std::vector<cv::Point2f> &key_points1, std::vector<cv::KeyPoint> &key_points2,
					   std::vector<std::pair<int, int> > &matches, KeysMatcherOptions &options) override;
};


#endif //DESCRIPTORDETECTOR_TESTER_SIMPLEKEYSMATCHER_H

//
// Created by piotrek on 13.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_MATCHER_H
#define DESCRIPTORDETECTOR_TESTER_MATCHER_H

#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>

#include "../INIReader/INIReader.h"


class KeysMatcherOptions
{
public:
	virtual KeysMatcherOptions* getConfiguration(INIReader cfgFile, std::string section ) = 0;
};


class KeysMatcher
{
public:

public:

	virtual const char* getName() = 0;

	virtual void match( std::vector< cv::Point2f >& key_points1, std::vector< cv::KeyPoint >& key_points2,
						   std::vector< std::pair<int,int> >& matches, KeysMatcherOptions& options ) = 0;

};


#endif //DESCRIPTORDETECTOR_TESTER_MATCHER_H

//
// Created by piotrek on 14.05.16.
//

#include <typeinfo>
#include <iostream>
#include "SimpleKeysMatcher.h"

#define DISTANCE(x1,x2,y1,y2) (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)

void SimpleKeysMatcher::match(std::vector<cv::Point2f> &key_points1, std::vector<cv::KeyPoint> &key_points2,
							  std::vector<std::pair<int, int> > &matches, KeysMatcherOptions &options)
{
	SimpleKeysMatcherOptions opts;
	try
	{
		opts = static_cast< SimpleKeysMatcherOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "MATCHING:\t" << "Error while casting options object in " << this->matcher_name << "!\n";
		exit(1);
	}

	float eps = opts.epsilon * opts.epsilon;

	for(int i = 0; i < key_points1.size(); ++i)
		for(int j = 0; j < key_points2.size(); ++j)
		{

			if( DISTANCE( key_points1[i].x, key_points2[j].pt.x, key_points1[i].y, key_points2[j].pt.y ) <= eps )
			{
				matches.push_back( std::pair<int,int>(i,j) );
			}
		}

}

KeysMatcherOptions *SimpleKeysMatcherOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	SimpleKeysMatcherOptions* opts = new SimpleKeysMatcherOptions();

	opts->epsilon = (float)cfgFile.GetReal(section, "epsilon",opts->epsilon);

	return opts;
}

const char *SimpleKeysMatcher::getName()
{
	return this->matcher_name;
}

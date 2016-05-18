//
// Created by piotrek on 14.05.16.
//

#include <typeinfo>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <opencv2/features2d/features2d.hpp>
#include "SimpleDescriptionsMatcher.h"

double euclidean_distance( std::vector<float>& lhs, std::vector<float>& rhs)
{
	double dist = 0.0;
	if(lhs.size() != rhs.size())
	{
		std::cerr<< "MATCHING:\t" << "Error while computing distance. " << "vectors are different size" << "!\n";
		exit(1);
	}

	for(int i = 0; i < lhs.size(); ++i)
	{
		dist += (double)(lhs[i] - rhs[i])*(lhs[i] - rhs[i]);
	}

	return dist;
}


void SimpleDescriptionsMatcher::match(cv::Mat &descriptions1,
									  cv::Mat &descriptions2,
									  std::vector<std::pair<int, int> > &matches, DescriptionsMatcherOptions &options)
{
	SimpleDescriptionsMatcherOptions opts;
	try
	{
		opts = static_cast< SimpleDescriptionsMatcherOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "MATCHING:\t" << "Error while casting options object in " << this->matcher_name << "!\n";
		exit(1);
	}


//	std::pair<int,double>* desc1_distances = new std::pair<int,double>[ descriptions1.size() ];
//	std::pair<int,double>* desc2_distances = new std::pair<int,double>[ descriptions2.size() ];

//	for(int i = 0; i < descriptions1.size(); ++i)
//		desc1_distances[i] = std::pair<int,double>(-1,0.0);
//	for(int i = 0; i < descriptions2.size(); ++i)
//		desc2_distances[i] = std::pair<int,double>(-1,0.0);
//
//	double dist;
//
//	for(int i = 0; i < descriptions1.size(); ++i)
//		for(int j = 0; j < descriptions2.size(); ++j)
//		{
//			dist = euclidean_distance( descriptions1[i], descriptions2[j] );
//			if(desc1_distances[i].first == -1)
//			{
//				desc1_distances[i].first = j;
//				desc1_distances[i].second = dist;
//			}
//			else if(desc1_distances[i].second > dist)
//			{
//				desc1_distances[i].first = j;
//				desc1_distances[i].second = dist;
//			}
//
//			if(desc2_distances[j].first == -1)
//			{
//				desc2_distances[j].first = i;
//				desc2_distances[j].second = dist;
//			}
//			else if(desc2_distances[j].second > dist)
//			{
//				desc2_distances[j].first = i;
//				desc2_distances[j].second = dist;
//			}
//		}
//
//	for(int i = 0; i < descriptions1.size(); ++i)
//	{
//		if( desc2_distances[ desc1_distances[i].first ].first == i )
//		{
//			matches.push_back( std::pair<int,int>(i, desc1_distances[i].first ) );
//		}
//	}

//	delete[] desc1_distances;
//	delete[] desc2_distances;
}

DescriptionsMatcherOptions *SimpleDescriptionsMatcherOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	SimpleDescriptionsMatcherOptions* opts = new SimpleDescriptionsMatcherOptions();

	return opts;
}

const char *SimpleDescriptionsMatcher::getName()
{
	return this->matcher_name;
}

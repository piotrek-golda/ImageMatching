//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_ORB_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_ORB_DESCRIPTOR_H


#include <opencv2/features2d/features2d.hpp>
#include "../Interfaces/Descriptor.h"
#include "../Interfaces/DescriptorOptions.h"


class ORB_descriptorOptions : public DescriptorOptions
{
public:
	int nfeatures=500;
	float scaleFactor=1.2f;
	int nlevels=8;
	int edgeThreshold=31;
	int firstLevel=0;
	int WTA_K=2;
	int scoreType=cv::ORB::HARRIS_SCORE;
	int patchSize=31;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);
};


class ORB_descriptor : public Descriptor
{
private:

	const char* descriptor_name = "ORBDescriptor";

public:

	virtual const char *getName();

	virtual void describe( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						   cv::Mat& descriptions, DescriptorOptions& options );


};




#endif //DESCRIPTORDETECTOR_TESTER_ORB_DESCRIPTOR_H

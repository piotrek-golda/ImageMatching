//
// Created by piotrek on 02.10.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_MULTI_DESCRIPTOR_H
#define DESCRIPTORDETECTOR_TESTER_MULTI_DESCRIPTOR_H

#include "../Interfaces/DescriptorOptions.h"
#include "../Interfaces/Descriptor.h"

enum CV_NORM
{
	NORM_MINMAX=32
};

struct DescriptorWrapper
{
	Descriptor* dsc;
	DescriptorOptions* dscOpt;
};

class MULTI_descriptorOptions : public DescriptorOptions
{
public:
	CV_NORM normType = CV_NORM::NORM_MINMAX; // 32=CV_NORM::NORM_MINMAX;
	int singleDescriptionLength = 128;

	virtual DescriptorOptions *getConfiguration(INIReader cfgFile, std::string section);
};

class MULTI_descriptor : public Descriptor
{
private:
	std::string name= "";
	std::vector< DescriptorWrapper > descriptors;

public:

	virtual ~MULTI_descriptor();

	void append( DescriptorWrapper );

	virtual const char *getName();

	virtual void describe( cv::Mat& image, std::vector< cv::KeyPoint >& key_points,
						   cv::Mat& descriptions, DescriptorOptions& options );

	void removeKeyDescription(std::vector<cv::Mat>& descriptions, unsigned int keyIdx, unsigned int outputsNumber);

	void removeRow(cv::Mat &matIn, unsigned int row, cv::Mat &matOut);
};


#endif //DESCRIPTORDETECTOR_TESTER_MULTI_DESCRIPTOR_H

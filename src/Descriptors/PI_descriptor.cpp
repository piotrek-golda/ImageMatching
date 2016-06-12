//
// Created by piotrek on 17.05.16.
//

#include <typeinfo>
#include <iomanip>
#include "PI_descriptor.h"
#include "../Interfaces/PatchExtractor.h"
#include "../Extractors/SimplePatchExtractor.h"
#include "../Helpers.h"

const char *PI_descriptor::getName()
{
	return this->descriptor_name;
}

void PI_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
							 DescriptorOptions &options)
{
	PI_descriptorOptions opts;
	try
	{
		opts = static_cast< PI_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}
	std::pair<double,double>* limits = NULL;
	if( opts.minDiagramLimits < opts.maxDiagramLimits )
	{
		limits = new std::pair<double,double>(opts.minDiagramLimits, opts.maxDiagramLimits);
	}
	PI::PersistantImageParams params;
	params.normType = opts.normType;
	params.weighting = opts.weighting;
	params.ignoreOutliers = opts.ignoreOutliers;
	params.diagramLimits = limits;
	params.resolution = opts.resolution;
	params.sigma = opts.sigma;

//	this->filterBoundKeyPoints(key_points,opts.patchSize,image.cols,image.rows);

	PatchExtractor* extractor =  new SimplePatchExtractor();

	double* patch = new double[opts.patchSize*opts.patchSize];
	double** dscs = new double*[key_points.size()];
	int dscSize;

#pragma omp parallel for
	for(int i = 0; i < key_points.size(); ++i)
	{
		extractor->extract(image,key_points[i],patch,opts.patchSize, opts.scaling, opts.rotating);
		PI::feature_persistence_image(opts.patchSize,opts.patchSize,patch,NULL,params,dscs[i],dscSize);
	}
	cv::Mat descriptionsDouble = cv::Mat(key_points.size(),dscSize,CV_64F);
	descriptions = cv::Mat(key_points.size(),dscSize,CV_32F);
	for(int i = 0; i < key_points.size(); ++i)
		for(int j = 0; j < dscSize; ++j)
			descriptions.at<float>(i,j) = (float)dscs[i][j];

	for(int i = 0; i < key_points.size(); ++i)
	{
		delete[] dscs[i];
	}
	delete[] dscs;

	delete patch;
	if(limits)
	{
		delete limits;
	}
}

void PI_descriptor::filterBoundKeyPoints(std::vector<cv::KeyPoint> &kpoints, int patchSize, int imgCols, int imgRows)
{
	float x;
	float y;
	cv::Rect bound;
	for(int i = 0; i < kpoints.size(); ++i)
	{
		x = kpoints[i].pt.x;
		y = kpoints[i].pt.y;
		bound = cv::Rect(x-patchSize/2,y-patchSize/2,patchSize,patchSize);
		if( bound.x < 0
			|| bound.y < 0
			|| bound.x + bound.width > imgCols
			|| bound.y + bound.height > imgRows )
		{
			kpoints[i] = kpoints[kpoints.size()-1];
			kpoints.pop_back();
			--i;
		}
	}
}


DescriptorOptions *PI_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	PI_descriptorOptions* opts = new PI_descriptorOptions();

	opts->patchSize = cfgFile.GetInteger(section, "patchSize",opts->patchSize);
	opts->resolution = (unsigned int)cfgFile.GetInteger(section, "resolution",opts->resolution);
	opts->normType = static_cast<PI::NormType>( cfgFile.GetInteger(section, "normType",opts->normType) );
	opts->maxDiagramLimits = cfgFile.GetReal(section, "maxDiagramLimits",opts->maxDiagramLimits);
	opts->minDiagramLimits = cfgFile.GetReal(section, "minDiagramLimits",opts->minDiagramLimits);
	opts->sigma = cfgFile.GetReal(section, "sigma",opts->sigma);
	opts->ignoreOutliers = cfgFile.GetBoolean(section, "ignoreOutliers",opts->ignoreOutliers);
	opts->weighting = cfgFile.GetBoolean(section, "weighting",opts->weighting);
	opts->scaling = cfgFile.GetBoolean(section, "scaling",opts->scaling);
	opts->rotating = cfgFile.GetBoolean(section, "rotating",opts->rotating);

	return opts;
}

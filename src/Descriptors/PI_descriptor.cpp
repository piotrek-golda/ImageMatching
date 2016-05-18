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

	this->filterBoundKeyPoints(key_points,opts.patchSize,image.cols,image.rows);

	PatchExtractor* extractor =  new SimplePatchExtractor();

	double* patch = new double[opts.patchSize*opts.patchSize];
	double** dscs = new double*[key_points.size()];
	int dscSize;

	for(int i = 0; i < key_points.size(); ++i)
	{
		extractor->extract(image,key_points[i],patch,opts.patchSize);
//		std::string name = "patch0.csv";
//		name[5] = i + '0';
//		cv::FileStorage file(name.c_str(), cv::FileStorage::WRITE);
//		cv::Mat p(opts.patchSize,opts.patchSize,CV_64F, patch);
//		file << "patch" << p;
		PI::feature_persistence_image(opts.patchSize,opts.patchSize,patch,NULL,params,dscs[i],dscSize);
//		std::cout << std::fixed;
//		std::cout << std::setprecision(5);
//		for(int j = 0; j < dscSize; ++j)
//			std::cout << dscs[i][j] <<' ';
//		std::cout << std::endl;
//		cv::Mat ds(1,dscSize,CV_64F, dscs[i]);
//		file << "description" << ds;
	}

	cv::Mat descriptionsDouble = cv::Mat(key_points.size(),dscSize,CV_64F);
	descriptions = cv::Mat(key_points.size(),dscSize,CV_32F);
	for(int i = 0; i < key_points.size(); ++i)
		for(int j = 0; j < dscSize; ++j)
			descriptions.at<float>(i,j) = (float)dscs[i][j];
//	descriptionsDouble.convertTo(descriptions,CV_32F);

//	matTo8u(descriptionsDouble,descriptions);

//	double rnd;
//	for(int i = 0; i < descriptionsDouble.rows; i++)
//		for(int j = 0; j < descriptionsDouble.cols; j++)
//		{
//			rnd = round(descriptionsDouble.at<double>(i,j)) ;
//			if(rnd > (double)std::numeric_limits<int>::max()
//					|| rnd < (double)std::numeric_limits<int>::min() )
//			{
//				descriptionsDouble.at<double>(i,j) = 0.;
//			}
//			else
//			{
//				descriptionsDouble.at<double>(i,j) = round(descriptionsDouble.at<double>(i,j)) ;
//			}
//		}

//	std::cout<<descriptions <<std::endl;
//
//	double min;
//	double max;
//	cv::minMaxLoc(descriptionsDouble, &min, &max);
//	std::cout<< (descriptionsDouble.type() == CV_64F) << std::endl;
//	std::cout<<min <<' '<<max;

//	getchar();

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

	return opts;
}

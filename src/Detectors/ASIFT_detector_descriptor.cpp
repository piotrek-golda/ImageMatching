//
// Created by piotrek on 12.06.16.
//

#include <typeinfo>
#include "ASIFT_detector_descriptor.h"
#include "ASIFT/demo_lib_sift.h"
#include "ASIFT/compute_asift_keypoints.h"
#include "../Helpers.h"

const char *ASIFT_detector_descriptor::getName()
{
	return this->detector_name;
}

void ASIFT_detector_descriptor::detect(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, DetectorOptions &options)
{
	ASIFT_detectorOptions opts;
	try
	{
		opts = static_cast< ASIFT_detectorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DETECTION:\t" << "Error while casting options object in " << this->detector_name << "!\n";
		exit(1);
	}

	siftPar siftparameters = opts.getSiftParams();
	cv::Mat grayImage;
	cv::cvtColor(image, grayImage, CV_BGR2GRAY);

	vector<float> imgV;
	matToVector( grayImage, imgV );

	imgV.push_back(0.);

	vector< vector< keypointslist > > keys;

	int verb=0;
	compute_asift_keypoints(imgV, image.cols, image.rows, opts.num_of_tilts, verb, keys, siftparameters );

	keypointslist localKeysCopy;

	for(int i = 0; i < keys.size(); ++i)
		for(int j = 0; j < keys[i].size(); ++j)
			for(int k = 0; k < keys[i][j].size(); ++k)
			{
				localKeysCopy.push_back(keys[i][j][k]);
			}
	std::random_shuffle(localKeysCopy.begin(),localKeysCopy.end());

	while(localKeysCopy.size() > opts.nfeatures)
	{
		localKeysCopy.pop_back();
	}

	key_points.resize(localKeysCopy.size());
	#pragma omp critical(keysCopy)
	{
		int r = keysCopy.size();
		keysCopy.resize(keysCopy.size() + localKeysCopy.size());
		for(int i = 0; i < localKeysCopy.size();++i)
		{
			key_points[i] = ( cv::KeyPoint(cv::Point2f( localKeysCopy[i].x, localKeysCopy[i].y ),localKeysCopy[i].scale,localKeysCopy[i].angle,0.,0, r));
			keysCopy[r++] = localKeysCopy[i];
		}
	}
}

siftPar ASIFT_detectorOptions::getSiftParams() const
{
	siftPar siftparameters;

	siftparameters.OctaveMax=OctaveMax;
	siftparameters.DoubleImSize = DoubleImSize;
	siftparameters.order = order;
	siftparameters.InitSigma = InitSigma;
	siftparameters.BorderDist = BorderDist;
	siftparameters.Scales = Scales;
	siftparameters.PeakThresh = PeakThresh;
	siftparameters.EdgeThresh = EdgeThresh;
	siftparameters.EdgeThresh1 = EdgeThresh1;
	siftparameters.OriBins  = OriBins;
	siftparameters.OriSigma = OriSigma;
	siftparameters.OriHistThresh = OriHistThresh;
	siftparameters.MaxIndexVal = MaxIndexVal;
	siftparameters.MagFactor  = MagFactor;
	siftparameters.IndexSigma  = IndexSigma;
	siftparameters.IgnoreGradSign = IgnoreGradSign;
	siftparameters.MatchRatio =MatchRatio;
	siftparameters.MatchXradius = MatchXradius;
	siftparameters.MatchYradius = MatchYradius;

	siftparameters.noncorrectlylocalized = noncorrectlylocalized;

	return siftparameters;
}

DetectorOptions *ASIFT_detectorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	ASIFT_detectorOptions* opts = new ASIFT_detectorOptions();

	//ordinary sift params
	opts->OctaveMax = cfgFile.GetInteger(section, "OctaveMax",opts->OctaveMax);
	opts->DoubleImSize = cfgFile.GetInteger(section, "DoubleImSize",opts->DoubleImSize);
	opts->order = cfgFile.GetInteger(section, "order",opts->order);
	opts->InitSigma = (float)cfgFile.GetReal(section, "InitSigma",opts->InitSigma);
	opts->BorderDist = cfgFile.GetInteger(section, "BorderDist",opts->BorderDist);
	opts->Scales = cfgFile.GetInteger(section, "Scales",opts->Scales);
	opts->PeakThresh = (float)cfgFile.GetReal(section, "PeakThresh",opts->PeakThresh);
	opts->EdgeThresh = (float)cfgFile.GetReal(section, "EdgeThresh",opts->EdgeThresh);
	opts->EdgeThresh1 = (float)cfgFile.GetReal(section, "EdgeThresh1",opts->EdgeThresh1);
	opts->OriBins = cfgFile.GetInteger(section, "OriBins",opts->OriBins);
	opts->OriSigma = (float)cfgFile.GetReal(section, "OriSigma",opts->OriSigma);
	opts->OriHistThresh = (float)cfgFile.GetReal(section, "OriHistThresh",opts->OriHistThresh);
	opts->MaxIndexVal = (float)cfgFile.GetReal(section, "MaxIndexVal",opts->MaxIndexVal);
	opts->MagFactor = cfgFile.GetInteger(section, "MagFactor",opts->MagFactor);
	opts->IndexSigma = (float)cfgFile.GetReal(section, "IndexSigma",opts->IndexSigma);
	opts->IgnoreGradSign = cfgFile.GetInteger(section, "IgnoreGradSign",opts->IgnoreGradSign);
	opts->MatchRatio = (float)cfgFile.GetReal(section, "MatchRatio",opts->MatchRatio);
	opts->MatchXradius = (float)cfgFile.GetReal(section, "MatchXradius",opts->MatchXradius);
	opts->MatchYradius = (float)cfgFile.GetReal(section, "MatchYradius",opts->MatchYradius);
	opts->noncorrectlylocalized = cfgFile.GetInteger(section, "noncorrectlylocalized",opts->noncorrectlylocalized);

	//asift params
	opts->num_of_tilts = cfgFile.GetInteger(section, "num_of_tilts",opts->num_of_tilts);

	return opts;
}

DescriptorOptions *ASIFT_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	return new ASIFT_descriptorOptions();;
}

void ASIFT_detector_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
										 DescriptorOptions &options)
{
	ASIFT_descriptorOptions opts;
	try
	{
		opts = static_cast< ASIFT_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->descriptor_name << "!\n";
		exit(1);
	}

	descriptions = cv::Mat(0,VecLength,CV_8UC1);

	for(int i = 0; i < key_points.size(); ++i)
	{
		cv::Mat desc = cv::Mat();
		arrTo8UC1Mat(keysCopy[key_points[i].class_id].vec, VecLength, desc );
		descriptions.push_back(desc);

	}
}

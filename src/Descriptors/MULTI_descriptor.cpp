//
// Created by piotrek on 02.10.16.
//

#include <typeinfo>
#include "MULTI_descriptor.h"

const char *MULTI_descriptor::getName()
{
	std::stringstream names;
	names << "<multi: ";
	for( auto dsc : descriptors )
	{
		names << dsc.dsc->getName() << ' ';
	}
	names << ">";
	name = names.str();
	return name.c_str();
}

void MULTI_descriptor::describe(cv::Mat &image, std::vector<cv::KeyPoint> &key_points, cv::Mat &descriptions,
								DescriptorOptions &options)
{
	MULTI_descriptorOptions opts;
	try
	{
		opts = static_cast< MULTI_descriptorOptions& >(options);
	}
	catch(const std::bad_cast& e)
	{
		std::cerr<< "DESCRIPTION:\t" << "Error while casting options object in " << this->getName() << "!\n";
		exit(1);
	}

	std::vector<cv::Mat> output;
	output.resize( descriptors.size() );
	for( unsigned i = 0; i < descriptors.size(); ++i )
	{
		cv::Mat out;
		descriptors[i].dsc->describe(image,key_points,output[i], *(descriptors[i].dscOpt) );
		output[i].convertTo(output[i], CV_32F);

		std::cout << "Mat size: " << output[i].size() << std::endl;
//		std::cout << output[i] << "\n\n";
		cv::Size size{ output[i].size() };
		size.width = opts.singleDescriptionLength;
		cv::resize( output[i], out, size );
		std::cout << "Mat size after resize: " << out.size() << std::endl;
//		std::cout << out << "\n\n";

		output[i] = cv::Mat(0,opts.singleDescriptionLength, output[i].type());
//		cv::resize( output[i], output[i], cv::Size(0, opts.singleDescriptionLength ) );
		cv::Mat temp;
		for (int j = 0; j <= out.rows - 1; j++)
		{
			cv::normalize( out.row(j), temp, 0.0, 256.0, opts.normType );
			output[i].push_back(temp);
		}
//		std::cout << output[i] << "\n\n";
//		cv::waitKey(0);
	}
//	cv::Mat combined;

//	std::cout << output[0].type() << ' ' << output[1].type() << std::endl;
	hconcat(output, descriptions);
//	for( auto out : output )
//	{
//		cv::hconcat( descriptions, out, descriptions );
//	}
//	std::cout << "Final Mat size: " << descriptions.size() << std::endl;
}

MULTI_descriptor::~MULTI_descriptor()
{
	for(auto descriptor : descriptors )
	{
		delete descriptor.dsc;
		delete descriptor.dscOpt;
	}
}

DescriptorOptions *MULTI_descriptorOptions::getConfiguration(INIReader cfgFile, std::string section)
{
	MULTI_descriptorOptions* opts = new MULTI_descriptorOptions();
	opts->normType = static_cast<CV_NORM>( cfgFile.GetInteger(section, "normType",opts->normType) );
	opts->singleDescriptionLength = cfgFile.GetInteger(section, "singleDescriptionLength",opts->singleDescriptionLength);

	return opts;
}

void MULTI_descriptor::append(DescriptorWrapper wrapper)
{
	descriptors.push_back( wrapper );
}

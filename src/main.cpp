#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <ctime>
#include "ProgramFlowFacade.h"
#include "Interfaces/FacadeAbstractFactory.h"
#include "FacadeFactory.h"
#include "Detectors/ASIFT/compute_asift_keypoints.h"
#include "DataCollector.h"


void printParams( cv::Algorithm* algorithm ) {
	std::vector<std::string> parameters;
	algorithm->getParams(parameters);

	for (int i = 0; i < (int) parameters.size(); i++) {
		std::string param = parameters[i];
		int type = algorithm->paramType(param);
		std::string helpText = algorithm->paramHelp(param);
		std::string typeText;

		switch (type) {
			case cv::Param::BOOLEAN:
				typeText = "bool";
				break;
			case cv::Param::INT:
				typeText = "int";
				break;
			case cv::Param::REAL:
				typeText = "real (double)";
				break;
			case cv::Param::STRING:
				typeText = "string";
				break;
			case cv::Param::MAT:
				typeText = "Mat";
				break;
			case cv::Param::ALGORITHM:
				typeText = "Algorithm";
				break;
			case cv::Param::MAT_VECTOR:
				typeText = "Mat vector";
				break;
		}
		std::cout << "Parameter '" << param << "' type=" << typeText << " help=" << helpText << std::endl;
	}
}


cv::Mat ReadMatFromTxt(std::string filename, int rows,int cols)
{
	double m;
	cv::Mat out = cv::Mat_<double>(rows,cols);//Matrix to store values

	std::ifstream fileStream(filename);
	int cnt = 0;//index starts from 0
	while (fileStream >> m)
	{
		int temprow = cnt / cols;
		int tempcol = cnt % cols;
		out.at<double>(temprow, tempcol) = m;
		cnt++;
	}
	return out;
}

int main(int argc, char** argv )
{
	if ( argc != 6 )
	{
		std::cout<< "usage: ./" << argv[0]
		<< " <mainConfig_File_Path> <detectionDescriptionConfig_File_Path> <matchingConfig_File_Path> <outTimeFile> <outResultFile>"
		<< "\n";
		exit(1);
	}
	std::srand ( unsigned ( std::time(0) ) );

	DataCollector& collector = DataCollector::getDataCollector();
	std::string image1Path;
	std::string image2Path;
	std::string homographyPath;


	FacadeAbstractFactory *factory = new FacadeFactory();
	ProgramFlowFacade *facade = factory->constructFacade(argv[1], argv[2], argv[3]);

	cout << "enter <Image1_Path> <Image2_Path> <Homography_File_Path> or 'q' if You want to finish\n";
	do
	{

		std::cin >> image1Path;
		if(image1Path.compare("q") == 0)
			break;
		if(image1Path.compare("n") == 0)
		{
			collector.newMeasure();
			continue;
		}
		std::cin >> image2Path;
		if(image1Path.compare("q") == 0)
			break;
		std::cin >> homographyPath;
		if(image1Path.compare("q") == 0)
			break;

		cv::Mat image1;
		cv::Mat image2;
		image1 = cv::imread(image1Path, 1);
		image2 = cv::imread(image2Path, 1);


		if (!image1.data)
		{
			std::cerr << "Wrong image1 data! type 'q' if You want to quit or 'n' if You want to start new measure\n";
			continue;
		}
		if (!image2.data)
		{
			std::cerr << "Wrong image2 data! type 'q' if You want to quit\n";
			continue;
		}
		cv::Mat hom;
		hom = ReadMatFromTxt(homographyPath, 3, 3);

		std::cout<< "Starting matching " << image1Path  << " with " << image2Path << std::endl;
		facade->compute(image1, image2, hom);
		std::cout<< "Finished matching " << image1Path  << " with " << image2Path << std::endl;
	}
	while(true);

	collector.createCSV( argv[4], argv[5]);
	delete facade;
	delete factory;


	return 0;
}
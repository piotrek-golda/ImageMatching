#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "ProgramFlowFacade.h"
#include "Interfaces/FacadeAbstractFactory.h"
#include "FacadeFactory.h"


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
	if ( argc != 7 )
	{
		std::cout<< "usage: ./" << argv[0]
		<< " <Image1_Path> <Image2_Path> <Homography_File_Path> <mainConfig_File_Path>"
		<< " <detectionDescriptionConfig_File_Path> <matchingConfig_File_Path>\n";
		exit(1);
	}

	cv::Mat image1;
	cv::Mat image2;
	image1 = cv::imread( argv[1], 1 );
	image2 = cv::imread( argv[2], 1 );


	if ( !image1.data )
	{
		std::cerr << "Wrong image1 data \n";
		exit(1);
	}
	if ( !image2.data )
	{
		std::cerr << "Wrong image2 data \n";
		exit(1);
	}
	cv::Mat hom;
	hom = ReadMatFromTxt(argv[3], 3, 3);

	FacadeAbstractFactory* factory = new FacadeFactory();

	ProgramFlowFacade* facade = factory->constructFacade(argv[4],argv[5],argv[6]);

	facade->compute(image1,image2,hom);

	delete facade;
	delete factory;


	return 0;
}
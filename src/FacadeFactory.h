//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_FACADEFACTORY_H
#define DESCRIPTORDETECTOR_TESTER_FACADEFACTORY_H


#include "Interfaces/FacadeAbstractFactory.h"

class FacadeFactory : public FacadeAbstractFactory
{

public:
	virtual ProgramFlowFacade *constructFacade(std::string mainOptionsFilePath,
											   std::string detectionDescriptionOptionsFilePath,
											   std::string matchingOptionsFilePath);

private:
	void createDescriptor( const char *dscName, INIReader &detDscReader, Descriptor*& descriptor_,
						   DescriptorOptions*& descriptorOptions_, char& ASIFTFLAG, Detector* detector_);

	void createDetector( const char *detName, INIReader &detDscReader, Detector*& detector_,
						 DetectorOptions*& detectorOptions_, char& ASIFTFLAG, int keyPointsLimit );
};


#endif //DESCRIPTORDETECTOR_TESTER_FACADEFACTORY_H

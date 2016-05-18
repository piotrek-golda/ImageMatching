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
};


#endif //DESCRIPTORDETECTOR_TESTER_FACADEFACTORY_H

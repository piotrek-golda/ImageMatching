//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_FACADEABSTRACTFACTORY_H
#define DESCRIPTORDETECTOR_TESTER_FACADEABSTRACTFACTORY_H

#include <string>

#include "../ProgramFlowFacade.h"



class FacadeAbstractFactory
{
public:

public:

	virtual ProgramFlowFacade* constructFacade(std::string mainOptionsFilePath,
											   std::string detectionDescriptionOptionsFilePath,
											   std::string matchingOptionsFilePath) = 0;
protected:

};


#endif //DESCRIPTORDETECTOR_TESTER_FACADEABSTRACTFACTORY_H

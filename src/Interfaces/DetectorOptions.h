//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_DETECTOROPTIONS_H
#define DESCRIPTORDETECTOR_TESTER_DETECTOROPTIONS_H

#include <string>
#include "../INIReader/INIReader.h"


class DetectorOptions
{
public:
	virtual DetectorOptions* getConfiguration(INIReader cfgFile, std::string section ) = 0;
};


#endif //DESCRIPTORDETECTOR_TESTER_DETECTOROPTIONS_H

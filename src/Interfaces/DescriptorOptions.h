//
// Created by piotrek on 08.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_DESCRIPTOROPTIONS_H
#define DESCRIPTORDETECTOR_TESTER_DESCRIPTOROPTIONS_H

#include <string>
#include "../INIReader/INIReader.h"


class DescriptorOptions
{
public:
	virtual DescriptorOptions* getConfiguration(INIReader cfgFile, std::string section ) = 0;
};


#endif //DESCRIPTORDETECTOR_TESTER_DESCRIPTOROPTIONS_H

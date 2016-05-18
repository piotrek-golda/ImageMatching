//
// Created by piotrek on 15.05.16.
//

#include <algorithm>

#include "FacadeFactory.h"
#include "supported_algorithms.h"
#include "Detectors/ORB_detector.h"
#include "Detectors/FAST_detector.h"
#include "Detectors/SIFT_detector.h"
#include "Detectors/SURF_detector.h"
#include "Descriptors/BRIEF_descriptor.h"
#include "Descriptors/SURF_descriptor.h"
#include "Descriptors/SIFT_descriptor.h"
#include "Descriptors/ORB_descriptor.h"
#include "Matchers/SimpleDescriptionsMatcher.h"
#include "Matchers/BruteForceDescriptionsMatcher.h"
#include "Matchers/SimpleKeysMatcher.h"
#include "Descriptors/PI_descriptor.h"

#define DET_NAME(n)  alg_types::detector_names[ n ]
#define DSC_NAME(n)  alg_types::deascriptor_names[ n ]
#define KM_NAME(n)  alg_types::key_matcher_names[ n ]
#define DM_NAME(n)  alg_types::dsc_matcher_names[ n ]

#define DET_HASH(n) alg_types::str2int( alg_types::detector_names[ n ] )
#define DSC_HASH(n) alg_types::str2int( alg_types::deascriptor_names[ n ] )
#define KM_HASH(n) alg_types::str2int( alg_types::key_matcher_names[ n ] )
#define DM_HASH(n) alg_types::str2int( alg_types::dsc_matcher_names[ n ] )


ProgramFlowFacade *FacadeFactory::constructFacade(std::string mainOptionsFilePath,
												  std::string detectionDescriptionOptionsFilePath,
												  std::string matchingOptionsFilePath)
{
	DetectorOptions* detectorOptions_ = NULL;
	Detector* detector_ = NULL;
	DescriptorOptions* descriptorOptions_ = NULL;
	Descriptor* descriptor_ = NULL;
	HomographyGetter* homographyGetter_ = NULL;
	KeysMatcherOptions* keysMatcherOptions_ = NULL;
	KeysMatcher * keysMatcher_ = NULL;
	DescriptionsMatcherOptions* descMatcherOptions_ = NULL;
	DescriptionsMatcher* descMatcher_ = NULL;


	INIReader mainReader(mainOptionsFilePath);
	INIReader detDscReader(detectionDescriptionOptionsFilePath);
	INIReader matReader(matchingOptionsFilePath);

	if (mainReader.ParseError() < 0)
	{
		std::cerr << "OPTIONS PARSING: " << "Can't load " << mainOptionsFilePath << " file \n";
		exit(1);
	}

	if (detDscReader.ParseError() < 0)
	{
		std::cerr << "OPTIONS PARSING: " << "Can't load " << detectionDescriptionOptionsFilePath << " file \n";
		exit(1);
	}

	if (matReader.ParseError() < 0)
	{
		std::cerr << "OPTIONS PARSING: " << "Can't load " << matchingOptionsFilePath << " file \n";
		exit(1);
	}

	std::string detectorName = mainReader.Get("DETECTION","detector", "missing");
	std::transform(detectorName.begin(), detectorName.end(),detectorName.begin(), ::toupper);

	std::string descriptorName = mainReader.Get("DESCRIPTION","descriptor", "missing");
	std::transform(descriptorName.begin(), descriptorName.end(),descriptorName.begin(), ::toupper);

	std::string descriptionMatcherName = mainReader.Get("MATCHING","descriptionsMatching", "missing");
	std::transform(descriptionMatcherName.begin(), descriptionMatcherName.end(),descriptionMatcherName.begin(), ::toupper);

	std::string keyMatcherName = mainReader.Get("MATCHING","keysMatching", "missing");
	std::transform(keyMatcherName.begin(), keyMatcherName.end(),keyMatcherName.begin(), ::toupper);

	switch( alg_types::str2int( detectorName.c_str() ) )
	{
		case DET_HASH( alg_types:: DET_FAST ):
			detector_ = new FAST_detector();
			detectorOptions_ = FAST_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_FAST ) );
			break;
		case DET_HASH( alg_types:: DET_ORB ):
			detector_ = new ORB_detector();
			detectorOptions_ = ORB_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_ORB ) );
			break;
		case DET_HASH( alg_types:: DET_SIFT ):
			detector_ = new SIFT_detector();
			detectorOptions_ = SIFT_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_SIFT ) );
			break;
		case DET_HASH( alg_types:: DET_SURF ):
			detector_ = new SURF_detector();
			detectorOptions_ = SURF_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_SURF ) );
			break;
		default:
			std::cerr << "OPTIONS PARSING: " << "unsupported/missing detector " << detectorName.c_str() << "\n";
			exit(1);
	}

	switch( alg_types::str2int( descriptorName.c_str() ) )
	{
		case DSC_HASH( alg_types:: DSC_BRIEF ):
			descriptor_ = new BRIEF_descriptor();
			descriptorOptions_ = BRIEF_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_BRIEF ) );
			break;
		case DSC_HASH( alg_types:: DSC_ORB ):
			descriptor_ = new ORB_descriptor();
			descriptorOptions_ = ORB_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_ORB ) );
			break;
		case DSC_HASH( alg_types:: DSC_SIFT ):
			descriptor_ = new SIFT_descriptor();
			descriptorOptions_ = SIFT_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_SIFT ) );
			break;
		case DSC_HASH( alg_types:: DSC_SURF ):
			descriptor_ = new SURF_descriptor();
			descriptorOptions_ = SURF_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_SURF ) );
			break;
		case DSC_HASH( alg_types:: DSC_PI ):
			descriptor_ = new PI_descriptor();
			descriptorOptions_ = PI_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_PI ) );
			break;
		default:
			std::cerr << "OPTIONS PARSING: " << "unsupported/missing descriptor " << descriptorName.c_str() << "\n";
			exit(1);
	}

	switch( alg_types::str2int( descriptionMatcherName.c_str() ) )
	{
		case DM_HASH( alg_types:: DM_SIMPLE ):
			descMatcher_ = new SimpleDescriptionsMatcher();
			descMatcherOptions_ = SimpleDescriptionsMatcherOptions().getConfiguration(matReader, DM_NAME( alg_types:: DM_SIMPLE ) );
			break;
		case DM_HASH( alg_types:: DM_BRUTEFORCE ):
			descMatcher_ = new BruteForceDescriptionsMatcher();
			descMatcherOptions_ = BruteForceDescriptionsMatcherOptions().getConfiguration(matReader, DM_NAME( alg_types:: DM_BRUTEFORCE ) );
			break;
		default:
			std::cerr << "OPTIONS PARSING: " << "unsupported/missing descriptions matcher " << descriptionMatcherName.c_str() << "\n";
			exit(1);
	}

	switch( alg_types::str2int( keyMatcherName.c_str() ) )
	{
		case KM_HASH( alg_types:: KM_SIMPLE ):
			keysMatcher_ = new SimpleKeysMatcher();
			keysMatcherOptions_ = SimpleKeysMatcherOptions().getConfiguration(matReader, KM_NAME( alg_types:: KM_SIMPLE ) );
			break;
		default:
			std::cerr << "OPTIONS PARSING: " << "unsupported/missing keys matcher " << keyMatcherName.c_str() << "\n";
			exit(1);
	}

	homographyGetter_ = new HomographyGetter();


	return new ProgramFlowFacade(detectorOptions_,detector_,descriptorOptions_,descriptor_,homographyGetter_,
								 keysMatcherOptions_,keysMatcher_,descMatcherOptions_,descMatcher_);
}

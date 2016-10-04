//
// Created by piotrek on 15.05.16.
//

#include <algorithm>
#include <typeinfo>

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
#include "Descriptors/FREAK_descriptor.h"
#include "Detectors/HARRIS_detector.h"
#include "Detectors/MSER_detector.h"
#include "Detectors/AGAST_detector.h"
#include "Detectors/ASIFT_detector_descriptor.h"
#include "Descriptors/MULTI_descriptor.h"

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

	char ASIFTFLAG = 0;
	int keyPointsLimit = mainReader.GetInteger("DETECTION","kpoints_limit",0);
	std::string detectorName = mainReader.Get("DETECTION","detector", "missing");
	std::transform(detectorName.begin(), detectorName.end(),detectorName.begin(), ::toupper);

	std::string descriptorName = mainReader.Get("DESCRIPTION","descriptor", "missing");
	std::transform(descriptorName.begin(), descriptorName.end(),descriptorName.begin(), ::toupper);

	std::string descriptionMatcherName = mainReader.Get("MATCHING","descriptionsMatching", "missing");
	std::transform(descriptionMatcherName.begin(), descriptionMatcherName.end(),descriptionMatcherName.begin(), ::toupper);

	std::string keyMatcherName = mainReader.Get("MATCHING","keysMatching", "missing");
	std::transform(keyMatcherName.begin(), keyMatcherName.end(),keyMatcherName.begin(), ::toupper);


	createDetector(detectorName.c_str(),detDscReader,detector_,detectorOptions_,ASIFTFLAG, keyPointsLimit);

	createDescriptor(descriptorName.c_str(), detDscReader, descriptor_, descriptorOptions_, ASIFTFLAG, detector_);

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
								 keysMatcherOptions_,keysMatcher_,descMatcherOptions_,descMatcher_,keyPointsLimit, ASIFTFLAG == 2 );
}

void FacadeFactory::createDescriptor(const char *dscName, INIReader &detDscReader, Descriptor*& descriptor_,
									 DescriptorOptions*& descriptorOptions_, char& ASIFTFLAG, Detector* detector_)
{

	std::string name = dscName;
	if (name.find('-')!=std::string::npos)
	{
		MULTI_descriptor* multiDSC = new MULTI_descriptor();
		descriptor_ = multiDSC;
		descriptorOptions_ = MULTI_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_MULTI ) );
		const char* subdsc = NULL;
		char *cname = new char[name.length() + 1];
		strcpy(cname, name.c_str());

		subdsc = strtok(cname, "-");
		Descriptor* dsc;
		DescriptorOptions* dscOpt;

		while(subdsc != NULL)
		{
			createDescriptor(subdsc,detDscReader,dsc,dscOpt,ASIFTFLAG,detector_);
			multiDSC->append( {dsc,dscOpt} );
			subdsc = strtok(NULL, "-");
		}
		return;
	}
	switch( alg_types::str2int( dscName ) )
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
		case DSC_HASH( alg_types:: DSC_FREAK ):
			descriptor_ = new FREAK_descriptor();
			descriptorOptions_ = FREAK_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_FREAK ) );
			break;
		case DSC_HASH( alg_types:: DSC_ASIFT ):
			// allowed only when ASIFT detector was used.
			if( ASIFTFLAG != 1 )
			{
				std::cerr << "OPTIONS PARSING: " << "ASIFT descriptor allowed only with ASIFT detector.\n"
						"Consider using SIFT descriptor." << "\n";
				exit(1);
			}
			ASIFTFLAG++;
			descriptor_ = dynamic_cast< ASIFT_detector_descriptor* >(detector_);
			descriptorOptions_ = ASIFT_descriptorOptions().getConfiguration(detDscReader, DSC_NAME( alg_types:: DSC_ASIFT ) );
			break;
		default:
			std::cerr << "OPTIONS PARSING: " << "unsupported/missing descriptor " << dscName << "\n";
			exit(1);
	}
}

void FacadeFactory::createDetector(const char *detName, INIReader &detDscReader, Detector*& detector_,
								   DetectorOptions*& detectorOptions_, char &ASIFTFLAG, int keyPointsLimit)
{
	switch( alg_types::str2int( detName) )
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
		case DET_HASH( alg_types:: DET_HARRIS ):
			detector_ = new HARRIS_detector();
			detectorOptions_ = HARRIS_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_HARRIS ) );
			break;
		case DET_HASH( alg_types:: DET_MSER ):
			detector_ = new MSER_detector();
			detectorOptions_ = MSER_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_MSER ) );
			break;
		case DET_HASH( alg_types:: DET_AGAST ):
			detector_ = new AGAST_detector();
			detectorOptions_ = AGAST_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_AGAST ) );
			break;
		case DET_HASH( alg_types:: DET_ASIFT ):
			detector_ = new ASIFT_detector_descriptor();
			detectorOptions_ = ASIFT_detectorOptions().getConfiguration(detDscReader, DET_NAME( alg_types:: DET_ASIFT ) );
			(dynamic_cast<ASIFT_detectorOptions*>(detectorOptions_) )->nfeatures = keyPointsLimit;
			ASIFTFLAG++;
			break;
		default:
			std::cerr << "OPTIONS PARSING: " << "unsupported/missing detector " << detName << "\n";
			exit(1);
	}
}

//
// Created by piotrek on 15.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_SUPPORTED_ALGORITHMS_H
#define DESCRIPTORDETECTOR_TESTER_SUPPORTED_ALGORITHMS_H

#include <string>


namespace alg_types
{
	constexpr unsigned int str2int(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
	}

	enum detector_types
	{
		DET_FAST = 0,
		DET_ORB = 1,
		DET_SIFT = 2,
		DET_SURF = 3,
		DET_HARRIS = 4,
		DET_MSER = 5,
		DET_AGAST = 6,
		DET_ASIFT = 7
	};

	constexpr const char* detector_names[] =
			{"FAST_DET","ORB","SIFT","SURF","HARRIS_DET","MSER_DET", "AGAST_DET", "ASIFT_DET"};


	enum descriptor_types
	{
		DSC_BRIEF = 0,
		DSC_ORB = 1,
		DSC_SIFT = 2,
		DSC_SURF = 3,
		DSC_PI = 4,
		DSC_FREAK = 5,
		DSC_ASIFT = 6
	};

	constexpr const char* deascriptor_names[] =
			{"BRIEF_DSC","ORB","SIFT","SURF","PI_DSC","FREAK_DSC", "ASIFT_DSC"};

	enum key_matcher_types
	{
		KM_SIMPLE = 0
	};

	constexpr const char* key_matcher_names[] =
			{"SIMPLE_KEY_MAT"};

	enum dsc_matcher_types
	{
		DM_SIMPLE = 0,
		DM_BRUTEFORCE = 1
	};

	constexpr const char* dsc_matcher_names[] =
			{"SIMPLE_DSC_MAT", "BRUTEFORCE_DSC_MAT"};
}




#endif //DESCRIPTORDETECTOR_TESTER_SUPPORTED_ALGORITHMS_H

cmake_minimum_required(VERSION 3.3)
project(DescriptorDetector_tester)

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp INIReader/INIReader.cpp INIReader/ini.c Interfaces/Detector.h Interfaces/DetectorOptions.h Interfaces/Descriptor.h Interfaces/DescriptorOptions.h Detectors/ORB_detector.cpp Detectors/ORB_detector.h Descriptors/ORB_descriptor.cpp Descriptors/ORB_descriptor.h ProgramFlowFacade.cpp ProgramFlowFacade.h HomographyGetter.cpp HomographyGetter.h Interfaces/KeysMatcher.h Interfaces/DescriptionsMatcher.h MatchesChecker.cpp MatchesChecker.h Matchers/SimpleKeysMatcher.cpp Matchers/SimpleKeysMatcher.h Matchers/SimpleDescriptionsMatcher.cpp Matchers/SimpleDescriptionsMatcher.h Descriptors/SIFT_descriptor.cpp Descriptors/SIFT_descriptor.h Helpers.cpp Helpers.h Detectors/SIFT_detector.cpp Detectors/SIFT_detector.h Descriptors/SURF_descriptor.cpp Descriptors/SURF_descriptor.h Detectors/SURF_detector.cpp Detectors/SURF_detector.h Descriptors/BRIEF_descriptor.cpp Descriptors/BRIEF_descriptor.h Matchers/BruteForceDescriptionsMatcher.cpp Matchers/BruteForceDescriptionsMatcher.h Detectors/FAST_detector.cpp Detectors/FAST_detector.h Interfaces/FacadeAbstractFactory.h FacadeFactory.cpp FacadeFactory.h supported_algorithms.h Descriptors/PI_descriptor.cpp Descriptors/PI_descriptor.h Descriptors/PI_features/ComputePersistentImage.cpp Descriptors/PI_features/features_Persistant_Image.cpp Descriptors/PI_features/Norms.cpp Interfaces/PatchExtractor.h Extractors/SimplePatchExtractor.cpp Extractors/SimplePatchExtractor.h)
add_executable(DescriptorDetector_tester ${SOURCE_FILES})

target_link_libraries( DescriptorDetector_tester ${OpenCV_LIBS} )
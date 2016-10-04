cmake_minimum_required(VERSION 2.8)
project(DescriptorDetector_tester)

find_package( OpenCV REQUIRED )

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


ADD_SUBDIRECTORY(Detectors/ASIFT/libMatch)
ADD_SUBDIRECTORY(Detectors/ASIFT/libNumerics)

set(ASIFT_srcs
        Detectors/ASIFT/numerics1.cpp
        Detectors/ASIFT/frot.cpp
        Detectors/ASIFT/splines.cpp
        Detectors/ASIFT/fproj.cpp
        Detectors/ASIFT/library.cpp
        Detectors/ASIFT/flimage.cpp
        Detectors/ASIFT/filter.cpp
        Detectors/ASIFT/demo_lib_sift.cpp
        Detectors/ASIFT/compute_asift_keypoints.cpp)


set(SOURCE_FILES main.cpp INIReader/INIReader.cpp INIReader/ini.c Interfaces/Detector.h Interfaces/DetectorOptions.h Interfaces/Descriptor.h Interfaces/DescriptorOptions.h Detectors/ORB_detector.cpp Detectors/ORB_detector.h Descriptors/ORB_descriptor.cpp Descriptors/ORB_descriptor.h ProgramFlowFacade.cpp ProgramFlowFacade.h HomographyGetter.cpp HomographyGetter.h Interfaces/KeysMatcher.h Interfaces/DescriptionsMatcher.h MatchesChecker.cpp MatchesChecker.h Matchers/SimpleKeysMatcher.cpp Matchers/SimpleKeysMatcher.h Matchers/SimpleDescriptionsMatcher.cpp Matchers/SimpleDescriptionsMatcher.h Descriptors/SIFT_descriptor.cpp Descriptors/SIFT_descriptor.h Helpers.cpp Helpers.h Detectors/SIFT_detector.cpp Detectors/SIFT_detector.h Descriptors/SURF_descriptor.cpp Descriptors/SURF_descriptor.h Detectors/SURF_detector.cpp Detectors/SURF_detector.h Descriptors/BRIEF_descriptor.cpp Descriptors/BRIEF_descriptor.h Matchers/BruteForceDescriptionsMatcher.cpp Matchers/BruteForceDescriptionsMatcher.h Detectors/FAST_detector.cpp Detectors/FAST_detector.h Interfaces/FacadeAbstractFactory.h FacadeFactory.cpp FacadeFactory.h supported_algorithms.h Descriptors/PI_descriptor.cpp Descriptors/PI_descriptor.h Descriptors/PI_features/ComputePersistentImage.cpp Descriptors/PI_features/features_Persistant_Image.cpp Descriptors/PI_features/Norms.cpp Interfaces/PatchExtractor.h Extractors/SimplePatchExtractor.cpp Extractors/SimplePatchExtractor.h Descriptors/FREAK_descriptor.cpp Descriptors/FREAK_descriptor.h Detectors/HARRIS_detector.cpp Detectors/HARRIS_detector.h Detectors/MSER_detector.cpp Detectors/MSER_detector.h Detectors/AGAST/agast.cpp Detectors/AGAST/agast_score.hpp Detectors/AGAST/agast_score.cpp Detectors/AGAST/agast_wrapper.hpp Detectors/AGAST_detector.cpp Detectors/AGAST_detector.h Detectors/ASIFT_detector_descriptor.cpp Detectors/ASIFT_detector_descriptor.h DataCollector.cpp DataCollector.h Descriptors/MULTI_descriptor.cpp Descriptors/MULTI_descriptor.h)
add_executable(DescriptorDetector_tester ${ASIFT_srcs} ${SOURCE_FILES})

target_link_libraries( DescriptorDetector_tester ${OpenCV_LIBS}    )
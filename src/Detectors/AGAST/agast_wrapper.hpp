//
// Created by piotrek on 12.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_AGAST_WRAPPER_HPP
#define DESCRIPTORDETECTOR_TESTER_AGAST_WRAPPER_HPP

#include <opencv2/features2d/features2d.hpp>

/** @overload */
 void AGAST( cv::InputArray image, CV_OUT std::vector<cv::KeyPoint>& keypoints,
					   int threshold, bool nonmaxSuppression=true );

/** @brief Detects corners using the AGAST algorithm

@param image grayscale image where keypoints (corners) are detected.
@param keypoints keypoints detected on the image.
@param threshold threshold on difference between intensity of the central pixel and pixels of a
circle around this pixel.
@param nonmaxSuppression if true, non-maximum suppression is applied to detected corners
(keypoints).
@param type one of the four neighborhoods as defined in the paper:
AgastFeatureDetector::AGAST_5_8, AgastFeatureDetector::AGAST_7_12d,
AgastFeatureDetector::AGAST_7_12s, AgastFeatureDetector::OAST_9_16

For non-Intel platforms, there is a tree optimised variant of AGAST with same numerical results.
The 32-bit binary tree tables were generated automatically from original code using perl script.
The perl script and examples of tree generation are placed in features2d/doc folder.
Detects corners using the AGAST algorithm by @cite mair2010_agast .

 */
 void AGAST( cv::InputArray image, CV_OUT std::vector<cv::KeyPoint>& keypoints,
					   int threshold, bool nonmaxSuppression, int type );
//! @} features2d_main

//! @addtogroup features2d_main
//! @{

/** @brief Wrapping class for feature detection using the AGAST method. :
 */
class  AgastFeatureDetector
{
public:
enum
{
	AGAST_5_8 = 0, AGAST_7_12d = 1, AGAST_7_12s = 2, OAST_9_16 = 3,
	THRESHOLD = 10000, NONMAX_SUPPRESSION = 10001,
};

 static cv::Ptr<AgastFeatureDetector> create( int threshold=10,
												 bool nonmaxSuppression=true,
												 int type=AgastFeatureDetector::OAST_9_16 );

 virtual void detect( cv::InputArray _image, std::vector<cv::KeyPoint>& keypoints, cv::InputArray _mask ) = 0;

 virtual void setThreshold(int threshold) = 0;
 virtual int getThreshold() const = 0;

 virtual void setNonmaxSuppression(bool f) = 0;
 virtual bool getNonmaxSuppression() const = 0;

 virtual void setType(int type) = 0;
 virtual int getType() const = 0;
};

#endif //DESCRIPTORDETECTOR_TESTER_AGAST_WRAPPER_HPP

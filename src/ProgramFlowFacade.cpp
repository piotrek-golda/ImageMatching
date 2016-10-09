//
// Created by piotrek on 08.05.16.
//

#include <fstream>
#include "ProgramFlowFacade.h"
#include "MatchesChecker.h"
#include "Matchers/SimpleDescriptionsMatcher.h"
#include "Helpers.h"
#include "DataCollector.h"

int ProgramFlowFacade::compute(cv::Mat &image1, cv::Mat &image2, cv::Mat homographyMat, std::string figureFolder)
{

	this->descriptions_matches.clear();
	this->key_points1.clear();
	this->key_points2.clear();
	this->key_points_transformed.clear();
	this->matches_found.clear();

	DataCollector& collector = DataCollector::getDataCollector();

	std::cout<< '\n';
	std::cout<< "DETECTION: " << this->detector_->getName() << "\n";
	//DETECTION
	#pragma omp sections
	{
		{this->detector_->detect(image1, this->key_points1, *(this->detectorOptions_));}
		#pragma omp section
		{this->detector_->detect(image2, this->key_points2, *(this->detectorOptions_));}
	}
	std::cout <<
			"\nim1 key points number: " << this->key_points1.size() <<
			"\nim2 key points number: "<< this->key_points2.size() << std::endl;

	std::cout<< '\n';
	std::cout<< "FILTERING KEY POINTS: " << "\n";
	if(keyPointsLimit > 0)
	{
		auto compareFunc = []( const cv::KeyPoint& k1, const cv::KeyPoint& k2){return k1.response > k2.response;};

		#pragma omp sections
		{
			{
				std::sort(key_points1.begin(), key_points1.end(), compareFunc);
				while (key_points1.size() > keyPointsLimit)
					key_points1.pop_back();
			}
			#pragma omp section
			{
				std::sort(key_points2.begin(), key_points2.end(), compareFunc);
				while(key_points2.size() > keyPointsLimit )
					key_points2.pop_back();
			}
		}


	}

	std::cout <<
	"\nim1 key points number: " << this->key_points1.size() <<
	"\nim2 key points number: "<< this->key_points2.size() << std::endl;


	std::cout<< '\n';
	std::cout<< "DESCRIPTION: " << this->descriptor_->getName() << "\n";
	//DESCRIPTION
	collector.startMeasuringTime();
	#pragma omp sections
	{
		{this->descriptor_->describe(image1, this->key_points1, this->descriptions1, *(this->descriptorOptions_));}
		#pragma omp section
		{this->descriptor_->describe(image2, this->key_points2, this->descriptions2, *(this->descriptorOptions_));}
	}
	collector.stopMeasuringTime();

	std::cout<<
		"\nim1 descriptions size & number: " << this->descriptions1.size() <<
		"\nim2 descriptions size & number: "<< this->descriptions2.size() << std::endl;
	std::cout <<
	"\nim1 key points number: " << this->key_points1.size() <<
	"\nim2 key points number: "<< this->key_points2.size() << std::endl;

	std::cout<< '\n';
	std::cout << "DESCRIPTIONS MATCHER: " << descMatcher_->getName() << "\n";
	//DETERMINING DESCRIPTIONS MATCHES
	this->descMatcher_->match(this->descriptions1,this->descriptions2,this->descriptions_matches, *(this->descMatcherOptions_) );
	std::cout << this->descriptions_matches.size() << '\n';


	std::cout<< '\n';
	//GETTING TRANSFORMATION
	if( ! homographyMat.empty() )
		this->homographyGetter_->set(homographyMat);
	this->homography = this->homographyGetter_->get();

	//KEY POINTS TRANSFORMATION
	this->key_points_transformed.resize(this->key_points1.size());
	std::vector<cv::Point2f> kp1(this->key_points1.size());
	for(int i =0; i < kp1.size(); ++i )
	{
		kp1[i] = this->key_points1[i].pt;
	}
	cv::perspectiveTransform( kp1, this->key_points_transformed, this->homography);


	//DETERMINING TRUE MATCHES
	std::cout << "KEYS MATCHER: " << keysMatcher_->getName() << "\n";
	this->keysMatcher_->match(this->key_points_transformed,this->key_points2,this->true_matches, *(this->keysMatcherOptions_) );
	std::cout << "TRUE MATCHES: " << this->true_matches.size() << '\n';

	std::cout<< '\n';
	//CHECK MATCHES
	MatchesChecker::check( this->true_matches, this->descriptions_matches, this->matches_found );

	std::cout << "TRUE MATCHES found through descriptions:\n" << this->matches_found.size() << '\n';
	collector.logResult(this->matches_found.size() );

//	for(int i = 0; i < descriptions_matches.size(); ++i)
//	{
//		std::cout<<euclidean_distance( descriptions1[descriptions_matches[i].first],descriptions2[descriptions_matches[i].second] ) << std::endl;
//	}
//
//	for(int i =0; i < descriptions_matches.size(); ++i)
//	{
//		std::cout<< euclidean_distance( descriptions1[descriptions_matches[i].first],descriptions2[descriptions_matches[i].second] ) <<std::endl;
//
//		std::vector<cv::KeyPoint> kp1;
//		std::vector<cv::KeyPoint> kp2;
//		kp1.push_back( cv::KeyPoint( this->key_points_transformed[ descriptions_matches[i].first ], 2.) );
//		kp2.push_back( this->key_points2[descriptions_matches[i].second] );
//		cv::Mat img;cv::Mat img2;
//		cv::drawKeypoints( image2, kp1, img, cv::Scalar(0,256,256), cv::DrawMatchesFlags::DEFAULT );
//		cv::drawKeypoints( img, kp2, img2, cv::Scalar(0,0,256), cv::DrawMatchesFlags::DEFAULT );
//		imshow("Keypoints", img2 );
//		cv::waitKey(0);
//	}



//	cv::Mat img_keypoints_1; cv::Mat img_keypoints_2; cv::Mat img_keypoints_3;
//	std::vector<cv::KeyPoint> kpt;
////	for(int i = 0; i < key_points_transformed.size(); ++i)
////		kpt.push_back( cv::KeyPoint(key_points_transformed[i], 2.) );
//	cv::drawKeypoints( image1, key_points1, img_keypoints_1, cv::Scalar(256,0,0), cv::DrawMatchesFlags::DEFAULT );
////	cv::drawKeypoints( image2, key_points2, img_keypoints_2, cv::Scalar(0,256,0), cv::DrawMatchesFlags::DEFAULT );
////	cv::drawKeypoints( image2, kpt, img_keypoints_3, cv::Scalar(0,0,256), cv::DrawMatchesFlags::DEFAULT );
//	std::stringstream ss;
//	ss << this->detector_->getName() << "_keypoints.png";
////	imshow(ss.str(), img_keypoints_1 );
//	imwrite( ss.str() , img_keypoints_1 );

//	imshow("Keypoints 2", img_keypoints_2 );
//	imwrite("Keypoints 2.png", img_keypoints_2 );
//	imshow("Keypoints 3", img_keypoints_3 );
//	imwrite("Keypoints 3.png", img_keypoints_3 );


	if( figureFolder.compare("") != 0 )
	{
		std::vector<cv::DMatch> CVmatches;
		for (auto match : this->matches_found)
		{
			CVmatches.push_back(cv::DMatch(match.first, match.second, 0.));
		}

		cv::Mat imgMatches;
		cv::drawMatches(image1, key_points1, image2, key_points2, CVmatches, imgMatches);
		std::stringstream ss;
		ss << figureFolder << "/Matches.png";
		imwrite(ss.str(), imgMatches);

		ss.str("");
		ss << figureFolder << "/im1Keys.txt";
		std::ofstream im1Keys;
		im1Keys.open (ss.str());
		std::cout << "Creating file " << ss.str() << std::endl;

		ss.str(figureFolder);
		ss << figureFolder << "/im2Keys.txt";
		std::ofstream im2Keys;
		im2Keys.open (ss.str());
		std::cout << "Creating file " << ss.str() << std::endl;

		for( auto match : this->matches_found )
		{
			im1Keys << key_points1[match.first].pt << ' ' << key_points1[match.first].size;
			im2Keys << key_points2[match.second].pt << ' ' << key_points2[match.second].size;
			im1Keys << '\n';
			im2Keys << '\n';
		}

		im1Keys.close();
		im2Keys.close();
	}

	return this->matches_found.size();

}

ProgramFlowFacade::~ProgramFlowFacade()
{
	delete this->detector_;
	delete this->descMatcher_;
	delete this->descMatcherOptions_;
	if(!DETDSCFLAG)
		delete this->descriptor_;
	delete this->descriptorOptions_;
	delete this->detectorOptions_;
	delete this->homographyGetter_;
	delete this->keysMatcher_;
	delete this->keysMatcherOptions_;
}

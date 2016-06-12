//
// Created by piotrek on 14.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_HELPERS_H
#define DESCRIPTORDETECTOR_TESTER_HELPERS_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <iostream>

void matToVector(cv::Mat& mat, std::vector< std::vector<float> >& vec);
void matToVector(cv::Mat& mat, std::vector<float> & vec);
void arrTo8UC1Mat(float* v, const int size, cv::Mat& mat);

void matToArray(cv::Mat& mat, double* arr);

void vecToFloatMat(std::vector<std::vector<float> >& v, cv::Mat& mat);

void matTo8u(cv::Mat& source, cv::Mat& dest);

std::string type2str(int type);
void printMatType( cv::Mat m);

#endif //DESCRIPTORDETECTOR_TESTER_HELPERS_H

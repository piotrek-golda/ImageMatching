//
// Created by piotrek on 14.05.16.
//

#include "Helpers.h"

void matToVector(cv::Mat& mat, std::vector< std::vector<float> >& vec)
{
	std::vector<uchar> tmp;
	vec.resize(mat.rows);
	for(int i = 0; i < mat.rows; ++i)
	{
		uchar *p = mat.ptr<uchar>(i);
		tmp.reserve(mat.cols);
		tmp.assign(p, p + mat.cols);
		vec[i].resize(tmp.size());
		for(int j = 0; j < tmp.size(); ++j)
		{
			vec[i][j] = (float)tmp[j];
		}
	}
}

void vecToFloatMat(std::vector<std::vector<float> >& v, cv::Mat& mat)
{
	mat = cv::Mat(v.size(),v[0].size(),CV_32F);
	for(int i = 0; i < v.size(); ++i)
		for(int j = 0; j < v[i].size(); ++j)
		{
			mat.at<float>(i,j) = v[i][j];
		}
}

void matToArray(cv::Mat &mat, double *arr)
{
	std::vector<uchar> tmp;
	for(int i = 0; i < mat.rows; ++i)
	{
		uchar *p = mat.ptr<uchar>(i);
		tmp.reserve(mat.cols);
		tmp.assign(p, p + mat.cols);
		for(int j = 0; j < tmp.size(); ++j)
		{
			arr[i*mat.cols+j] = (double)tmp[j];
		}
	}
}

void matTo8u(cv::Mat &source, cv::Mat &dest)
{
	double min;
	double max;
	double d;
	dest = cv::Mat(source.rows,source.cols, CV_8U);
	for(int i = 0; i < source.rows; ++i)
	{
		source.at<double>(i,0) = round( source.at<double>(i,0) );
		min = source.at<double>(i,0);
		max = source.at<double>(i,0);
		for(int j = 1; j < source.cols; ++j)
		{
			source.at<double>(i,j) = round( source.at<double>(i,j) );
			d = source.at<double>(i,j);
			if(d > max )
				max = d;
			if(d > min )
				min = d;
		}
		for(int j = 0; j < source.cols; ++j)
		{
			source.at<double>(i,j) = round( (source.at<double>(i,j) - min)/(max-min) );
		}
	}

	std::cout << source << std::endl;

	cv::minMaxLoc(source, &min, &max);
	source.convertTo(dest,CV_8U,255.0/(min-max),-255.0*min/(max-min));
}

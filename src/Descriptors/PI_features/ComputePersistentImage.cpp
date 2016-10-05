#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <cfloat>
#include "ComputePersistentImage.h"

namespace PI
{

#define SQUARED_2PI 39.47841760435743447533
#define LN2            0.693147180559945309417



//double normalPDF_2d(double x[2], double mu[2], double sigma[2][2])
//{
//	double detSigma = sigma[0][0] * sigma[1][1] - sigma[0][1] * sigma[1][0];
//	double xmu[2] = { x[0] - mu[0], x[1] - mu[1] };
//	double expVal = -0.5*(xmu[0] * xmu[0] * sigma[1][1] + xmu[1] * xmu[1] * sigma[0][0]
//						  + xmu[0] * xmu[1] * (-sigma[0][1] - sigma[1][0]))/detSigma;
//	return 1. / sqrt(detSigma*SQUARED_2PI)*exp(expVal);
//}

//fast version, assumed that sigma has non zero values only on diagonal and those values are the same
	double normalPDF_2d(double x[2], double mu[2], double &sigma)
	{
		double xmu[2] = {x[0] - mu[0], x[1] - mu[1]};
		return 1. / sqrt(sigma * sigma * SQUARED_2PI) * exp((xmu[0] * xmu[0] + xmu[1] * xmu[1]) / sigma * (-0.5));
	}

	inline double max(const double &a, const double &b)
	{
		if (a > b)
			return a;
		return b;
	}


	void computePersistentImage(std::vector<double> perDia[2], double &sigma,
								unsigned int resolution, bool ignoreOutliers, bool weighting,
								double *&outputPI, std::pair<double, double> *diaLim, double maxBar)
	{
		double maxLim = 0.;
		double minLim = DBL_MAX;
		if (diaLim == NULL)
		{
			for (int i = 0; i < perDia[0].size(); ++i)
			{
				if (maxLim < perDia[1][i])
					maxLim = perDia[1][i];
				if (minLim > perDia[0][i])
					minLim = perDia[0][i];
			}
			maxBar = max(maxLim - minLim, 1.);
		}
		else
		{
			minLim = diaLim->first;
			maxLim = diaLim->second;
			for (int i = 0; i < perDia[0].size(); ++i)
			{
				//TODO double comparition
				if (perDia[0][i] < minLim || perDia[1][i] > maxLim)
				{
					perDia[0][i] = perDia[0][perDia[0].size() - 1];
					perDia[0].pop_back();
					perDia[1][i] = perDia[1][perDia[1].size() - 1];
					perDia[1].pop_back();
				}
			}
		}

		outputPI = new double[resolution * resolution];

		//double sigmaMatrix[][2] = { {sigma,0.}, {0.,sigma} };
		double xMatrix[2];
		double muMatrix[2];
		unsigned long long int indx;

		if (!weighting)
		{
			for (int x = 0; x < resolution; ++x)
			{
				for (int y = 0; y < resolution; ++y)
				{
					indx = (unsigned long long int) x * resolution + y;
					outputPI[indx] = 0.;
					xMatrix[0] = (double) (x + 1) / resolution;
					xMatrix[1] = (double) (y + 1) / resolution;
					for (int rb = 0; rb < perDia[0].size(); ++rb)
					{
						muMatrix[0] = (maxLim - perDia[1][rb]) / maxBar;
						muMatrix[1] = (perDia[0][rb] - minLim) / maxBar;
						outputPI[indx] = outputPI[indx] + normalPDF_2d(xMatrix, muMatrix, sigma);
					}
				}
			}

		}
		else
		{
			double weight = 1.;
			for (int x = 0; x < resolution; ++x)
			{
				for (int y = 0; y < resolution; ++y)
				{
					indx = (unsigned long long int) x * resolution + y;
					outputPI[indx] = 0.;
					xMatrix[0] = (double) (x + 1) / resolution;
					xMatrix[1] = (double) (y + 1) / resolution;
					for (int rb = 0; rb < perDia[0].size(); ++rb)
					{
						weight = (exp(LN2 * ((perDia[1][rb] - perDia[0][rb]) / maxBar)) - 1.);
						muMatrix[0] = (maxLim - perDia[1][rb]) / maxBar;
						muMatrix[1] = (perDia[0][rb] - minLim) / maxBar;
						outputPI[indx] = outputPI[indx] + weight * normalPDF_2d(xMatrix, muMatrix, sigma);
					}
				}
			}
		}
	}
}
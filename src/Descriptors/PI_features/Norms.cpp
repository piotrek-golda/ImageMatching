#include <cmath>
#include <algorithm>
#include <vector>
#include <numeric>
#include <cmath>
#include <functional>
#include <iostream>

namespace PI
{

#define EPSILON 1e-12

	inline bool equal(double a, double b)
	{
		return fabs(a - b) < EPSILON;
	}

	void zstd_norm(double *image, int imSize)
	{
		double sum = std::accumulate(image, image + imSize, 0.0);
		double mean = sum / imSize;

		double accum = 0.0;
		std::for_each(image, image + imSize, [&](const double d) {
			accum += (d - mean) * (d - mean);
		});

		double stdev = sqrt(accum / (imSize - 1));

		if (stdev < EPSILON)
			stdev = EPSILON;
		std::for_each(image, image + imSize, [&](double &d) {
			d = (d - mean) / stdev;
		});
	}

	void n2_norm(double *image, int imSize)
	{
		double *imCopy = new double[imSize];
		for (int i = 0; i < imSize; ++i)
		{
			imCopy[i] = image[i];
		}

		double median;
		std::nth_element(imCopy, imCopy + imSize / 2, imCopy + imSize);
		median = imCopy[imSize / 2];

		if (imSize % 2 == 0)
		{
			std::nth_element(imCopy, imCopy + (imSize / 2 - 1), imCopy + imSize);
			median += imCopy[imSize / 2 - 1];
			median /= 2.;
		}

		double mad = 0.;

		for (int i = 0; i < imSize; ++i)
		{
			image[i] -= median;
			imCopy[i] = abs(imCopy[i] - median);
		}

		std::nth_element(imCopy, imCopy + imSize / 2, imCopy + imSize);
		mad = imCopy[imSize / 2];

		if (imSize % 2 == 0)
		{
			std::nth_element(imCopy, imCopy + (imSize / 2 - 1), imCopy + imSize);
			mad += imCopy[imSize / 2 - 1];
			mad /= 2.;
		}

		if (equal(mad, 0.))
		{
			std::cerr << "Warning: Norms.cpp: impossible to divide by mad equals 0" << std::endl;
		}
		else
		{
			for (int i = 0; i < imSize; ++i)
			{
				image[i] /= mad;
			}
		}

		delete[] imCopy;
	}

	void min_max_norm(double *image, int imSize)
	{
		std::pair<double *, double *> minmax = std::minmax_element(image, image + imSize);
		double diff = *(minmax.second) - *(minmax.first);
		if (equal(diff, EPSILON))
		{
			"Warning: Norms.cpp: The matrix contains only constant values. Can not use min max norm.";
		}
		else
		{
			for (int i = 0; i < imSize; ++i)
			{
				image[i] = (image[i] - *(minmax.first)) / diff;
			}
		}
	}
}
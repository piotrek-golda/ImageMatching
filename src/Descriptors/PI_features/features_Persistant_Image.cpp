#include <algorithm>
#include <iostream>
#include <vector>
#include <dlfcn.h>

#include "ComputePersistentImage.h"
#include "features_Persistant_Image.h"
#include "Norms.h"

namespace PI
{

#define EPSILON 1e-12

	extern "C"
	{
	typedef int(*RedHom_ImagePersistentHomologyFunc)(int rows, int cols, double *data, int memoryOrder, double **begins,
													 double **ends);
	}

	inline bool equal(double a, double b)
	{
		return fabs(a - b) < EPSILON;
	}


	void normalizeImage(double *image, int imSize, NormType &normType)
	{
		switch (normType)
		{
			case NONE:
				break;
			case ZSTD:
				zstd_norm(image, imSize);
				break;
			case N2:
				n2_norm(image, imSize);
				break;
			case MINMAX:
				min_max_norm(image, imSize);
				break;
		}
	}


	void feature_persistence_image(const int patchCols, const int patchRows, double *patch, char *mask,
								   PersistantImageParams varArgs, double *&featureVec, int &featureVecSize)
	{


		// apply normalization:
		normalizeImage(patch, patchCols * patchRows, varArgs.normType);

		// apply mask to the normilized image:
		float maskValue = patch[0];
		int size = patchCols * patchRows;
		for (int it = 1; it < size; ++it)
		{
			if (maskValue > patch[it])
				maskValue = patch[it];
		}
		maskValue = floor(maskValue);

		if (mask != NULL)
		{
			for (int it = 1; it < size; ++it)
			{
				if (mask[it] == 0)
					patch[it] = maskValue;
			}
		}

		void *libHandle = dlopen(library.c_str(), RTLD_LAZY);
		RedHom_ImagePersistentHomologyFunc RedHom_ImagePersistentHomology = reinterpret_cast<RedHom_ImagePersistentHomologyFunc>(dlsym(
				libHandle, "RedHom_ImagePersistentHomology"));

		double *begins = 0;
		double *ends = 0;

		////compute Persistant Diagram:
		int intervals = RedHom_ImagePersistentHomology(patchCols, patchRows, patch, 1, &begins, &ends);
//int intervals = 0;
		std::vector<double> PD[2];
		PD[0].reserve(intervals);
		PD[1].reserve(intervals);

		//create PD and remove intervals created by the mask:
		for (int i = 0; i < intervals; ++i)
		{
			if (!equal(begins[i], maskValue))
			{
				PD[0].push_back(begins[i]);
				PD[1].push_back(ends[i]);
			}
		}

		//if the last interval goes to infinity, remove it:
		if (!PD[1].empty() && isinf(PD[1][PD[1].size() - 1]))
		{
			PD[1].pop_back();
			PD[0].pop_back();
		}
		free(begins);
		free(ends);

		double *PI = NULL;
		if (varArgs.diagramLimits == NULL)
		{
			computePersistentImage(PD, varArgs.sigma, varArgs.resolution, varArgs.ignoreOutliers, varArgs.weighting,
								   PI);
		}
		else if (varArgs.useCLBP)
		{
			//TODO
		}
		else
		{
			double maxBar = varArgs.diagramLimits->second - varArgs.diagramLimits->first;
			computePersistentImage(PD, varArgs.sigma, varArgs.resolution, varArgs.ignoreOutliers, varArgs.weighting, PI,
								   varArgs.diagramLimits, maxBar);
		}

		featureVecSize =
				(unsigned long long int) varArgs.resolution * ((unsigned long long int) varArgs.resolution + 1) / 2;

		featureVec = new double[featureVecSize];
		int k = 0;
		for (int i = 0; i < varArgs.resolution; ++i)
		{
			for (int j = 0; j < varArgs.resolution - i; ++j)
			{
				featureVec[k++] = PI[j * varArgs.resolution + i];
			}
		}

		delete[] PI;
	}
}
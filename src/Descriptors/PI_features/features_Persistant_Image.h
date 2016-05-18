#include <string>

namespace PI
{


	const std::string library = "/home/piotrek/Programming/PiTest/PILibs/capd-4.2.142-dev-ubuntu_wily-x86_64/usr/local/lib/libcapd.so.2";


	enum NormType
	{
		NONE = 0,
		ZSTD = 1,
		N2 = 2,
		MINMAX = 3
	};

//
//   -visualize: true / false, default: false.
//   -norm : {zstd | n2 | minmax | none}, default: none.
//   -ignoreOutliers : true, false, default: false.
//     If true : values(intervals) outside of diagramLimits are removed,
//     otherwised they are retained.This option works only together with
//     a specified value range.If no value range is specified, the limits
//     are determined from the data and thus all intervals are included.
//   -diagramLimits : default: [], i.e.estimate from data, otherwise
//     provide a vector of 2 elements[minLim maxLim] that represent the
//     minimum and maximum values that the persistence diagram should be
//     computed for.
//   -sigma : the sigma for the gaussian kernels that make up
//     the persistence image, default: 0.001.
//   -resolution : the resolution of the persistence images : a scalar
//	   (as the images are always square), default: 16.
//   -weighting(default: false) : give components further away from
//     the diagonal more weight!This reduces noise(attenuates very short
//     intervals along and near the diagonal).
//   -useCLBP : true, false, default: false.
//   -CLBP_nSamples : TODO.
//   -CLBP_radius : TODO.
//   -CLBP_encoding : TODO.
//   -CLBP_preComputedMapping : TODO.
//
	struct PersistantImageParams
	{
		NormType normType;
		bool ignoreOutliers;
		std::pair<double, double> *diagramLimits;
		double sigma;
		unsigned int resolution;
		bool weighting;
		bool useCLBP;

		//CLBP_nSamples: TODO.
		//CLBP_radius : TODO.
		//CLBP_encoding : TODO.
		//CLBP_preComputedMapping : TODO.
		PersistantImageParams()
		{
			normType = NONE;
			ignoreOutliers = false;
			diagramLimits = NULL;
			sigma = 0.001;
			resolution = 16;
			weighting = false;
//		useCLBP = false;
		}
	};

	void feature_persistence_image(const int patchCols, const int patchRows, double *patch, char *mask,
								   PersistantImageParams varArgs,
								   double *&featureVec, int &featureVecSize);
}
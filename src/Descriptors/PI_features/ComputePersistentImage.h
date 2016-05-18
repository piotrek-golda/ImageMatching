
namespace PI
{
	double normalPDF_2d(double x[2], double mu[2], double &sigma);

	void computePersistentImage(std::vector<double> perDia[2], double &sigma,
								unsigned int resolution, bool ignoreOutliers, bool weighting,
								double *&outputPI, std::pair<double, double> *diaLim = 0, double maxBar = 0.);
}
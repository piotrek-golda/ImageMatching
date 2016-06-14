//
// Created by piotrek on 13.06.16.
//

#include <fstream>
#include "DataCollector.h"

 std::unique_ptr<DataCollector> DataCollector::instance(new DataCollector);

DataCollector &DataCollector::getDataCollector()
{
	return *DataCollector::instance;
}

void DataCollector::startMeasuringTime()
{
	begin_time = clock();
}

void DataCollector::stopMeasuringTime()
{
	 timesVector[timesVector.size() - 1].push_back( float( clock () - begin_time ) /  CLOCKS_PER_SEC );
}

void DataCollector::logResult(int result)
{
	results[results.size() -  1].push_back( result );
}

void DataCollector::createCSV(std::string timeFileName, std::string resultFileName)
{
	std::ofstream myfile;
	myfile.open (timeFileName);
	for(int i = 0; i < timesVector.size(); ++i)
	{
		myfile << timesVector[i][0];
		for (int j = 1; j < timesVector[i].size(); ++j)
		{
			myfile << ',' <<timesVector[i][j];
		}
		myfile << '\n';
	}
	myfile.close();

	myfile.open (resultFileName);
	for(int i = 0; i < results.size(); ++i)
	{
		myfile << results[i][0];
		for (int j = 1; j < results[i].size(); ++j)
		{
			myfile << ',' <<results[i][j];
		}
		myfile << '\n';
	}
	myfile.close();
}

DataCollector::DataCollector()
{
}

void DataCollector::reset()
{
	results.clear();
	timesVector.clear();
}

void DataCollector::newMeasure()
{
	results.push_back( std::vector<int>() );
	timesVector.push_back( std::vector<float>() );
}

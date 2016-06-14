//
// Created by piotrek on 13.06.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_DATACOLLECTOR_H
#define DESCRIPTORDETECTOR_TESTER_DATACOLLECTOR_H


#include <string>
#include <bits/unique_ptr.h>
#include <vector>

class DataCollector
{

private:

	DataCollector();

	static std::unique_ptr<DataCollector> instance;

	clock_t begin_time{0};
	std::vector< std::vector<float> > timesVector;
	std::vector< std::vector<int> > results;

public:
	static DataCollector& getDataCollector();

	void startMeasuringTime();
	void stopMeasuringTime();

	void logResult( int result );

	void createCSV( std::string timeFileName, std::string resultFileName );

	void newMeasure();

	void reset();
};


#endif //DESCRIPTORDETECTOR_TESTER_DATACOLLECTOR_H

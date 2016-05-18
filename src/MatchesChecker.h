//
// Created by piotrek on 13.05.16.
//

#ifndef DESCRIPTORDETECTOR_TESTER_MATCHESCHECKER_H
#define DESCRIPTORDETECTOR_TESTER_MATCHESCHECKER_H

#include <vector>

class MatchesChecker
{

public:
	//returns number of true matches amongs predicted matches
	static int check( std::vector< std::pair<int,int> >& true_matches, std::vector< std::pair<int,int> >& predicted_matches);

};


#endif //DESCRIPTORDETECTOR_TESTER_MATCHESCHECKER_H

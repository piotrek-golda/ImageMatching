//
// Created by piotrek on 13.05.16.
//

#include <algorithm>

#include "MatchesChecker.h"

int MatchesChecker::check(std::vector<std::pair<int,int> >& true_matches, std::vector<std::pair<int,int> >& predicted_matches, std::vector<std::pair<int,int> >& out_matches)
{
	int matches_found = 0;

	std::sort(true_matches.begin(), true_matches.end());
	std::sort(predicted_matches.begin(),predicted_matches.end());

	int t_it = 0;
	int p_it = 0;
	while( t_it < true_matches.size() && p_it < predicted_matches.size() )
	{
		if( true_matches[t_it] < predicted_matches[p_it] )
		{
			++t_it;
		}
		else if(true_matches[t_it] > predicted_matches[p_it])
		{
			++p_it;
		}
		else
		{
			++matches_found;
			++t_it;
			++p_it;
			out_matches.push_back( true_matches[t_it] );
		}
	}

	return matches_found;
}

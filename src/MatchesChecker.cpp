//
// Created by piotrek on 13.05.16.
//

#include <algorithm>

#include "MatchesChecker.h"

int MatchesChecker::check(std::vector<std::pair<int,int> >& true_matches, std::vector<std::pair<int,int> >& predicted_matches)
{
	int matches_found = 0;

	std::sort(true_matches.begin(), true_matches.end());
	std::sort(predicted_matches.begin(),predicted_matches.end());

	int p_it = 0;
	int t_it = 0;
	while( p_it < predicted_matches.size() && t_it < true_matches.size() )
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
			++p_it;
			++t_it;
		}
	}

	return matches_found;
}

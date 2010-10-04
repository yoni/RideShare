#include "BruteForceOptimizer.hpp"
#include <iostream>

namespace optimizer
{

using std::vector;

void BruteForceOptimizer::optimize() {
	iterate();
}

double BruteForceOptimizer::iterate() {
	//static size_t count = 0;
	//cout<<"count: "<<count++<<endl;
	for(Solution::RidersMap::iterator cur_rider = mySolution.myRiders.begin(); 
			cur_rider != mySolution.myRiders.end(); 
			cur_rider++) 
	{
		// try not assigning this rider first
		Rider temp_copy(cur_rider->second);
		// keep track of where to put the rider back
		Solution::RidersMap::iterator save_where = cur_rider;

		// remove the rider from the pool of unassigned riders
		mySolution.myRiders.erase(cur_rider);

		double cur_score;
		cur_score = iterate();
		if(cur_score > best_score)
		{
			best_score = cur_score;
			best_solution = mySolution;
		}

		unsigned int cur_match_num = 0;
		for(Solution::MatchesMap::iterator cur_match = mySolution.myMatches.begin(); 
				cur_match != mySolution.myMatches.end();
				cur_match++) 
		{
			if(cur_match->second.addRider(temp_copy))
			{
				cur_score = iterate();
				if(cur_score > best_score)
				{
					best_score = cur_score;
					best_solution = mySolution;
				}

				// remove the rider from the match
				cur_match->second.removeRider(temp_copy.routeId);
			}
			cur_match_num++;
		}

		// put the rider back in the pool of unassigned riders
		mySolution.myRiders[temp_copy.routeId] = temp_copy;
		// point iterator back at this rider
		cur_rider = mySolution.myRiders.find(temp_copy.routeId);
	}
	
	//cout << "Score of cur solution: " << score(mySolution) << endl;
	return Optimizer::score(mySolution);
}

}

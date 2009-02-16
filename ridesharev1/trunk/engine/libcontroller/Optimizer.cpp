#include "Optimizer.hpp"

namespace optimizer
{

using std::vector;

double Optimizer::score(const Solution& scoreme) 
{
	double total= 0;
	double totalDistance = 0;
	for(Solution::MatchesMap::const_iterator cur_match = scoreme.myMatches.begin();
			cur_match != scoreme.myMatches.end();
			cur_match++) 
	{
		if(cur_match->second.numPassengers() > 0)
			total += cur_match->second.numPassengers() + 1;
		totalDistance += cur_match->second.myRoute.getRouteDistance();

		//cout << "Match with distance: " << cur_match->second.myRoute.getRouteDistance() << " and numPassengers: " << cur_match->second.numPassengers() << endl;
		//cout << "printAllPoints(): " << endl;
		//cur_match->second.myRoute.printAllPoints();
	}
	return total + 1/totalDistance;
}

}

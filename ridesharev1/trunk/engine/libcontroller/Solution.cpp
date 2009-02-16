#include "Solution.hpp"
#include "RouteMatrixLocal.hpp"
#include "RouteMatrix.hpp"
#include <algorithm>

extern bool useLocalMatrix;
#define allow_scramble true
#define debug_scramble true 

namespace optimizer
{

	const string& BRUTE_FORCE = "brute force";
	const string& GENETIC     = "genetic";
	const string& BIPARTITE   = "bipartite";

	Solution::RouteMatrixPtr myInternalMatrix;
	using controller::routes::RouteMatrixLocal;
	using controller::routes::RouteMatrix;


Solution::~Solution()
{
}

Solution::Solution(const Drivers& drivers, const Riders& riders, 
		const Matches& matches, RouteMatrixInitType matrixInit)
: matrixInitType(matrixInit)
{
	initMyMatches(matches);
	initMyMatches(drivers);
	initMyRiders(riders);
	initRouteMatrix();
	setMatchRouteMatrixPtrs();
}

Solution::Solution(const Drivers& drivers, const Riders& riders,
		RouteMatrixInitType matrixInit)
: matrixInitType(matrixInit)
{
	initMyMatches(drivers);
	initMyRiders(riders);
	initRouteMatrix();
	setMatchRouteMatrixPtrs();
}

Solution::Solution(const Solution& rhs)
	: myRiders(rhs.myRiders)
	, myMatches(rhs.myMatches)
	, matrixInitType(rhs.matrixInitType)
	, algorithm(rhs.getOptimizeType())
{
	initRouteMatrix();
	setMatchRouteMatrixPtrs();
}

void Solution::initMyMatches(const Drivers& drivers){
	for(size_t ii = 0; ii < drivers.size(); ii++){
		Match match(drivers[ii]);
		myMatches[drivers[ii].routeId] = match;
	}
}

void Solution::initMyMatches(const Matches& matches){
	for (size_t ii = 0; ii < matches.size(); ii++){
		myMatches[matches[ii].myDriver.routeId] = matches[ii];
	}
}

void Solution::initMyRiders(const Riders& riders){
	for(size_t ii = 0; ii < riders.size(); ii++){
		myRiders[riders[ii].routeId] = riders[ii];
	}
}
/*
 * Function:		initRouteMatrix()
 * Comments:		Initializes global route matrix for this Solution
 */
void Solution::initRouteMatrix()
{
	if(matrixInitType == FLUSH || myInternalMatrix.use_count() == 0)
	{
		Matches matches;
		Riders riders;
		for(MatchesMap::iterator it = myMatches.begin();
				it != myMatches.end();
				it++)
		{
			matches.push_back(it->second);
			for(Riders::iterator rider = it->second.confirmedRiders.begin();
					rider != it->second.confirmedRiders.end();
					rider++){
				riders.push_back(*rider);
			}
		}
		for(RidersMap::iterator it = myRiders.begin();
				it != myRiders.end();
				it++)
		{
			riders.push_back(it->second);
		}

		Drivers emptyDrivers;
		if(useLocalMatrix){
			myInternalMatrix.reset(new RouteMatrixLocal(emptyDrivers,riders,matches));
		}else{
			myInternalMatrix.reset(new RouteMatrix<>(emptyDrivers,riders,matches));
		}
	}
	else
	{
		//std::cout << "Using old route Matrix" <<std::endl;
	}
	routeMatrix = myInternalMatrix;
}

bool Solution::setOptimizeType(const string& type)
{
	if(type == BRUTE_FORCE)
		algorithm = type;
	else if(type == GENETIC)
		algorithm = type;
	else if(type == BIPARTITE)
		algorithm = type;
	else
		return false;
	return true;
}

Solution& Solution::operator=(const Solution& rhs)
{
	if(this == &rhs)
		return *this;
	myRiders = rhs.myRiders;
	myMatches = rhs.myMatches;
	routeMatrix = rhs.routeMatrix;
	matrixInitType = rhs.matrixInitType;
	algorithm = rhs.getOptimizeType();
	return *this;
}

void Solution::setMatchRouteMatrixPtrs()
{
	//cout<<"Initializing match matrix pointers."<<endl;
	for(MatchesMap::iterator match = myMatches.begin();
			match != myMatches.end();
			match++)
	{
		match->second.setRouteMatrixPtr(routeMatrix);
	}
}

double Solution::getTotalRouteLength()
{
	double retSum = 0;
	for(MatchesMap::iterator match = myMatches.begin();
			match != myMatches.end();
			match++)
	{
		retSum += match->second.myRoute.getRouteDistance();
	}
	return retSum;
}

Solution::Matches Solution::getMatchesVector() const
{
	Matches match_vector;
	for(MatchesMap::const_iterator match = myMatches.begin();
			match != myMatches.end();
			match++)
	{
		match_vector.push_back(match->second);
	}
	return match_vector;
}

Solution::Riders Solution::getRidersVector() const
{
	Riders rider_vector;
	for(RidersMap::const_iterator rider = myRiders.begin();
			rider != myRiders.end();
			rider++)
	{
		rider_vector.push_back(rider->second);
	}
	return rider_vector;
}

void Solution::printRouteIds() const
{
	cout<<"Solution Route ids are:"<<endl;
	cout<<"  Matches:"<<endl;
	for(MatchesMap::const_iterator match = myMatches.begin();
			match != myMatches.end();
			match++)
	{
		cout << "    " << match->second.myDriver.routeId << endl;
	}
	cout<<"  Riders:"<<endl;
	for(RidersMap::const_iterator rider = myRiders.begin();
			rider != myRiders.end();
			rider++)
	{
		cout << "    " << rider->second.routeId << endl;
	}
}
void Solution::printAllRoutes() const
{

	cout<<"*****************************************" <<endl;
	cout<<"*** Printing all routes for this solution" <<endl;
	cout<<"*****************************************" <<endl;
	for(MatchesMap::const_iterator match = myMatches.begin();
		match != myMatches.end();
		match++)
	{
		match->second.myRoute.printAllPoints();
	}
}

#if 1 
vector< Solution::RidersMap::iterator > Solution::getRandomRiderIteratorVector()
{
	vector<RidersMap::iterator> rider_iterators;
	for(RidersMap::iterator i= myRiders.begin(); 
			i != myRiders.end(); 
			i++
			)
	{
		rider_iterators.push_back(i);
	}
	random_shuffle(rider_iterators.begin(), rider_iterators.end());
	return rider_iterators;
}

vector<Solution::MatchesMap::iterator> Solution::getRandomMatchIteratorVector()
{
	vector<Solution::MatchesMap::iterator> match_iterators;
	for(Solution::MatchesMap::iterator i = myMatches.begin(); 
			i != myMatches.end(); 
			i++
			)
	{
		match_iterators.push_back(i);
	}
	random_shuffle(match_iterators.begin(), match_iterators.end());
	return match_iterators;
}
#endif

}


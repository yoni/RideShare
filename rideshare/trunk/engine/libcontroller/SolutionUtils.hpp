#ifndef _SOLUTIONUTILS_HPP
#define _SOLUTIONUTILS_HPP

#include "RouteInfo.hpp"
#include "Solution.hpp"
#include "RiderRouteSubmission.hpp"
#include "DriverRouteSubmission.hpp"
#include <ctime>
#include <cstdlib>
#include <fstream>


namespace optimizer
{
	using std::ofstream;
	typedef Solution::Solutions Solutions;
	enum SolutionType { SIMPLE };

	void solutions2javascript(Solution::Solutions solution, string outFile);
	void printEpilogue(ofstream& out);
	void printHeader(ofstream& out);

	RiderRouteSubmission::ptr getRiderSubmission(Location<> beg, Location<> end);
	DriverRouteSubmission::ptr getDriverSubmission(Location<> beg, Location<> end, size_t capacity);
	Solution::ptr optimizeSolution(const Solution& solution, SolutionType type);
	Solution::ptr simpleOptimization(const Solution & solution);
	RouteInfo<double> getOptimalRouteInfo(Match::Driver *, Match::Riders *);

} // end optimizer namespace

#endif // #ifndef _SOLUTIONUTILS_HPP

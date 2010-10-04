#ifndef _OPTIMIZER_HPP
#define _OPTIMIZER_HPP

#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "Solution.hpp"
#include "DriverRouteSubmission.hpp"
#include "RiderRouteSubmission.hpp"
#include "Match.hpp"
#include "Utils.hpp"

namespace optimizer 
{

using std::vector;

class Optimizer
{
	public:
		typedef boost::shared_ptr<Optimizer> ptr;
		typedef vector<Solution> Solutions;
		typedef vector<Match> Matches;
		typedef RiderRouteSubmission Rider;
		typedef DriverRouteSubmission Driver;
		typedef vector<Rider> Riders;
		typedef vector<Driver> Drivers;
		typedef map<uint32_t,Match> MatchesMap;
		typedef map<uint32_t,Rider> RidersMap;


		explicit Optimizer(Solution solution, RouteMatrixInitType matrixInit = FLUSH)
			: mySolution(solution)
		{
		}

		explicit Optimizer(Drivers drivers, Riders riders, RouteMatrixInitType matrixInit = FLUSH)
			: mySolution(drivers, riders, matrixInit)
		{}

		explicit Optimizer(Drivers drivers, Riders riders, Matches matches, 
												RouteMatrixInitType matrixInit = FLUSH)
			: mySolution(drivers, riders, matches, matrixInit)
		{}

		virtual ~Optimizer()
		{}

		virtual void optimize() = 0;
		virtual double getBestScore() const = 0;
		virtual const Solution& getBestSolution() const = 0;

		static double score(const Solution& scoreme);
		Solutions solutionHistory;
		void printAllRoutes() const{ mySolution.printAllRoutes(); }

	protected:
		Solution mySolution;
		//TODO implement tabu table
};

}

#endif // #ifndef _OPTIMIZER_HPP

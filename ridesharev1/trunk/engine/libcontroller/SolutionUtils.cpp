#include "SolutionUtils.hpp"
#include "RouteClient.hpp"
#include "Optimizer.hpp"
#include <iostream>
#include <algorithm>

namespace optimizer
{
	uint32_t routeId = 0;
	using std::ostream;
	using namespace std;
	
#if 1
	struct printMatch : public unary_function<Match, void>
	{
		printMatch(ostream &out) 
			: os(out)
		{}

		ostream &os;
		void operator () (const Match& x, uint32_t solutionId, uint32_t matchId)
		{
			os << "solutions[" << solutionId << "]['matches']["
				<< matchId << "] = new Array();\n"; 

			os << "solutions[" << solutionId << "]['matches'][" << matchId << "]"
				<< "['driver_id'] = '" << x.myDriver.uInfo.firstName << " " 
				<< x.myDriver.uInfo.lastName << "';\n"; 
			os << "solutions[" << solutionId << "]['matches'][" << matchId << "]"
				<< "['route_id'] = " << x.myDriver.routeId << ";\n"; 
			os << "solutions[" << solutionId << "]['matches'][" << matchId << "]"
				<< "['riders'] = new Array();\n"; 
			// add each rider in match
			//if (x.myRiders.size() >= 1)
			{
				for(uint32_t ii=0; ii < (x.myRiders.size()); ii++)
				{
					os << "solutions[" << solutionId << "]['matches'][" << matchId << "]"
						<< "['riders'][" << ii << "] = '" << x.myRiders[ii].uInfo.firstName << " " 
						<< x.myRiders[ii].uInfo.lastName << "';\n"; 
				}
			}
		}
	};
#endif

	struct processSolution : public unary_function<Solution, void>
	{
		processSolution(ostream &out) 
			: os(out)
		{}
		ostream &os;

		void operator () (Solution& x)
		{
			static uint32_t solutionId = 0;
			static string defaultFile("image_pool/solution_");

			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << defaultFile << solutionId<< ".gif";
			string fName = ss.str();

			RouteClient rClient;
			rClient.createRouteImage(x, fName);

			double solutionScore = Optimizer::score(x);
			os << "solutions[" << solutionId << "] = new Array();\n"; 
			os << "solutions[" << solutionId << "]['score'] = " << solutionScore << ";\n"; 
			os << "solutions[" << solutionId << "]['map'] = new Image();\n"; 
			os << "solutions[" << solutionId << "]['map'].src = '" << fName << "';\n"; 

			os << "solutions[" << solutionId << "]['matches'] = new Array();\n"; 

			// add each map in solution
			uint32_t matchId = 0;
			for(Solution::MatchesMap::const_iterator cur_match = x.myMatches.begin();
					cur_match != x.myMatches.end();
					cur_match++) 
			{
				printMatch pm(os);
				pm(cur_match->second, solutionId, matchId++);
			}
			solutionId++;
		}
	};

	void printHeader(ofstream& out)
	{
	//	out << "<script>\n";
		out << "solutions = new Array();\n";
	}

	void printEpilogue(ofstream& out)
	{
		//out << "</script>";
	}

	void solutions2javascript(Solutions solutions, string outFile)
	{
		ofstream oFile;
		oFile.open(outFile.c_str(), std::ios::out);
		printHeader(oFile);

		std::for_each(solutions.begin(), 
				solutions.end(), 
				processSolution(oFile));

		printEpilogue(oFile);
		oFile.close();
	}

	RiderRouteSubmission::ptr getRiderSubmission(Location<> beg, Location<> end)
	{
			RouteClient::Locations locs;
			locs.push_back(beg);
			locs.push_back(end);

			RouteClient rc;
			RouteInfo<double> rInfo = rc.getRouteInfo(locs, RouteClient::MQ_SERVER);
			double optimalDistance   = rInfo.getRouteDistance();

			RiderRouteSubmission::ptr rider(
					new RiderRouteSubmission(routeId++, beg, end, optimalDistance));

			return rider;
	}

	DriverRouteSubmission::ptr getDriverSubmission(Location<> beg, Location<> end, size_t capacity)
	{
			RouteClient::Locations locs;
			locs.push_back(beg);
			locs.push_back(end);

			RouteClient rc;
			RouteInfo<double> rInfo = rc.getRouteInfo(locs, RouteClient::MQ_SERVER);
			double optimalDistance   = rInfo.getRouteDistance();

			DriverRouteSubmission::ptr driver(
					new DriverRouteSubmission(routeId++, beg, end, optimalDistance, capacity));

			return driver;
	}

#if 0
	Solution::ptr optimizeSolution(const Solution& solution, SolutionType type)
	{
		srand(time(0));
		Solution::ptr retSolution;
		switch(type)
		{
			case SIMPLE:
				retSolution = simpleOptimization(solution);
				break;
		}
		return retSolution;
	}

	Solution::ptr simpleOptimization(const Solution & solution)
	{
		Solution::ptr retSolution(new Solution(solution));
		size_t numDrivers = retSolution->myMatches.size();
		size_t numRiders  = retSolution->myRiders.size();

		while(numRiders)
		{
			for(size_t ii=0; ii < numDrivers && numRiders; ii++)
			{
				Match * match  = &retSolution->myMatches[ii];
				bool isMatched = false;

				while(!isMatched)
				{
					size_t randIndex = (numRiders > 1) ? (rand() % (numRiders-1)) : 0;
					Solution::Rider * randRider  = &retSolution->myRiders[randIndex];

					RouteInfo<> rInfo; 
					if (match->canAddRider(*randRider,rInfo))
					{
						isMatched = true;
						match->addRider(*randRider);
						Solution::Riders::iterator begin = retSolution->myRiders.begin(); 
						retSolution->myRiders.erase( begin + randIndex );
						numRiders--;
					}
				}
			}
		}
		return retSolution;
	}
#endif
}


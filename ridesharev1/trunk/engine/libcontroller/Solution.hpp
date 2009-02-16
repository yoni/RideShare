#ifndef _SOLUTION_HPP
#define _SOLUTION_HPP

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>
#include "DriverRouteSubmission.hpp"
#include "RiderRouteSubmission.hpp"
#include "Match.hpp"
#include "Utils.hpp"
#include <map>
#include <boost/shared_ptr.hpp>
namespace controller
{
	namespace routes{
		template <class T>
			class RouteMatrix;
	}
}


namespace optimizer 
{

extern const string& BRUTE_FORCE;
extern const string& GENETIC;
extern const string& BIPARTITE;

using controller::RouteMatrixInitType;
using std::vector;
using std::map;
class Solution
{
	public:
		typedef boost::shared_ptr<Solution> ptr;
		typedef boost::shared_ptr< RouteMatrix<double> > RouteMatrixPtr;
		typedef RiderRouteSubmission Rider;
		typedef DriverRouteSubmission Driver;
		typedef vector<Solution> Solutions;
		typedef vector<Rider> Riders;
		typedef vector<Driver> Drivers;
		typedef vector<Match> Matches;
		typedef map<uint32_t,Match> MatchesMap;
		typedef map<uint32_t,Rider> RidersMap;
		
		Solution()
		{}

		explicit Solution(const Drivers& drivers, const Riders& riders, 
											const Matches& matches, RouteMatrixInitType = FLUSH );

		explicit Solution(const Drivers& drivers, const Riders& riders, 
											RouteMatrixInitType init = FLUSH);

		Solution(const Solution& rhs);
		
		virtual ~Solution();

		void setFlushType(RouteMatrixInitType flushType)
		{
			matrixInitType = flushType;
		}

		double getTotalRouteLength();
		
		// uint32_t represents routeId
		RidersMap myRiders; 
		MatchesMap myMatches;
		RouteMatrixPtr routeMatrix;
		RouteMatrixInitType matrixInitType;

		size_t getNumUnmatcedRiders() const { return myRiders.size(); }
		size_t getNumMatches() const { return myMatches.size(); }
		Matches getMatchesVector() const;
		Riders getRidersVector() const;
		string getOptimizeType() const { return algorithm; }
		bool setOptimizeType(const string& type); 
		Solution& operator=(const Solution& rhs);
		string getDateCalculated() const { return "CHANGE THIS DATE"; }
		void printRouteIds() const;
		void printAllRoutes() const;
#if 1
		vector<RidersMap::iterator> getRandomRiderIteratorVector();
		vector<MatchesMap::iterator> getRandomMatchIteratorVector();
#endif

	private:
		string algorithm;
		void initMyMatches(const Matches& matches);
		void initMyMatches(const Drivers& drivers);
		void initMyRiders(const Riders& riders);
		void initRouteMatrix();
		void setMatchRouteMatrixPtrs();
};

}
#endif // #ifndef _SOLUTION_HPP

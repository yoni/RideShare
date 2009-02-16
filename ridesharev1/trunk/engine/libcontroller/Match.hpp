#ifndef _MATCH_HPP
#define _MATCH_HPP

#include "DriverRouteSubmission.hpp"
#include "RiderRouteSubmission.hpp"
#include "RoutePreference.hpp"
#include "UserPreference.hpp"
#include "Location.hpp"
#include <iostream>
#include "RouteInfo.hpp"
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

using namespace controller::routes;
using namespace controller;
using namespace std;

#define RectangleMultiplier 2
#define DISTANCE_CONST 0.5 //i think 1 is 65 miles or so

class Match
{
	public:
		typedef RiderRouteSubmission Rider;
		typedef DriverRouteSubmission Driver;
		typedef vector<Driver> Drivers;
		typedef vector<Rider> Riders;
		typedef boost::shared_ptr< RouteMatrix<double> > RouteMatrixPtr;

		Match(){}
		Match(const Match& rhs);
		Match(Driver _driver, Riders _riders);
		Match(Driver _driver);
		
		void removeRider(uint32_t route_id);
		bool canAddRider(const Rider& rider) const;
		bool canAddRider(const Rider& rider, RouteInfo<> & rInfo) const;
		bool addRider(Rider& rider);
		void generateRoute(); // modifies myRoute
		void setRouteMatrixPtr(RouteMatrixPtr rm_ptr);

		bool   getHasMale(){ return hasMale;}
		bool   getHasFemale(){ return hasFemale;}
		size_t getMyMinAge(){ return myMinAge;}
		size_t getMyMaxAge(){ return myMaxAge;}
		size_t numPassengers() const { return myRiders.size(); }

		bool operator!=(Match rhs){
			return !(this->myDriver.routeId == rhs.myDriver.routeId);
		}
		bool operator<(Match rhs){
			if(this->myDriver.routeId < rhs.myDriver.routeId){ return true;}
			return false;
		}
		bool operator>(Match rhs){
			if(this->myDriver.routeId > rhs.myDriver.routeId){ return true;}
			return false;
		}

		Riders getMyRiders() const {
			Riders riders(confirmedRiders);
			riders.insert(riders.end(), myRiders.begin(), myRiders.end());
			return riders;
		}
		vector< Location<> > getLargestRectangle();

		Driver myDriver;
		Riders myRiders;
		Riders confirmedRiders;
		//RoutePreference routePref;
		RouteInfo<double> myRoute;
		UserPreference commonPrefs;

		//the following members are used for the augmenting path algorithm
		uint32_t matched_rider_id;//used for bipartite optimizer, 0 for unmatched, rider_id for matched 
		bool visited;//coloring is used to make sure we're not cycling over the same path

	private:
		void updateHasFemale();
		void updateHasMale();
		void updateMinAge();
		void updateMaxAge();
		void updateMyRoute();
		void updateDataMembers();
		void initializeRectangle();
		bool initializeRouteTimeWindows();
		Rider& getRider(uint32_t routeId);
		UserPreference::UserPreferences getUserPrefs() const;
		TimeWindow<ptime> calculateDriverLeaveWindow();
		bool isRiderCompatible(const Rider& rider) const;
		bool isRouteCompatible(Match& potentialMatch) const;

		bool hasMale;
		bool hasFemale;
		size_t myMinAge;
		size_t myMaxAge;
		Location<> rectangle_top_left;
		Location<> rectangle_bottom_right;
		RouteMatrixPtr SolutionRouteMatrixPtr;
};

}

#endif


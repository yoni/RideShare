#include <string>
#include <sstream>
#include "Match.hpp"
#include "DriverRouteSubmission.hpp"
#include "RiderRouteSubmission.hpp"
#include "RouteClient.hpp"
#include "RoutePreference.hpp"
#include "UserPreference.hpp"
#include "Location.hpp"
#include "Utils.hpp"
#include <iostream>
#include "RouteOptimizer.hpp"
#include "RouteInfo.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include "RouteMatrix.hpp"

/* 
 * these are user for compiler directives
 * setting them to true makes the given function output messages
 */
#define debug_match_constructors false
#define debug_init_route_time_windows false
#define debug_can_add_rider false
#define debug_update_rectangle false

namespace optimizer
{

using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;
using controller::Location;
typedef vector<Match> Matches;

// Match constructors

Match::Match(const Match& rhs)
	:myDriver(rhs.myDriver)
	,myRiders(rhs.myRiders)
	,confirmedRiders(rhs.confirmedRiders)
	,myRoute(rhs.myRoute)
	,commonPrefs(rhs.commonPrefs)
	,hasMale(rhs.hasMale)
	,hasFemale(rhs.hasFemale)
	,myMinAge(rhs.myMinAge)
	,myMaxAge(rhs.myMaxAge)
	,SolutionRouteMatrixPtr(rhs.SolutionRouteMatrixPtr)
{
	initializeRectangle();
#if debug_match_constructors
	//cout<<"SolutionRouteMatrixPtr initialized in copy constructor to: "<<SolutionRouteMatrixPtr.use_count() <<endl;
	//cout<<"Match(Match) constructor: routeId = "<<myDriver.routeId <<endl;
#endif
}

Match::Match(Driver _driver, Riders _riders)
	: myDriver(_driver)
	, confirmedRiders(_riders)
	//, routePref(_driver.routePref)
{
	commonPrefs = UserPreference::getCommonUserPreference(getUserPrefs());
	updateMinAge();
	updateMaxAge();
	updateHasMale();
	updateHasFemale();
	initializeRectangle();
}

Match::Match(Driver _driver)
	:myDriver(_driver)
//	,routePref(_driver.routePref)
{
	updateMinAge();
	updateMaxAge();
	updateHasMale();
	updateHasFemale();
	initializeRectangle();
	commonPrefs = UserPreference::getCommonUserPreference(getUserPrefs());
#if debug_match_constructors
	//cout<<"Match(Driver) constructor: routeId: "<<_driver.routeId <<endl;
#endif
}

/*
 * Function:		updateMyRoute()
 * Arguments:			Match
 * Comments:			updates the worst case time windows for a Match's RouteId
 */
void Match::updateMyRoute()
{
	//cout<<"Updating optimal route."<<endl;
	myRoute = optimizeRouteOrder(*this,SolutionRouteMatrixPtr);

	//initialize time windows to original user preference
	//cout<<"Initializing route time windows."<<endl;
	initializeRouteTimeWindows();
	
	//find the driver's leave window that adheres to all users' route prefs
	//cout<<"Computing the narrowest time window the driver can leave."<<endl;
	TimeWindow<ptime> narrowLeaveWindow = calculateDriverLeaveWindow();
	
	//update the points' time windows according to the driver leave time
	//cout<<"Updating time windows."<<endl;
	time_duration routeTime = minutes(0);
	for(size_t i = 0; i < myRoute.numPoints(); i++)
	{
		//cout<<"Current route time: " << routeTime<<endl;
		myRoute.timeWindows[i].startTime = narrowLeaveWindow.startTime + routeTime;
		myRoute.timeWindows[i].endTime = narrowLeaveWindow.endTime + routeTime;
		routeTime += minutes(  (long) myRoute.points[i].timeMinutes  );
	}
}

/*
 * Function:		setRouteMatrixPtr()
 * Comments:		this pointer is used by all Match members to update RouteInfo
 */
void Match::setRouteMatrixPtr(RouteMatrixPtr rm_ptr)
{
	SolutionRouteMatrixPtr = rm_ptr;
	updateMyRoute();
}


/*
 * Function:		getRider()
 * Arguments:		routeId
 * Return:			pointer to Rider
 * Comments:		Iterates through all riders, until one with routeId is found
 * 							Returns pointer to such rider
 */
Rider& Match::getRider(uint32_t routeId)
{
	for(size_t i = 0; i < myRiders.size(); i++)
	{
		if(myRiders[i].routeId == routeId)
			return myRiders[i];
	}
	for(size_t i = 0; i < confirmedRiders.size(); i++)
	{
		if(confirmedRiders[i].routeId == routeId)
			return confirmedRiders[i];
	}
	// TODO: return something on failure..
}

vector< Location<double> > Match::getLargestRectangle() // not used in canAddRider
{
	vector< Location<> > rectangle;
	rectangle.push_back(rectangle_top_left);
	rectangle.push_back(rectangle_bottom_right);
	return rectangle;
}
/*
 * Match::updateHasFemale()
 * updates hasFemale member
 */
void Match::updateHasFemale()
{
	hasFemale = false;
	if(myDriver.uInfo.genderId == FEMALE)
		hasFemale =  true;
	for(size_t i = 0; i < myRiders.size(); i++)
		if(myRiders[i].uInfo.genderId == FEMALE)
			hasFemale =  true;
	for(size_t i = 0; i < confirmedRiders.size(); i++)
		if(confirmedRiders[i].uInfo.genderId == FEMALE)
			hasFemale = true;
}

/*
 * Match::updateHasMale()
 * updates hasMale member
 */
void Match::updateHasMale()
{
	hasMale = false;
	if(myDriver.uInfo.genderId == MALE)
	{
		hasMale =  true;
		return;
	}

	for(size_t i = 0; i < myRiders.size(); i++)
		if(myRiders[i].uInfo.genderId == MALE)
			hasMale =  true;
	for(size_t i = 0; i < confirmedRiders.size(); i++)
		if(confirmedRiders[i].uInfo.genderId == MALE)
			hasMale = true;
}

/*
 * Match::updateMinAge()
 * updates myMinAge member
 */
void Match::updateMinAge(void)
{
	myMinAge = myDriver.uInfo.age;
	//cout<<"Updating myMinAge, driver's age = "<<myMinAge<<" number of riders = "<<myRiders.size()<<endl;
	size_t riderAge;
	for(size_t i = 0; i < myRiders.size(); i++)
	{
		riderAge = myRiders[i].uInfo.age;
		if(riderAge < myMinAge)
			myMinAge = riderAge;
	}
	for(size_t i = 0; i < confirmedRiders.size(); i++)
	{
		riderAge = confirmedRiders[i].uInfo.age;
		if(riderAge < myMinAge)
			myMinAge = riderAge;
	}
	//cout<<"myMinAge updated to: "<<myMinAge<<endl;
}

/*
 * Match::updateMaxAge()
 * updates myMaxAge member
 */
void Match::updateMaxAge(void)
{
	myMaxAge = myDriver.uInfo.age;
	size_t riderAge;
	for(size_t i = 0; i < myRiders.size(); i++)
	{
		riderAge = myRiders[i].uInfo.age;
		if(riderAge > myMaxAge)
			myMaxAge = riderAge;
	}
	for(size_t i = 0; i < confirmedRiders.size(); i++)
	{
		riderAge = confirmedRiders[i].uInfo.age;
		if(riderAge > myMaxAge)
			myMaxAge = riderAge;
	}
	//cout<<"myMaxAge updated to: "<<myMaxAge<<endl;
}

/*
 * Function:	getUserPrefs()
 * Return:		vector<UserPreference>
 *						, all of the user preferences for this match
 */
UserPreference::UserPreferences Match::getUserPrefs() const
{
	UserPreference::UserPreferences prefs;
	prefs.push_back(myDriver.userPref);

	for(size_t ii = 0; ii < myRiders.size(); ii++)
		prefs.push_back(myRiders[ii].userPref);
	return prefs;
}

/* 
 * Function:			calculateDriverLeaveWindow()
 * Return:				driver leave window that adheres to the most stringent 
 * 								of passenger time windows
 */
TimeWindow<ptime> Match::calculateDriverLeaveWindow()
{
	/*
	 * For each point in the route, check if that point's time window
	 * restricts the earliest and latest leave time for the driver.
	 * Find the most stringent of such restrictions.
	 *
	 * Comment: index until one before the last point, since we're always checking the distance/time
	 * 	to the next point
	 */
#if debug
	cout<<endl<<endl<<"myRoute before I calculate DriverLeaveWindow."<<endl;
	myRoute.printAllPoints();
#endif
	ptime maxEarlyLeave = myRoute.timeWindows[0].startTime;// lower bound for driver to leave
	ptime minLatestLeave = myRoute.timeWindows[0].endTime; // upper bound for driver to leave
	time_duration routeTime = minutes(0);  // a running count of the route time
	for(size_t i = 0; i < myRoute.numPoints()-1; i++)
	{
		routeTime += minutes(  (long) myRoute.points[i].timeMinutes  );
		//check if early time for this point would be met for earliest leave time
		if(myRoute.timeWindows[i+1].startTime - routeTime > maxEarlyLeave)
		{
#if debug 
			cout<<"myRoute.timeWindows["<<i<<"+1].startTime - routeTime = "
				<<myRoute.timeWindows[i+1].startTime<<endl;
			cout<<"is larger than:  maxEarlyLeave = "<<maxEarlyLeave<<endl;
#endif
			maxEarlyLeave = myRoute.timeWindows[i+1].startTime - routeTime;
		}
		//check if late time for this point would be met for latest leave time
		if(myRoute.timeWindows[i+1].endTime - routeTime < minLatestLeave)
		{
#if debug
			cout<<"myRoute.timeWindows["<<i<<"+1].endTime - routeTime = "
				<<myRoute.timeWindows[i+1].endTime<<endl;
			cout<<"is smaller than:  minLatesLeave = "<< minLatestLeave <<endl;
#endif
			minLatestLeave = myRoute.timeWindows[i+1].endTime - routeTime;
		}
	}
	if(maxEarlyLeave > minLatestLeave)
	{
		//cout<<"The time window for leaving is erroneous."<<endl;
		//cout<<"Must leave after: "<< maxEarlyLeave << " and before: " << minLatestLeave << endl;
	}
	TimeWindow<ptime> driverLeaveWindow(maxEarlyLeave,minLatestLeave);
#if debug
	cout<<"Driver leave window narrowed to: ("
		<<driverLeaveWindow.startTime<<" , "<<driverLeaveWindow.endTime<< ")"<<endl;
#endif
	return driverLeaveWindow;
}

/* 
 * Function:			InitializeRouteTimeWindows()
 * Return:				true if successful, false otherwise
 * Comments:			Initializes the RouteInfo::vector<TimeWindows> to users' 
 * 								original route preference values.
 * 								Converts from DateTime to ptime for each TimeWindow
 */
bool Match::initializeRouteTimeWindows()
{
	// initialize time window for each point

#if debug_init_route_time_windows
	cout<<endl<<endl<<"RouteInfo before I initialize time windows:"<<endl;
	myRoute.printAllPoints();
#endif
	
	vector< TimeWindow<ptime> > tWindows;
#if debug_init_route_time_windows
	cout<<"Initializing to user route preference time windows."<<endl;
#endif
	tWindows.push_back(convertToPtime(myDriver.routePref.leaveWindow)); //add driver's leave window

#if debug_init_route_time_windows
		cout<<"Driver leave window: " 
		<< tWindows[0].startTime << "," << tWindows[0].endTime << endl;
#endif
	for(size_t i = 1; i < myRoute.numPoints()-1; i++)
	{
		PointInfo<> point = myRoute.points[i];
		//get rider corresponding to the current point
		Rider r = getRider(point.routeId);
		//add time window to vector
		if(point.locType == START)
			tWindows.push_back(convertToPtime(r.routePref.leaveWindow));
		else
			tWindows.push_back(convertToPtime(r.routePref.arriveWindow));
	}
	tWindows.push_back(convertToPtime(myDriver.routePref.arriveWindow)); //add driver's arrive window
	myRoute.timeWindows = tWindows;
	return true;
}

bool Match::canAddRider(const Rider& rider) const
{
	RouteInfo<> temp;
	return canAddRider(rider, temp);
}

/*
 * Function:			canAddRider()
 * Argument:			Rider to add, RouteInfo object to 
 *                              initialize with optimal route
 * Return:				RiderRouteSubmission
 * Comments:			Calls functions for checking: 
 * 								route compatibility, rider preference compatibility,
 * 								match preference compatibility
 */
bool Match::canAddRider(const Rider& rider, RouteInfo<> & rInfoArg) const
{
	
	// check that the number of riders will not exceed the driver's capacity
	if(myDriver.capacity == 0)
	{
#if debug_can_add_rider 
		cout<<"canAddRider() checks failed on capacity"<<endl;
		cout<<"Number of riders: "<< myRiders.size() + confirmedRiders.size() 
			<<" Capacity: " << myDriver.capacity<<endl;
#endif
		return false;
	}
	
	/*
	 * check that rider meets common user preferences 
	 * & match users meet rider's preferences
	 */
	if(!isRiderCompatible(rider))
	{
#if debug_can_add_rider 
		cout<<"canAddRider() returned false on rider compatibility."<<endl;
#endif 
		return false;
	}

	//TODO: use heuristics to check that the rider's route is within a 
	//     reasonable distance from the current Match route
	// Check that match and rider general time windows preferences coincide.
	if(!((myDriver.routePref.leaveWindow.startTime <= 
					rider.routePref.leaveWindow.endTime)
			&&( myDriver.routePref.arriveWindow.endTime >= 
				rider.routePref.arriveWindow.startTime)))
	{
#if debug_can_add_rider 
		cout<<"canAddRider() returned false on initial time windows checks."<<endl;
#endif
		return false;
	}

	// Check for basic lat/lng rectangle
	if ((rider.startLoc().lng < rectangle_top_left.lng) || //too far west
			(rider.endLoc().lng < rectangle_top_left.lng)){
		return false;
	}
	if ((rider.startLoc().lng > rectangle_bottom_right.lng) || //too far east
			(rider.endLoc().lng > rectangle_bottom_right.lng)){
		return false;
	}
	if ((rider.startLoc().lat > rectangle_top_left.lat) || //too far north
			(rider.endLoc().lat > rectangle_top_left.lat)){
		return false;
	}
	if ((rider.startLoc().lat < rectangle_bottom_right.lat) || //too far south 
			(rider.endLoc().lat < rectangle_bottom_right.lat)){
		return false;
	}
	
	// Check that the route generated by adding this rider will be valid

	//add rider to an identical match
	Match potentialMatch(*this);
	potentialMatch.myRiders.push_back(rider);
	//generate the match's route
	potentialMatch.updateMyRoute();
	
	/*
	if(rider.routeId == 666688 || rider.routeId == 666689){
		cout << "Found bad rider: \n";
		potentialMatch.myRoute.printAllPoints();
	}
	*/

	//validate the route
	if(!isRouteCompatible(potentialMatch))
	{
#if debug_can_add_rider 
		cout<<"canAddRider() returned false on route compatibility."<<endl;
#endif
		return false;
	}

#if debug_can_add_rider 
	cout<<"All canAddRider() checks passed"<<endl;
#endif
	rInfoArg = potentialMatch.myRoute;
	return true; 
}

/*
 * Function:	isRiderCompatible()
 * Argument:	Rider for which to check compatibility
 * Return:		true if compatible, false otherwise
 */
bool Match::isRiderCompatible(const Rider& rider) const 
{
	// check that the Match includes only users meeting the rider's preferences 
	if((rider.userPref.ageMin > myMinAge)||(rider.userPref.ageMax < myMaxAge))
	{
#if 0
		cout<<"canAddRider() returned false on rider age preferences: ageMin: "<< rider.userPref.ageMin
			<< "\tmyMinAge: " << myMinAge << "\tageMax: " << rider.userPref.ageMax 
			<< "\tmyMaxAge: " << myMaxAge << endl;
#endif
		return false;
	}
	if(((rider.userPref.genderId == MALE_ONLY) && hasFemale)
			||((rider.userPref.genderId == FEMALE_ONLY) && hasMale))
	{
		//cout<<"canAddRider() returned false failed on rider gender preferences"<<endl;
		return false;
	} 
	
	/* 
	 * check that rider meets the common preferences
	 * Unspecified common age preferences means we don't have to check.
	 */
	if(commonPrefs.ageMin != UNSPECIFIED_MIN_AGE
				|| commonPrefs.ageMax != UNSPECIFIED_MAX_AGE)
	{
		if(rider.uInfo.age == UNSPECIFIED_AGE) 
			return false;
		if((rider.uInfo.age < commonPrefs.ageMin || rider.uInfo.age > commonPrefs.ageMax))
		{
			//cout<<"canAddRider() returned false on age preferences"<<endl;
			return false;
		}
	}
	if(commonPrefs.genderId != DONT_CARE)
	{
		if(rider.uInfo.genderId == UNSPECIFIED_GENDER) return false;
		if(rider.uInfo.genderId == MALE && commonPrefs.genderId == FEMALE_ONLY)
		{
			//cout<<"canAddRider() creturned false on gender"<<endl;
			return false;
		}
		if(rider.uInfo.genderId == FEMALE && commonPrefs.genderId == MALE_ONLY)
		{
			//cout<<"canAddRider() returned false on gender"<<endl;
			return false;
		}
	}
	return true;
}

/*
 * Function:	initializeRectangle()
 */
void Match::initializeRectangle()
{
	/* We create the largest rectangle that includes all of the Match's Points */
	
	/* Set top left and bottom right values
	 * More + is more North (up) (Latitude)
	 * More - is more West (left) (Longitude)
	 */
	if (myDriver.startLoc().lat > myDriver.endLoc().lat){ // more north/top
		rectangle_top_left.lat = myDriver.startLoc().lat;
		rectangle_bottom_right.lat = myDriver.endLoc().lat;
	}else{
		rectangle_top_left.lat = myDriver.endLoc().lat;
		rectangle_bottom_right.lat = myDriver.startLoc().lat;
	}
	
	if (myDriver.startLoc().lng < myDriver.endLoc().lng){ // more west/left
		rectangle_top_left.lng = myDriver.startLoc().lng;
		rectangle_bottom_right.lng = myDriver.endLoc().lng;
	}else{
		rectangle_top_left.lng = myDriver.endLoc().lng;
		rectangle_bottom_right.lng = myDriver.startLoc().lng;
	}
#if debug_update_rectangle
	cout << "Rectangle Before:"<<endl;
	cout << "  top left:     " << rectangle_top_left.lat << "," << rectangle_top_left.lng << endl;
	cout << "  bottom right: " << rectangle_bottom_right.lat << "," << rectangle_bottom_right.lng << endl;
#endif
	double lat_distance = (rectangle_top_left.lat - rectangle_bottom_right.lat);
	double lng_distance = (-(rectangle_top_left.lng - rectangle_bottom_right.lng));
	
	lat_distance = ((lat_distance * RectangleMultiplier)/2) + DISTANCE_CONST;
	lng_distance = ((lng_distance * RectangleMultiplier)/2) + DISTANCE_CONST;
	
	rectangle_top_left.lat += lat_distance; // More pos/north
	rectangle_bottom_right.lat -= lat_distance; // more neg/south

	rectangle_top_left.lng -= lng_distance; // more neg/west
	rectangle_bottom_right.lng += lng_distance; // more pos/east

	
#if debug_update_rectangle
	cout << "Rectangle after:"<<endl;
	cout << "  top left:     " << rectangle_top_left.lat << "," << rectangle_top_left.lng << endl;
	cout << "  bottom right: " << rectangle_bottom_right.lat << "," << rectangle_bottom_right.lng << endl;
#endif
}

/*
 * Function:	isRouteCompatible()
 * Argument:	Match for which to check route compatibility
 * Return:		true if compatible, false otherwise
 */
bool Match::isRouteCompatible(Match& potentialMatch) const
{
	/*
	 * check that adding the rider won't increase the match length by 
	 * more than MAX_DEVIATION (declared in Utils.cpp)
	 */
	// cout << "Distance Compared: " << potentialMatch.myRoute.getRouteDistance() << endl;
	if(potentialMatch.myRoute.getRouteDistance() > 
			MAX_DEVIATION * potentialMatch.myDriver.optimalDistance)
	{
		//cout<<"canAddRider() checks returned false on route deviation."<<endl;
		//cout<<"Adding the rider would increase the route length by more than "
			//<<(MAX_DEVIATION)*100<<"%"<<endl;
		//cout<<"Driver's optimal distance: "<< myDriver.optimalDistance <<" New route length: "
			//<< potentialMatch.myRoute.getRouteDistance() << endl;
		return false;
	}

	// check for time window compatibility using RouteInfo (i.e. optimized route)

	//cout<<endl<<"******************************************************"<<endl;
	//cout<<"Checking Route Compatibility for the following Route:"<<endl;

	//potentialMatch.myRoute.printAllPoints();
	TimeWindow<ptime> pointWindow;
	TimeWindow<ptime> preferredWindow;
	time_duration routeTime = minutes(0);
	for (size_t i=0; i < potentialMatch.myRoute.numPoints(); i++)
	{
		//run through all points, check that time window preferences are met
		
		pointWindow = potentialMatch.myRoute.timeWindows[i];
		//check for erroneous time window, i.e. leave time after arrive time
		if(pointWindow.startTime > pointWindow.endTime)
		{
			//cout << "canAddRider() returned false: Leave time later than arrive time." << endl;
			return false;
		}

		PointInfo<> point = potentialMatch.myRoute.points[i];
		routeTime += minutes(  (long) point.timeMinutes  );

		/*
		 * Set preferredWindow to the window corresponding 
		 * to this point's user preference
		 */
		if(i==0)
		{
			//set preferred time window to driver's leave time window
			preferredWindow = convertToPtime(potentialMatch.myDriver.routePref.leaveWindow); 
		}
		else if(i==potentialMatch.myRoute.numPoints()-1)
		{
			//set preferred time window to driver's arrive time window
			preferredWindow = convertToPtime(potentialMatch.myDriver.routePref.arriveWindow); 
		}
		else
		{
			//find rider whose point this is, set preferredWindow to that rider's preference
			if(point.locType==START)
			{
				preferredWindow = 
					convertToPtime(potentialMatch.getRider(point.routeId).routePref.leaveWindow);
			}
			else
			{
				preferredWindow = 
					convertToPtime(potentialMatch.getRider(point.routeId).routePref.arriveWindow);
			}
		}
		
		//check that the time window for this point adheres to the preferred time window
		if(pointWindow.startTime < preferredWindow.startTime ||
				pointWindow.endTime > preferredWindow.endTime)
		{
#if 0
			cout << "canAddRider() returned false: found incompatible time windows." <<endl;
			cout << "Point Window: ("
				<<pointWindow.startTime<<" , "<<pointWindow.endTime<<")"<<endl
				<< "Preferred Window: ("
				<<preferredWindow.startTime<<" , "<<preferredWindow.endTime <<")" << endl;
#endif
			return false;
		}
	}
	return true;
}

/*
 * Function:		updateDataMembers()
 * Comments:		updates Match data members
 */
void Match::updateDataMembers()
{
	updateMyRoute();
	updateHasMale();
	updateHasFemale();
	updateMinAge();
	updateMaxAge();
	commonPrefs = UserPreference::getCommonUserPreference(getUserPrefs());
}

/*
 * Function:		addRider()
 * Arguments:		Rider&
 * Return:			true if successful, false if adding rider would
 * 							conflict with the match.
 * Comments:		tries to add rider, updates Match data members
 */
bool Match::addRider(Rider& rider)
{
	RouteInfo<> rInfo;
	if(!canAddRider(rider, rInfo))
	{
		//cout<<"Match::addRider() failed on canAddRider()."<<endl;
		return false;
	}
	myRoute = rInfo;
	myDriver.capacity--;
	myRiders.push_back(rider);
	updateHasMale();
	updateHasFemale();
	updateMinAge();
	updateMaxAge();
	return true;
}

/*
 * Function:		removeRider()
 * Arguments:		routeId
 * Comments:		Iterates through all riders, until one with routeId is found
 * 							Removes such rider
 */
void Match::removeRider(uint32_t route_id)
{
	for(Riders::iterator cur_rider = myRiders.begin(); cur_rider != myRiders.end(); cur_rider++)
		if(cur_rider->routeId == route_id)
		{
			myDriver.capacity++;
			myRiders.erase(cur_rider);
			updateDataMembers();
			break;
		}
}

}

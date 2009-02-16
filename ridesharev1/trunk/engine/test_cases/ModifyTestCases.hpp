#ifndef _MODIFYTESTCASES_HPP
#define _MODIFYTESTCASES_HPP

using namespace std;

#include <vector>
#include <string>
#include <stdlib.h>

#include "DBAccess.hpp"
#include "RouteClient.hpp"

#include "RouteSubmission.hpp"
#include "DriverRouteSubmission.hpp"
#include "RoutePreference.hpp"
#include "UserPreference.hpp"


#include "Match.hpp"
#include "Solution.hpp"



namespace testing 
{
	using namespace controller;
	using namespace controller::dba;
	using namespace controller::routes;
	using namespace optimizer;
	using std::string;
	
	typedef RiderRouteSubmission Rider;
	typedef DriverRouteSubmission Driver;
	typedef vector<Rider> Riders;
	typedef vector<Driver> Drivers;
	

uint32_t userId(uint32_t current);
uint32_t routeId(uint32_t current);
size_t capacity(size_t current);
TimeWindow<DateTime> leave(TimeWindow<DateTime> current);
TimeWindow<DateTime> arrive(TimeWindow<DateTime> current);
uint32_t ageMin(size_t current);
uint32_t ageMax(size_t current);
size_t genderPref(size_t current);
double ratingMin(double current);
	
	void modifyTestCases();
}


#endif // #ifndef _MODIFYTESTCASES_HPP

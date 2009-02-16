#ifndef _TESTCASES_HPP
#define _TESTCASES_HPP

#include <vector>
#include "Location.hpp"
#include "Solution.hpp"
#include "SolutionUtils.hpp"

namespace UnitTests
{
		using namespace optimizer;

		typedef vector< Location<double> > Locations;
		typedef Solution::Rider   Rider;
		typedef Solution::Driver  Driver;
		typedef Rider::ptr        RiderPtr;
		typedef Driver::ptr       DriverPtr;
		typedef vector<Rider>     Riders;
		typedef vector<Driver>    Drivers;
		typedef vector<Match>     Matches;
	
	namespace MatchTests
	{
		Location<> r1StartLoc(30.380146, -97.716339, "Metric Blvd");
		Location<> r1EndLoc(30.353078, -97.797554, "W Courtyard Dr");
		Location<> r2StartLoc("Clarkson Ave", 30.301580, -97.716620);
		Location<> r2EndLoc("Shoalwood Ave", 30.319730, -97.743450);
		Location<> r3StartLoc("Windsor Rd ", 30.295440, -97.766850);
		Location<> r3EndLoc("Pegram Ave", 30.347140, -97.740830);
		Location<> r4StartLoc("Balcones Dr ", 30.315670, -97.766570);
		Location<> r4EndLoc("Ferguson Ln ", 30.344667, -97.668879);
		Location<> r5StartLoc("Sherwood Ln ",30.235220, -97.751570);
		Location<> r5EndLoc("Navasota St ", 30.272510, -97.727750);
		Location<> d1StartLoc(30.260180, -97.745700, "Congress Ave S");
		Location<> d1EndLoc(30.352747, -97.643664, "Cameron Rd");
		Location<> d2StartLoc("E Martin Luther King Jr Blvd",30.280530, -97.737770);
		Location<> d2EndLoc("Arroyo Seco", 30.333070, -97.734050);

		TimeWindow<DateTime> d1Leave(DateTime("2008-01-30 08:30:00"),DateTime("2008-01-30 10:30:00"));
		TimeWindow<DateTime> d1Arrive(DateTime("2008-01-30 08:45:00"),DateTime("2008-01-30 12:00:00"));

		TimeWindow<DateTime> r1Leave(DateTime("2008-01-30 08:30:00"),DateTime("2008-01-30 10:30:00"));
		TimeWindow<DateTime> r1Arrive(DateTime("2008-01-30 08:45:00"),DateTime("2008-01-30 12:00:00"));

	
		TimeWindow<DateTime> incompatibleLeave(DateTime("2008-01-29 05:30:00"),DateTime("2008-01-30 03:00:00"));
		TimeWindow<DateTime> incompatibleArrive(DateTime("2008-02-27 06:31:00"),DateTime("2008-02-28 08:00:00"));

		//RoutePreference rPref(leave, arrive);
		RoutePreference incompRPref1(incompatibleLeave,r1Arrive);
		RoutePreference incompRPref2(r1Leave,incompatibleArrive);
		RoutePreference d1RoutePref(d1Leave, d1Arrive);
		RoutePreference d2RoutePref(d1Leave, d1Arrive);
		RoutePreference r1RoutePref(r1Leave, r1Arrive);
	
		UserInfo d1Info("joe","schmoe", "joeschmoe@joeschmoe.com", MALE, 21);
		UserInfo d2Info("joe","schmoe", "joeschmoe@joeschmoe.com", FEMALE, 31);
		UserInfo r1Info("jane","schmoe", "janeschmoe@joeschmoe.com", FEMALE, 32);

		UserInfo r2Info("john","schmoe", "johnschmoe@joeschmoe.com", MALE, 20);
		UserInfo r3Info("jill","schmoe", "jillschmoe@joeschmoe.com", FEMALE, 45);

		UserPreference d1Pref(18,40,DONT_CARE,0);//(ageMin,ageMax, genderId, ratingMin);
		UserPreference d2Pref(18,40,MALE_ONLY,0);
		UserPreference r1Pref(18,33,DONT_CARE,0);
		UserPreference r2Pref(22,32,DONT_CARE,0);
		UserPreference r3Pref(18,30,FEMALE_ONLY,0);
		UserPreference r7Pref(20,32,DONT_CARE,0);
		size_t capacity = 5;
		/*
		 * Compatible cases:
		 * 		{d1,r1}
		 * 		{d2,r2} d2 is a female driver, whose preference is MALE_ONLY
		 * Incompatible cases:
		 * 		{d1,r2} d1's age is 21, r2 requires minAge of 22
		 * 		{d1,r3} r3's pref is FEMALE_ONLY, d1 is male
		 * 		{d1,r4} incompatible time windows, rider leave window incompatible
		 * 		{d1,r5} incompatible time windows, rider arrive window incompatible
		 * 		
		 * 		{d2,r1} r1 is a female, d2's pref is MALE_ONLY
		 * 		{d2,r3} r3 is a FEMALE, d2 wants only MALES. r3 is 45 years old, d2 has maxAge 40.
		 * 		{d2,r4} d2 requires MALE_ONLY, r4 is FEMALE. incompatible time windows, rider leave window incompatible
		 * 		{d2,r5} d2 requires MALE_ONLY, r5 is FEMALE. incompatible time windows, rider arrive window incompatible
		 */
		Driver d1(1,1, d1StartLoc,d1EndLoc, d1Pref, d1RoutePref, d1Info, 42.52, capacity);
		Driver d2(2,2, d2StartLoc, d2EndLoc, d2Pref, d2RoutePref, d2Info, 42.52, capacity);
		Rider r1(3,3, r1StartLoc, r1EndLoc, r1Pref, r1RoutePref, r1Info, 42.52);
		Rider r2(4,4, r2StartLoc, r2EndLoc, r2Pref, r1RoutePref, r2Info, 42.52);
		Rider r3(5,5, r3StartLoc, r3EndLoc, r3Pref, r1RoutePref, r3Info, 42.52);
		Rider r4(6,6, r4StartLoc, r4EndLoc, d1Pref, incompRPref1, r1Info, 42.52);
		Rider r5(7,7, r5StartLoc, r5EndLoc, d1Pref, incompRPref2, r1Info, 42.52);
		Rider r6(8,8, r1StartLoc, r1EndLoc, r1Pref, r1RoutePref, r1Info, 42.52);//same as r1
		Rider r7(9,9, r2StartLoc, r2EndLoc, r7Pref, r1RoutePref, r2Info, 42.52);//same as r2, except for user preferences
	}



	namespace TestCases
	{
	
		static const size_t NUM_SAMPLE_DRIVERS = 2;
		static const size_t NUM_SAMPLE_RIDERS  = 4;
		static const size_t NUM_SAMPLE_MATCHES = 2;
		//TODO: These test cases are broken, since they contain no valid dates
		//			Add dates.
		Matches getSampleMatches()
		{
			RiderPtr r1 = getRiderSubmission(
					Location<>(30.380146, -97.716339, "Metric Blvd")
				, Location<>(30.353078, -97.797554, "W Courtyard Dr")
				);

			RiderPtr r2 = getRiderSubmission(
					Location<>("Clarkson Ave", 30.301580, -97.716620)
				, Location<>("Shoalwood Ave", 30.319730, -97.743450)
				);

			RiderPtr r3 = getRiderSubmission(
					Location<>("Windsor Rd ", 30.295440, -97.766850)
				, Location<>("Pegram Ave", 30.347140, -97.740830)
				);

			RiderPtr r4 = getRiderSubmission(
					Location<>("Balcones Dr ", 30.315670, -97.766570)
				, Location<>("Ferguson Ln ", 30.344667, -97.668879)
				);

			RiderPtr r5 = getRiderSubmission(
					Location<>("Sherwood Ln ",30.235220, -97.751570)
				, Location<>("Navasota St ", 30.272510, -97.727750)
				);

			DriverPtr d1 = getDriverSubmission(
					Location<>(30.260180, -97.745700, "Congress Ave S")
				, Location<>(30.352747, -97.643664, "Cameron Rd")
				, 4);

			DriverPtr d2 = getDriverSubmission(
					Location<>("E Martin Luther King Jr Blvd",30.280530, -97.737770)
				, Location<>("Arroyo Seco", 30.333070, -97.734050)
				, 3);
			
			Riders riders1;
			riders1.push_back(*r1); riders1.push_back(*r2);
			Match match1(*d1, riders1);

			Riders riders2;
			riders2.push_back(*r3); riders2.push_back(*r4);
			Match match2(*d2, riders2);

			Matches retMatches;
			retMatches.push_back(match1);  retMatches.push_back(match2);
			return retMatches;
		}

		Drivers getSampleDrivers()
		{
			Drivers retDrivers;

			DriverPtr d1 = getDriverSubmission(
					Location<>(30.234330, -97.723100, "e riverside dr")
				, Location<>(30.384559, -97.745226, "jollyville road")
				, 2);

			DriverPtr d2 = getDriverSubmission(
					Location<>(30.265740, -97.771830, "Andre Zilker Rd")
				, Location<>(30.328469, -97.711066, "E Highland Mall Blvd")
				, 1);
			
			retDrivers.push_back(*d1);
			retDrivers.push_back(*d2);

			return retDrivers;
		}

		Riders getSampleRiders()
		{
			Riders retRiders;
			RiderPtr r1 = getRiderSubmission(
					Location<>(30.323100, -97.783600, "Anikawi Dr")
				, Location<>(30.340330, -97.771760, "Creek Mtn")
				);

			RiderPtr r2 = getRiderSubmission(
					Location<>(30.380151, -97.716339, "Metric Blvd")
				, Location<>(30.353081, -97.797554, "W Courtyard Dr")
				);
			
			RiderPtr r3 = getRiderSubmission(
					Location<>(30.383043, -97.673819, "I-35 S")
				, Location<>(30.336600, -97.711910, "W St Johns Ave")
				);
			
			RiderPtr r4 = getRiderSubmission(
					Location<>(30.342040, -97.663400,"Ferguson Ln")
				, Location<>(30.297984, -97.649651, "Johnny Morris Rd")
				);
			
			retRiders.push_back(*r1);
			retRiders.push_back(*r2);
			retRiders.push_back(*r3);
			retRiders.push_back(*r4);

			return retRiders;
		}

	}

}

#endif // #ifndef _TESTCASES_HPP

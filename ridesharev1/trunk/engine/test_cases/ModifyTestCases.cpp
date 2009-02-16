using namespace std;

#include "ModifyTestCases.hpp"

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

uint32_t userId(uint32_t current){
	return current;
	// return 3;
}
uint32_t routeId(uint32_t current){
	static uint32_t baseRouteId = 12010;
	return baseRouteId++;
}
size_t capacity(size_t current){
	// size_t randMax = 4;
	return current;
	// return (rand()%randMax + 1);
	// return 3;
}

TimeWindow<DateTime> leave(TimeWindow<DateTime> current){
	//TimeWindow<DateTime> leaveWindow(DateTime("2008-08-01 00:00:01"), 
	//	DateTime("2008-08-02 23:59:59"));
	 return current;
	// return leaveWindow;
}

TimeWindow<DateTime> arrive(TimeWindow<DateTime> current){
	//TimeWindow<DateTime> arriveWindow(DateTime("2008-08-01 00:00:01"), 
	//	DateTime("2008-08-03 23:59:59"));
	 return current;
	// return arriveWindow;
}

uint32_t ageMin(size_t current){
	return current;
	// return 18;
}
uint32_t ageMax(size_t current){
	return current;
	// return 80;
}

size_t genderPref(size_t current){
	return current;
	// return 0;
}
double ratingMin(double current){
	return current;
	//return 0;
}


void modifyTestCases(void){
		/* Variables:
		 *  Change these to change the test cases 
		 */
		
		string readComment = "Test_Data_1"; // read these comments as input from DB
		string writeComment = "Test_Data_2"; // write these comments as output from DB
		
		bool getRiders = 1;
		bool getDrivers = 1;
// All other vars,
		// EDIT FUNCTIONS ABOVE TO DO THIS!!!
		
		/* End variables */

		string host = "rideshare.ece.utexas.edu";
		string user = "jonas";
		string pw   = "letmein2";
		string db   = "rideshare";

	
		printf("\nModifying Test Cases...\n\n");
		
		ReturnCode success;
		
		cout << "\nConnecting to database... ";
		DBAccess::ptr dba;
		dba.reset(new DBAccess(host, db, user, pw));
		cout << "Done.\n\n";
			
		Riders riders;
		if (getRiders){
			cout << "Getting Riders...";
			riders = dba->getRiderSubmissions(readComment);
			cout << "got " << riders.size() << endl;
		}

		Drivers drivers;
		if (getDrivers){
			cout << "Getting Drivers...";
			drivers = dba->getDriverSubmissions(readComment);
			cout << "got " << drivers.size() << endl;
		}

		cout << "\nNow starting Riders...\n";
		for(uint32_t ii = 0; ii < riders.size(); ii++){
		
			cout << "Rider "<<ii<<"'s starting address: "<<riders[ii].startLoc().addr.street<<endl; 
			cout << "Rider "<<ii<<"'s   ending address: "<<riders[ii].endLoc().addr.street<<endl; 

			riders[ii].comment = writeComment;
			cout << "writeComment: " << writeComment << ", Rider "<<ii<<"'s comment: " << riders[ii].comment << endl;
			
			riders[ii].routeId = routeId(riders[ii].routeId); 
				riders[ii].userPref.routeId = riders[ii].routeId; // needs same
			riders[ii].userId = userId(riders[ii].userId);
				riders[ii].userPref.userId = riders[ii].userId; // must be same
			
			riders[ii].userPref.ageMin = ageMin(riders[ii].userPref.ageMin);
			riders[ii].userPref.ageMax = ageMax(riders[ii].userPref.ageMax);
			riders[ii].userPref.genderId = genderPref(riders[ii].userPref.genderId);
			riders[ii].userPref.ratingMin = ratingMin(riders[ii].userPref.ratingMin);

			riders[ii].routePref.leaveWindow = leave(riders[ii].routePref.leaveWindow);
			riders[ii].routePref.arriveWindow = arrive(riders[ii].routePref.arriveWindow);
			
			RouteSubmission::ptr temp(new Rider(riders[ii]));
			success = dba->writeRouteSubmission(temp);
			if (success == SUCCESS){
				cout << "Rider " << ii << " written to DB as routeId "<<riders[ii].routeId << endl;
			}
			success = dba->writeRouteUserPreference(riders[ii].userPref);
			if (success == SUCCESS){
				cout << "Rider's " << ii << " user preferences written to DB with routeId "<<riders[ii].routeId << endl;
			}
			cout << endl;
		}
		
		cout << "\nNow starting Drivers...\n";
		for(uint32_t ii = 0; ii < drivers.size(); ii++){
			cout << "Driver " <<ii<<"'s starting address: "<<drivers[ii].startLoc().addr.street<<endl; 
			cout << "Driver "<<ii<<"'s   ending address: "<<drivers[ii].endLoc().addr.street<<endl; 

			drivers[ii].comment = writeComment;
			cout << "writeComment: " << writeComment << ", Driver "<<ii<<"'s comment: " << drivers[ii].comment << endl;

			drivers[ii].routeId = routeId(drivers[ii].routeId);
				drivers[ii].userPref.routeId = drivers[ii].routeId; // needs same
			drivers[ii].userId = userId(drivers[ii].userId);
				drivers[ii].userPref.userId = drivers[ii].userId; // must be same
			
			drivers[ii].capacity = capacity(drivers[ii].capacity);
			
			drivers[ii].userPref.ageMin = ageMin(drivers[ii].userPref.ageMin);
			drivers[ii].userPref.ageMax = ageMax(drivers[ii].userPref.ageMax);
			drivers[ii].userPref.genderId = genderPref(drivers[ii].userPref.genderId);
			drivers[ii].userPref.ratingMin = ratingMin(drivers[ii].userPref.ratingMin);

			drivers[ii].routePref.leaveWindow = leave(drivers[ii].routePref.leaveWindow);
			drivers[ii].routePref.arriveWindow = arrive(drivers[ii].routePref.arriveWindow);
			
			DriverRouteSubmission::ptr temp(new Driver(drivers[ii]));
			success = dba->writeDriverRouteSubmission(temp);
			if (success == SUCCESS){
				cout << "Driver " << ii << " written to DB as routeId "<< drivers[ii].routeId << endl;
			}
			success = dba->writeRouteUserPreference(drivers[ii].userPref);
			if (success == SUCCESS){
				cout << "Driver " << ii << "'s preferences written to DB as routeId "<< drivers[ii].routeId << endl;
			}
			cout << endl;
		}
	}
}



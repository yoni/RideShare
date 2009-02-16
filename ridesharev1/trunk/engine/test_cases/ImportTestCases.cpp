using namespace std;

#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "DBAccess.hpp"
#include "RouteClient.hpp"
#include "RouteSubmission.hpp"
#include "DriverRouteSubmission.hpp"
#include "RoutePreference.hpp"
#include "UserPreference.hpp"
#include "Match.hpp"
#include "Solution.hpp"

#include "ModifyTestCases.hpp"
bool useLocalMatrix = true;

namespace testing 
{
	using namespace controller;
	using namespace controller::dba;
	using namespace controller::routes;
	using namespace optimizer;
	using std::string;

	void Tokenize(const string& str, vector<string>& tokens,
		 const string& delimiters = " ")
	{
		// Skip delimiters at beginning.
		string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// Find first "non-delimiter".
		string::size_type pos = str.find_first_of(delimiters, lastPos);
		while (string::npos != pos || string::npos != lastPos){
			// Found a token, add it to the vector.
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			// Skip delimiters.  Note the "not_of"
			lastPos = str.find_first_not_of(delimiters, pos);
			// Find next "non-delimiter"
		  pos = str.find_first_of(delimiters, lastPos);
		}
	}
	
	
	void importTestCases(void){
		/* Variables:
		 *  Change these to change the test cases 
		 */
		string testComment = "Raw";
		uint32_t userID = 3; 
		uint32_t baseRouteID = 9000;
		TimeWindow<DateTime> leave(DateTime("2008-08-01 00:00:01"), 
			DateTime("2008-08-02 23:59:59"));
		TimeWindow<DateTime> arrive(DateTime("2008-08-01 00:00:01"), 
			DateTime("2008-08-03 23:59:59"));
		
		size_t capacityRandMax = 4; // will be 1-4 spots
		uint32_t minAge = 18;
		uint32_t maxAge = 80;
		uint32_t genderPref = 0; // 1 is male, 2 is female 
		uint32_t minRating = 0; // anyone.
		
		size_t oneInRider = 4; // 4 means 1/4 chance there will be a driver.
		size_t cleanup = 0; // 0 for don't, anything else for delete after we write.
		/* End variables */
		string host = "rideshare.ece.utexas.edu";
		string user = "jonas";
		string pw   = "letmein2";
		string db   = "rideshare";

		printf("\nImporting Test Cases...\n\n");
		
		vector<string> tokens;
		fstream inputStream;
		// inputStream.open("testUShipData.csv");
		inputStream.open("uShipData.csv");
		if(!inputStream){
			printf("Failed to open file!\n");
		}else{
			string temp;
			Address startAddr;
			Address endAddr;
			Location<> startLoc;
			Location<> endLoc;
			RouteClient tempClient;
			
			cout << "\nConnecting to database... ";
			DBAccess::ptr dba;
			dba.reset(new DBAccess(host, db, user, pw));
			cout << "Done.\n\n";
			
			uint32_t linecount = 1;
			
			while (!inputStream.eof()){
				tokens.clear();
				getline(inputStream, temp); 
				Tokenize(temp, tokens, ";");
				if (tokens.size() >= 4){ // we have complete addresses, probably
					string start = tokens[2] + " " + tokens[0];
					string end = tokens[3] + " " + tokens[1];
					cout << "line " << linecount << ", start: " << start << endl;
					cout << "line " << linecount << ", end: " << end << endl;
					
					startAddr = Address(tokens[2], "", "", tokens[0], "");
					endAddr = Address(tokens[3], "", "", tokens[1], "");
					startLoc = tempClient.getLocationFromAddress(startAddr);
					endLoc = tempClient.getLocationFromAddress(endAddr);
					cout << "line " << linecount << ", startLoc: (" << startLoc.lat << ", " << startLoc.lng << ")\n";
					cout << "line " << linecount << ", endLoc: (" << endLoc.lat << ", " << endLoc.lng << ")\n";
					
					if (startLoc.lat == endLoc.lat && startLoc.lng == endLoc.lng){
						cout << "Whoops! Line "<< linecount << "'s Starting point is the same as its End point!\n";
					}else{ // Adding to Database
						int routeID = baseRouteID + linecount;
						
						RoutePreference rPref(leave, arrive);
						UserPreference  uPref(routeID, userID, minAge, maxAge, genderPref, minRating); //should be loose enough
						RouteClient::Locations locs;
						locs.push_back(startLoc);
						locs.push_back(endLoc);
						RouteInfo<double> rInfo = tempClient.getRouteInfo(locs, RouteClient::MQ_SERVER);
						double routeLength = rInfo.getRouteDistance();
						double routeTime = rInfo.getRouteTime();
						routeTime = routeTime*60; // Seconds!
						cout << "Route " << linecount << " length = " << routeLength << " miles.\n";
						cout << "Route " << linecount << " time = " << routeTime << " seconds.\n";
						
						size_t capacity = rand()%capacityRandMax + 1;
						size_t rider = rand()%oneInRider;
						
						ReturnCode success1, success2;
						if (rider){ /* Rider */
							RouteSubmission::ptr rSubmission(new RiderRouteSubmission
								(routeID, userID, startLoc, endLoc, uPref, rPref, routeLength));  
							rSubmission->setComment(testComment);
							success1 = dba->writeRouteUserPreference(uPref);
							if (success1 == SUCCESS)
								cout << "Line " << linecount << " route Prefs written to database as a Rider with RouteID " << (baseRouteID + linecount) << endl;
							success2 = dba->writeRouteSubmission(rSubmission, start, end); // actually do the write
							if (success2 == SUCCESS)
								cout << "Line " << linecount << " written to database as a Rider with RouteID " << (baseRouteID + linecount) << endl;
						}else{ /* Driver */
							RouteSubmission::ptr rSubmission(new DriverRouteSubmission
								(routeID, userID, startLoc, endLoc, uPref, rPref, routeLength, capacity));
							rSubmission->setComment(testComment);
							success1 = dba->writeRouteUserPreference(uPref);
							if (success1 == SUCCESS)
								cout << "Line " << linecount << " route Prefs written to database as a Driver with RouteID " << (baseRouteID + linecount) << endl;
							success2 = dba->writeDriverRouteSubmission(rSubmission, start, end, routeLength, routeTime); // actually do the write
							if (success2 == SUCCESS)
								cout << "Line " << linecount << " written to database as a Driver with RouteID " << (baseRouteID + linecount) << endl;
						}
						if ((success1 == SUCCESS ) && (success2 == SUCCESS)){
							/* nothing */
						}else{
							cout << "Line " << linecount << " failed to write for some reason.\n" << endl;
						}
						if (cleanup){
							success1 = dba->deleteRouteSubmission(routeID); // delete 
							success2 = dba->deleteRoutePreference(routeID);
							cout << "RouteID " << routeID << " deleted from database (route & prefs)." << endl;
						}
					}
					linecount++;
				}else{ // bad line
					cout << "Line "<< linecount << " failed: not enough information.\n";
				}
				cout << endl;
			}
		}
		inputStream.close();
	}
}


int main()
{
	testing::modifyTestCases();
}



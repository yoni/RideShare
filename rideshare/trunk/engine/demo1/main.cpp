#include <iostream>
#include <string>
#include "DBAccess.hpp"
#include "RouteClient.hpp"
#include "RouteInfo.hpp"
#include "TesterUtil.hpp"

using std::string;
using controller::dba::DBAccess;
using controller::routes::RouteClient;
using controller::routes::RouteInfo;
using namespace UnitTests;

int main()
{
	std::string host = "rideshare.ece.utexas.edu";
	std::string user = "jonas";
	std::string pw   = "letmein2";
	std::string db   = "rideshare";

	DBAccess::ptr dba(new DBAccess(host, db, user, pw));
	//populateDB(dba);

	DBAccess::RouteSubmissions offers =   dba->getDriverSubmissions();
	DBAccess::RouteSubmissions requests = dba->getRiderSubmissions();
	RouteClient::Locations locs;

	std::cout<<"There are " << offers.size() << " drivers\n";
	std::cout<<"There are " << requests.size() << " riders\n";
	ASSERT_GT(1, offers.size());
	ASSERT(1, 1);
	
	// create Route with 1st driver
	for (size_t zz = 0; zz < 1; zz++)
	{
		locs.push_back(offers[zz].startLoc());
		for (size_t ii = 0; ii < requests.size(); ii++)
		{
			locs.push_back(requests[ii].startLoc());
			locs.push_back(requests[ii].endLoc());
			std::cout<<"adding request \n";
		}
		locs.push_back(offers[zz].endLoc());
	}

	RouteClient rClient;
	RouteInfo<double> rInfo = rClient.getRouteInfo(locs, RouteClient::MQ_SERVER);
	rInfo.printAllPoints();
	std::cout<< "\n Route Narrative \n" << rClient.getRouteDirections(locs) << std::endl;
	RouteClient::RouteResults result = rClient.getMQRouteResults();
	rClient.createRouteImage(result, "demo_img.gif");
	return 0;

}



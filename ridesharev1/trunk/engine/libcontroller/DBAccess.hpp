#ifndef _DBACCESS_
#define _DBACCESS_

#include <string>
#include <boost/shared_ptr.hpp>
#include <mysql++/mysql++.h>
#include <vector>
#include "UserInfo.hpp"
#include "RiderRouteSubmission.hpp"
#include "DriverRouteSubmission.hpp"
#include "UserPreference.hpp"
#include "Solution.hpp"

namespace controller 
{
	namespace routes {
		template <class T>
		class PointInfo;
	}
}

namespace controller
{
namespace dba
{

using mysqlpp::Connection;
using mysqlpp::Row;
using mysqlpp::Result;
using mysqlpp::Query;
using controller::RiderRouteSubmission;
using controller::DriverRouteSubmission;
using optimizer::Solution;
using std::string;
using std::vector;
using boost::shared_ptr;
using controller::routes::PointInfo;

enum ReturnCode { SUCCESS, FAIL };
enum SubmissionType { RIDER, DRIVER, ALL };

class DBAccess
{

	public:
		typedef shared_ptr<DBAccess> ptr;
		typedef shared_ptr<Connection> ptrCon;
		typedef shared_ptr<Solution> SolutionPtr;
		typedef vector<RouteSubmission> RouteSubmissions;
		typedef RiderRouteSubmission Rider;
		typedef DriverRouteSubmission Driver;
		typedef vector<Rider> Riders;
		typedef vector<Driver> Drivers;
		typedef Solution::MatchesMap MatchesMap;

		DBAccess(string host, string db, string user, string pw)
			: myConnection(new Connection(false))
		{
			myConnection->connect(db.c_str(), host.c_str(), user.c_str(), pw.c_str());
		}

		Query getQuery() const { return myConnection->query(); }

		vector<string> getUserEmails(const Solution &solu) const;
		Result query(string) const;
		RouteSubmission::ptr getRouteSubmission(uint32_t) const;
		Driver getDriverRouteSubmission(uint32_t) const;

		Drivers getDriverSubmissions() const;
		Riders getRiderSubmissions() const;

		/* Added for Test Case querying by comment */
		Drivers getDriverSubmissions(string comment) const;
		Drivers getDriverSubmissionsNoCapacity(string comment) const;
		Drivers getDriverSubmissions(vector<string> comments) const;
		Riders getRiderSubmissions(string comment) const;
		Riders getRiderSubmissions(vector<string> comments) const;
		
		UserPreference getRoutePreference(uint32_t routeId) const;
		UserInfo getUserInfo(uint32_t userId) const;
		UserPreference getUserPreference(uint32_t userId) const;
		ReturnCode updateRouteSubmission(const PointInfo<> &point, 
																			uint32_t solutionId, uint32_t matchId);

		ReturnCode writeRouteUserPreference(const UserPreference &uPref);
		ReturnCode writeUserPreference(const UserPreference &uPref);
		ReturnCode writeDriverRouteSubmission(DriverRouteSubmission::ptr rs);
		ReturnCode writeRouteSubmission(RouteSubmission::ptr );
		ReturnCode writeSolution(const SolutionPtr, uint32_t &solId );
		ReturnCode writeSolution(const SolutionPtr );
		ReturnCode writeSolution(const Solution& sol );

		/* added to deal with test case strings */
		ReturnCode writeDriverRouteSubmission(RouteSubmission::ptr rs, 
				string start, string end, double optimalRouteDistance, double optimalRouteTime);

		ReturnCode writeRouteSubmission(RouteSubmission::ptr, string start, string end);
		ReturnCode writeMatchRow(uint32_t seqId, uint32_t solutionId,
				uint32_t matchId, const PointInfo<> &point, const TimeWindow<DateTime> times);

		ReturnCode deleteRoutePreference(uint32_t routeId );
		ReturnCode deleteRouteSubmission(uint32_t routeId );
		ReturnCode deleteSolution(uint32_t solutionId );
		ReturnCode deleteUserPreference(uint32_t userId );;

	private:
		ptrCon myConnection;
		ReturnCode writeRouteSubmission(RouteSubmission::ptr, double optimalDistance, size_t capacity);
		ReturnCode writeRouteSubmission(RouteSubmission::ptr, string start, string end, double , double );
		RouteSubmission::ptr getRouteSubmissionFromRowFetch(const Row&) const;
		/* Added for Test Case querying by comment */
		RouteSubmissions getRouteSubmissions(SubmissionType, string comment) const;
		RouteSubmissions getRouteSubmissions(SubmissionType, vector<string> comments) const;
		string getRouteSubmissionIdsInSolution(const Solution &solu) const;
};

}
}

#endif

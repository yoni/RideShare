#include <string>
#include "Utils.hpp"
#include "RiderRouteSubmission.hpp"
#include "DriverRouteSubmission.hpp"
#include "UserInfo.hpp"
#include "UserPreference.hpp"
#include "RouteMatrixLocal.hpp"

namespace controller
{
	using std::string;
	using controller::routes::RouteMatrixLocal;

	/**
	 * Returns a ConfirmType from a string
	 **/
	ConfirmType getConfirmType(string confirm)
	{
		ConfirmType retType;
		if (confirm == "confirmed")
			retType = CONFIRMED;
		else if(confirm == "unconfirmed")
			retType = UNCONFIRMED;

		return retType;
	}

	/**
	 * Returns a RideType from a string
	 **/
	RideType getRideType(string ride)
	{
		RideType ret;
		if (ride == "driver")
			ret = DRIVER;
		else if(ride == "rider")
			ret = RIDER;

		return ret;
	}

	/**
	 * createRouteSubmission
	 *  @desc: takes in row from the routes table and UserPreference object 
	 *  and returns RouteSubmission object
	 **/
	RouteSubmission::ptr createRouteSubmission(const Row& row, 
			const UserPreference &uPref, 
			const UserInfo &uInfo)
	{
		uint32_t            routeId, userId;
		Location<double>     startLoc, endLoc;

		string      strTime, strDate;
		double       optimalDistance;
		string      rideType;

		string      str;

		userId    = row["user_id"];
		routeId   = row["route_submission_id"];
		
		startLoc.lat  = row["start_location_lat"];
		startLoc.lng  = row["start_location_lon"];
		startLoc.addr.street = row["start_addr"].get_string();
		endLoc.lat    = row["end_location_lat"];
		endLoc.lng    = row["end_location_lon"];
		endLoc.addr.street = row["end_addr"].get_string();



		DateTime leaveEarliest(row["leave_time_earliest"].get_string());
		DateTime leaveLatest(row["leave_time_latest"].get_string());
		DateTime arriveEarliest(row["arrive_time_earliest"].get_string());
		DateTime arriveLatest(row["arrive_time_latest"].get_string());

		TimeWindow<DateTime>  leaveWindow(leaveEarliest, leaveLatest);
		TimeWindow<DateTime>  arriveWindow(arriveEarliest, arriveLatest);

		optimalDistance  = RouteMatrixLocal::getDistance(startLoc, endLoc);
		// optimalTime = row["optimal_route_time"]; // except there is none..
			
		rideType         = row["driver_or_rider"].get_string();

		RoutePreference rPref(leaveWindow, arriveWindow);
		RouteSubmission::ptr retRoute;
		switch (getRideType(rideType))
		{
			case RIDER:
				retRoute.reset( 
						new RiderRouteSubmission(routeId, userId, startLoc, endLoc
										, uPref, rPref, uInfo, optimalDistance
										)
						);
				break;
			case DRIVER:
				retRoute.reset( 
						new DriverRouteSubmission(routeId, userId, startLoc, endLoc
										, uPref, rPref, uInfo, optimalDistance, 0
										)
						);
				break;
		}

		retRoute->setComment(row["comment"].get_string());
		return retRoute;
	}

	/* 
	 * Functions:			convertToPtime()
	 * Arguments:			TimeWindow<DateTime>
	 * Return:				TimeWindow<boost::ptime>
	 * Comments:			converts TimeWindow from DateTime to ptime
	 */
	TimeWindow<ptime> convertToPtime(TimeWindow<DateTime> tw) {
		//cout<<"DateTime format: (" << tw.startTime<<","<<tw.endTime<<")"<<endl;
		
		std::stringstream ss;
		ss << tw.startTime;
		ptime startPt(time_from_string(ss.str()));
		
		std::stringstream ss2;
		ss2 << tw.endTime;
		ptime endPt(time_from_string(ss2.str()));
		TimeWindow<ptime> pTimeWindow(startPt,endPt);
		
		//cout<<"ptime format: (" << startPt<<","<<endPt<<")"<<endl;
		return pTimeWindow;
	}

	/* 
	 * Functions:			convertToDateTime()
	 * Arguments:			TimeWindow<ptime>
	 * Return:				TimeWindow<DateTime>
	 * Comments:			converts TimeWindow from ptime to DateTime
	 */
	TimeWindow<DateTime> convertToDateTime(TimeWindow<ptime> tw) {
		const int T = 10;//index of 'T' in iso_extended_string
		//convert to string, replace 'T' with space (' ')
		string start = to_iso_extended_string(tw.startTime);
		string end = to_iso_extended_string(tw.endTime);
#if 0
		//cout<<"Time window conversion from ptime to DateTime."<<endl;
		//cout<<"Ptime format: (" << tw.startTime<<","<<tw.endTime<<")"<<endl;
		//cout<<"String format: (" << start<<","<<end<<")"<<endl;
#endif
		start.replace(T, 1, " ");
		end.replace(T, 1, " ");
		//cout<<"String format after removing 'T': (" << start<<","<<end<<")"<<endl;

		DateTime startDT(start);
		DateTime endDT(end);
		//cout<<"DateTime format: (" << startDT<<","<<endDT<<")"<<endl;
		
		TimeWindow<DateTime> dtTimeWindow(startDT,endDT);
		return dtTimeWindow;
	}
}

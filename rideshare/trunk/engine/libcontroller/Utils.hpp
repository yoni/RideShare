#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include <mysql++/mysql++.h>
#include "TimeWindow.hpp"
#include "mysql++/datetime.h"
#include <boost/date_time/posix_time/posix_time.hpp>


namespace controller
{
	using std::string;
	using mysqlpp::Row;
	using namespace boost::posix_time;
	
	class UserPreference;
	class RouteSubmission;
	class UserInfo;

	typedef boost::shared_ptr< RouteSubmission > RouteSubmissionPtr;
	enum RideType { DRIVER = 0, RIDER };
	enum ConfirmType { CONFIRMED = 0, UNCONFIRMED };
	enum GenderType { MALE = 1, FEMALE = 2 };
	enum RouteMatrixInitType { FLUSH = 1, NO_FLUSH = 2 };
	
	//Gender Preferences
	const size_t DONT_CARE = 0;
	const size_t MALE_ONLY = 1;
	const size_t FEMALE_ONLY = 2;
	
	//maximum deviation for a match, as a percentage. used in Match::canAddRider()
	const double MAX_DEVIATION = 1.33;
	
	//sentinels
	const size_t UNSPECIFIED_AGE = 0;
	const size_t UNSPECIFIED_MIN_AGE = 0;
	const size_t UNSPECIFIED_MAX_AGE = 255;
	const size_t UNSPECIFIED_GENDER = 0;

	enum LocationType { START=1, END=2 };

	//int32_t MINS_IN_HOUR;
	//int32_t MINS_IN_DAY;
	ConfirmType getConfirmType(string confirm);
	RideType getRideType(string ride);
	RouteSubmissionPtr createRouteSubmission(const Row& row, 
			const UserPreference& uPref, const UserInfo& uInfo);

	/* 
	 * Function:			convertTime()
	 * Arguments:			TimeWindow<DateTime>
	 * Return:				TimeWindow<boost::ptime>
	 * Comments:			converts TimeWindow from DateTime to ptime
	 */
	TimeWindow<ptime> convertToPtime(TimeWindow<DateTime> tw); 
	/* 
	 * Functions:			convertTime()
	 * Arguments:			TimeWindow<ptime>
	 * Return:				TimeWindow<DateTime>
	 * Comments:			converts TimeWindow from ptime to DateTime
	 */
	TimeWindow<DateTime> convertToDateTime(TimeWindow<ptime> tw);
} // end namespace

#endif

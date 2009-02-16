#ifndef _ROUTEPREFERENCE_HPP
#define _ROUTEPREFERENCE_HPP

#include "Preference.hpp"
#include <string>
#include "TimeWindow.hpp"


namespace controller
{
using std::string;

class RoutePreference : public Preference
{
	public:
	RoutePreference(TimeWindow<DateTime> _leave, TimeWindow<DateTime> _arrive)
			: Preference()
			, leaveWindow(_leave)
			, arriveWindow(_arrive)
	{}

	RoutePreference(const RoutePreference& rhs)
		: Preference()
		, leaveWindow(rhs.leaveWindow)
		, arriveWindow(rhs.arriveWindow)
	{}
	
	RoutePreference()
	{}

	TimeWindow<DateTime>  leaveWindow;
	TimeWindow<DateTime>  arriveWindow;
};

}
#endif // #ifndef _ROUTEPREFERENCE_HPP

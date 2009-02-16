#ifndef _DRIVERROUTESUBMISSION_HPP
#define _DRIVERROUTESUBMISSION_HPP
#include <string>
#include <boost/shared_ptr.hpp>
#include "Utils.hpp"
#include "RouteSubmission.hpp"


namespace controller
{

using std::string;
class DriverRouteSubmission : public RouteSubmission
{
	/**
	 * DriverRouteSubmission
	 *   @desc: holds the fields associated with the Route table
	 **/
	public:
		typedef boost::shared_ptr< DriverRouteSubmission > ptr;

		DriverRouteSubmission()
			: RouteSubmission(0, 0, Location<>(), Location<>(), 
												UserPreference(), RoutePreference(), 0)
			, capacity(0)
		{}

		DriverRouteSubmission(uint32_t _routeId, uint32_t _userId
							, Location<double> _startLoc, Location<double> _endLoc
							, UserPreference _userPref, RoutePreference _routePref
							, double _optimalDistance, size_t _capacity)
			: RouteSubmission(_routeId, _userId, _startLoc, _endLoc, 
												_userPref, _routePref, _optimalDistance)
			, capacity(_capacity)
		{}

		DriverRouteSubmission(uint32_t _routeId, uint32_t _userId
							, Location<double> _startLoc, Location<double> _endLoc
							, UserPreference _userPref, RoutePreference _routePref
							, UserInfo _uInfo, double _optimalDistance, size_t _capacity)
			: RouteSubmission(_routeId, _userId, _startLoc, _endLoc, 
												_userPref, _routePref, _uInfo, _optimalDistance)
			, capacity(_capacity)
		{}

		/**
		 * copy constructor
		 **/
		DriverRouteSubmission(const DriverRouteSubmission& rhs)
			: RouteSubmission(rhs)
			, capacity(rhs.capacity)
		{}

		DriverRouteSubmission(uint32_t _routeId, Location<double> _startLoc, Location<double> _endLoc
							, double _optimalDistance, size_t _capacity)
			: RouteSubmission(_routeId, 0, _startLoc, _endLoc, UserPreference()
								, RoutePreference(), UserInfo(), _optimalDistance)
			, capacity( _capacity )
		{}

		string get_type() const { return "driver"; } 
		
		size_t   capacity;
};

} // end namespace


#endif // #ifndef _DRIVERROUTESUBMISSION_HPP

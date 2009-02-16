#ifndef _RIDERROUTESUBMISSION_HPP_
#define _RIDERROUTESUBMISSION_HPP_
#include <string>
#include <boost/shared_ptr.hpp>
#include "Utils.hpp"
#include "RouteSubmission.hpp"

namespace controller
{

using std::string;
class RiderRouteSubmission : public RouteSubmission
{
	/**
	 * RiderRouteSubmission
	 *   @desc: holds the fields associated with the Route table
	 **/
	public:
		typedef boost::shared_ptr< RiderRouteSubmission > ptr;

		RiderRouteSubmission()
			: RouteSubmission(0, 0, Location<>(), Location<>(), 
												UserPreference(), RoutePreference(), 0)
		{}

		RiderRouteSubmission(uint32_t _routeId, uint32_t _userId
							, Location<double> _startLoc, Location<double> _endLoc
							, UserPreference _userPref, RoutePreference _routePref
							, double _optimalDistance)
			: RouteSubmission(_routeId, _userId, _startLoc, _endLoc, 
												_userPref, _routePref, _optimalDistance)
		{}

		RiderRouteSubmission(uint32_t _routeId, uint32_t _userId
							, Location<double> _startLoc, Location<double> _endLoc
							, UserPreference _userPref, RoutePreference _routePref
							, UserInfo _uInfo, double _optimalDistance)
			: RouteSubmission(_routeId, _userId, _startLoc, _endLoc, 
												_userPref, _routePref, 
												_uInfo, _optimalDistance)
		{}

		RiderRouteSubmission(uint32_t _routeId, Location<double> _startLoc, 
				Location<double> _endLoc, double _optimalDistance)
			: RouteSubmission(_routeId, 0, _startLoc, _endLoc, UserPreference()
								, RoutePreference(), UserInfo(), _optimalDistance)
		{}
		
		string get_type() const { return "rider"; }
		uint32_t match_id;//0 if unmatched, driver route_id if matched
		vector<uint32_t> unmatched;//list of match id's that are compatible, but unmatched
};

} // end namespace


#endif // #ifndef _RIDERROUTESUBMISSION_

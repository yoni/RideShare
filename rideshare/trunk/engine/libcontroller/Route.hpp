#ifndef _ROUTE_HPP
#define _ROUTE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "UserPreference.hpp"
#include "RoutePreference.hpp"
#include "TimeWindow.hpp"
#include "Location.hpp"

namespace controller
{

using std::string;
using std::vector;
class Route
{
	/**
	 * Route
	 *   @desc: holds the fields associated with the Route table
	 **/
	public:
		typedef boost::shared_ptr< Route > ptr;

		Route(Location<double> _startLoc, Location<double> _endLoc,
				  UserPreference _userPref, RoutePreference _routePref)
			: userPref(_userPref), routePref(_routePref)
		{
			locs.push_back(_startLoc);
			locs.push_back(_endLoc);
		}
		
		virtual ~Route()
		{}

		Location<double> startLoc() const { return locs[0]; }
		Location<double> endLoc() const { return locs[locs.size() - 1]; }

		Location<double> getLoc(size_t index) const { return locs[index]; }
		size_t           numLocs() const { return locs.size(); }

		UserPreference   userPref;
		RoutePreference  routePref;

	protected:
		vector< Location<double> > locs;
};

} // end namespace

#endif // #ifndef _ROUTE_HPP

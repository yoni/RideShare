#ifndef _POINTINFO_HPP
#define _POINTINFO_HPP

#include "Location.hpp"
#include "Utils.hpp"
namespace controller
{
namespace routes
{

template <class T=double>
class PointInfo
{
	public:
	PointInfo(Location<T> _loc, T _distance, T _time)
		: loc(_loc)
		, distanceMiles(_distance)
		, timeMinutes(_time)
	{}

	PointInfo(uint32_t _routeId, LocationType _locType = START, Location<T> _loc = Location<T>(), 
			T _distance = 0.0, T _time = 0.0)
		: routeId( _routeId )
		, locType( _locType )
		, loc(_loc)
		, distanceMiles(_distance)
		, timeMinutes(_time)
	{}

	uint32_t     routeId;
	LocationType locType;

	Location<T> loc;
	T distanceMiles;
	T timeMinutes;
};

} // end routes namespace
} // end controller namespace

#endif // #ifndef _POINTINFO_HPP

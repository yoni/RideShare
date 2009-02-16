#ifndef _ROUTEOPTIMIZER_HPP
#define _ROUTEOPTIMIZER_HPP

#include "Route.hpp"
#include "RouteMatrix.hpp"
#include "RouteClient.hpp"
#include "Match.hpp"
#include "Utils.hpp"
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
using namespace controller;
using std::vector;
using std::map;
using controller::routes::RouteMatrix;
using controller::routes::RouteInfo;

static const double INF = 99999;
namespace optimizer 
{
typedef boost::shared_ptr< RouteMatrix<double> > RouteMatrixPtr;
typedef struct _RouteElement
{
	uint32_t     routeId;
	Location<>   loc;
	LocationType locType;

} RouteElement;

	typedef vector<RouteElement> RouteElements;
	typedef DriverRouteSubmission Driver;
	typedef RiderRouteSubmission Rider;
	typedef vector<RiderRouteSubmission> Riders;

	RouteInfo<> optimizeRouteOrder(const Match& match, RouteMatrixPtr matrix);
	void optimizeRecursive(RouteElements elems, RouteInfo<> rInfo);
}
#endif

#ifndef _ROUTECLIENT_HPP
#define _ROUTECLIENT_HPP

#include <boost/shared_ptr.hpp>
#include "ifexec.h"
#include "mqservers.hpp"
#include "Location.hpp"
#include "Address.hpp"
#include "RouteInfo.hpp"

namespace optimizer
{
	class Solution;
}

namespace controller
{
namespace routes
{

using std::string;
using std::vector;
using optimizer::Solution;

// forward decs
template <class T>
	class RouteMatrix;
template <class T>
	class RouteInfo;

class RouteClient
{

	public:
		typedef boost::shared_ptr< CMQRouteMatrixResults > MQMatrixPtr;
		typedef vector< Location<double> > Locations;
		typedef CMQRouteResults RouteResults;
		typedef CMQRouteType OptimizeMetric;
		typedef boost::shared_ptr< CMQRouteOptions > pOptions;

		enum CalcType { MQ_SERVER = 1, LOCAL };

		RouteClient()
			: calculationType(MQ_SERVER)
		{
			mqRouteClient.SetServerName(mqRouteServerName);
			mqRouteClient.SetServerPath(mqRouteServerPath);
			mqRouteClient.SetServerPort(mqRouteServerPort);
			mqRouteClient.SetClientId(mqRouteServerClientId);
			mqRouteClient.SetPassword(mqRouteServerPassword);

			mqMapClient.SetServerName(mqMapServerName);
			mqMapClient.SetServerPath(mqMapServerPath);
			mqMapClient.SetServerPort(mqMapServerPort);
			mqMapClient.SetClientId(mqMapServerClientId);
			mqMapClient.SetPassword(mqMapServerPassword);

			mqGeocodeClient.SetServerName(mqGeocodeServerName);
			mqGeocodeClient.SetServerPath(mqGeocodeServerPath);
			mqGeocodeClient.SetServerPort(mqGeocodeServerPort);
			mqGeocodeClient.SetClientId(mqGeocodeServerClientId);
			mqGeocodeClient.SetPassword(mqGeocodeServerPassword);

			initColors();
		}

		~RouteClient()
		{
			routeLocations.RemoveAll();
		}

		Location<double> getLocationFromAddress(const Address &addr);

		void setLocations(const RouteInfo<>& rInfo);
		void setLocations(Locations locations);
		void setCalculationType(CalcType  rt) { calculationType = rt; }

		string              getRouteDirections(Locations locs);
		RouteInfo<double>   getRouteInfo(Locations locs, CalcType info);
		RouteMatrix<double> getRouteMatrix(Locations locs, CalcType info);

		MQMatrixPtr         getMQRouteMatrixResults();
		CMQRouteResults     getMQRouteResults();
		
		void createRouteImage(Solution &solution, string fileName);
		void createRouteImage(CMQRouteResults &routeResults, string filename );
	private:
		typedef long ColorCode;
		typedef vector<ColorCode> Colors;
		Colors colorVector;
		CMQLinePrimitive*  getLineShapeFromRoute(CMQRouteResults& route, ColorCode color);
		CalcType calculationType;
		CMQExec mqRouteClient; 
		CMQExec mqMapClient; 
		CMQExec mqGeocodeClient;
		CMQLocationCollection routeLocations;
		CMQString  getRouteNarrative(CMQRouteResults &routeResults);
		pOptions   myOptions;

		pOptions   getRouteOptions();
		RouteInfo<double> convertMQResults2Info(CMQRouteResults results);
		void addLocation(Location<double> loc);
		uint32_t getDTStyle(size_t index, size_t max);
		RouteInfo<double> getRouteInfo(CalcType info);
		string     getRouteDirections();
		void       initColors();

};


}

}

#endif // #ifndef _ROUTECLIENT_HPP

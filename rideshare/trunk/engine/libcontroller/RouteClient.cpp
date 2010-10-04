#include <iostream>
#include "Solution.hpp"
#include "RouteClient.hpp"

#include "Match.hpp"
#include "RouteInfo.hpp"
#include "RouteMatrix.hpp"
#include <stdlib.h>
#include <map>

using optimizer::Solution;
namespace controller
{
namespace routes
{
	using std::map;

//typedef map<uint32_t,Match> MatchesMap;
static const uint32_t DT_START = 3073;
static const uint32_t DT_MID = 3074;
static const uint32_t DT_END = 3075;

void RouteClient::initColors()
{
	colorVector.push_back(CMQColorStyle::BLACK);
	colorVector.push_back(CMQColorStyle::BLUE);
	colorVector.push_back(CMQColorStyle::CYAN);
	colorVector.push_back(CMQColorStyle::DARK_GRAY);
//	colorVector.push_back(CMQColorStyle::GRAY);
//	colorVector.push_back(CMQColorStyle::GREEN);
//	colorVector.push_back(CMQColorStyle::LIGHT_GRAY);
//	colorVector.push_back(CMQColorStyle::MAGENTA);
//	colorVector.push_back(CMQColorStyle::ORANGE);
//	colorVector.push_back(CMQColorStyle::PINK);
//	colorVector.push_back(CMQColorStyle::RED);
//	colorVector.push_back(CMQColorStyle::WHITE);
//	colorVector.push_back(CMQColorStyle::YELLOW);
}

RouteInfo<double> RouteClient::getRouteInfo(Locations locs, CalcType calcType)
{
	setLocations(locs);
	return getRouteInfo(calcType);
}

Location<double> RouteClient::getLocationFromAddress(const Address &addr)
{
	Location<double> loc(0.0, 0.0, addr);
	// Create Input Address
	CMQAddress Address;

	Address.Init();
	Address.SetStreet(addr.street.c_str());
	Address.SetCity(addr.city.c_str());
	Address.SetState(addr.state.c_str());
	Address.SetPostalCode(addr.zipCode.c_str());
	Address.SetCountry(addr.country.c_str());

	CMQLocationCollection lcOriginResults;

	try
	{
		mqGeocodeClient.Geocode(Address, lcOriginResults);
	}
	catch (CMQException& e)
	{
		printf("CMQException:%s\n", (const char*)e.GetExceptionString());
		return loc;
	}

	CMQGeoAddress* geocodedAddress = NULL;

	// If the results collection's Count property is zero, no matches could be found for the location
	if (lcOriginResults.GetSize() > 0)
	{
		geocodedAddress = (CMQGeoAddress*)lcOriginResults.GetAt(0);
	}
	else
	{
		printf ("The location could not be geocoded.\n");
		return loc;
	}

	loc.lat = geocodedAddress->GetLatLng().GetLatitude();
	loc.lng = geocodedAddress->GetLatLng().GetLongitude();
	return loc;
}

RouteInfo<double> RouteClient::getRouteInfo(CalcType calcType)
{
	RouteInfo<double> rInfo;
	switch (calcType)
	{
		case MQ_SERVER:
		{
			CMQRouteResults routeResults = getMQRouteResults();
			rInfo = convertMQResults2Info(routeResults);
			break;
		}
		case LOCAL:
			//rInfo = getSimpleRouteInfo();
			break;
	}
	return rInfo;
}

RouteMatrix<double> RouteClient::getRouteMatrix(Locations locs, CalcType calcType)
{
	setLocations(locs);
	RouteMatrix<double> rMatrix;
	switch (calcType)
	{
		case MQ_SERVER:
			{
			CMQRouteMatrixResults matrixResults = *getMQRouteMatrixResults();
			rMatrix.setAttr(matrixResults, locs);
			break;
			}
		case LOCAL:
			//rInfo = getSimpleRouteMatrix();
			break;
	}
	return rMatrix;
}

string RouteClient::getRouteDirections()
{
	CMQRouteResults routeResults = getMQRouteResults();
	string narrative( getRouteNarrative(routeResults).Cstring() );
	return narrative;
}

string RouteClient::getRouteDirections(Locations locs)
{
	setLocations(locs);
	return getRouteDirections();
}

/*************** begin private funcs *****************/

RouteClient::pOptions RouteClient::getRouteOptions()
{
	if (myOptions.use_count() == 0)
	{
		myOptions.reset(new CMQRouteOptions());
		myOptions->SetMaxShapePointsPerManeuver(50);
		myOptions->SetNarrativeDistanceUnitType(CMQDistanceUnits::MILES);
		//myOptions->SetRouteType(optimizeMetric);
	}
	return myOptions;
}

CMQRouteResults RouteClient::getMQRouteResults()
{
	pOptions routeOptions = getRouteOptions();
	CMQRouteResults routeResults;
	// This call to the server actually generates the route.
	try
	{
		mqRouteClient.DoRoute(routeLocations, *routeOptions, routeResults, NULL);
	}
	catch (CMQException& e)
	{
		printf("CMQException:%s\n", (const char*)e.GetExceptionString());
		exit(-1);
	}
	return routeResults;
}

RouteClient::MQMatrixPtr RouteClient::getMQRouteMatrixResults()
{
	pOptions routeOptions = getRouteOptions();
	MQMatrixPtr matrixResults(new CMQRouteMatrixResults);
	try
	{
		//std::cout<<"matrix query size:" << routeLocations.GetSize() << std::endl;
		mqRouteClient.DoRouteMatrix(routeLocations, true, *routeOptions, *matrixResults);
		if (matrixResults->GetResultCode() != CMQRouteMatrixResultsCode::SUCCESS)
		{
			std::cout<<"There were errors while creating the route matrix...\n";
			CMQStringCollection strings = matrixResults->ResultMessages();
			for (size_t ii = 0; ii < (size_t)strings.GetSize(); ii ++)
				std::cout<<"Error: " << strings.GetAt(ii).Cstring() << std::endl;
		}

		if (routeLocations.GetSize() != matrixResults->GetLocationCount())
		{
			std::cout<<"RouteMatrix generation has errors\n";
		}

	}
	catch (CMQException& e)
	{
		printf("CMQException:%s\n", (const char*)e.GetExceptionString());
		exit(-1);
	}
	return matrixResults;
}

CMQString RouteClient::getRouteNarrative(CMQRouteResults &routeResults)
{
	CMQString retString;
	size_t numTreks = routeResults.TrekRoutes().GetSize();
	// Each manuever object contains its own narrative, distance and drive time.
	for (size_t rc = 0; rc < numTreks; rc ++)
	{
		size_t numManeuvers = routeResults.TrekRoutes().GetAt(rc)->GetManeuvers().GetSize();
		for (size_t mc=0; mc < numManeuvers; mc++)
		{
			CMQManeuver* man = (CMQManeuver*)routeResults.TrekRoutes().GetAt(rc)->GetManeuvers().GetAt(mc);
			CMQString txtLine;
			txtLine.Format("%d  %.2d   %-54.54s    %.4f    %.2f\n",rc, mc+1,
					(const char*)man->GetNarrative(),1.6103*man->GetDistance(),(man->GetTime() / 60.0));
			retString += txtLine;
		}
	}

	return retString;
}

uint32_t RouteClient::getDTStyle(size_t index, size_t max)
{
	uint32_t thisDT = 0;
	if (index == 0)
	{
		thisDT = DT_START;
	} 
	else if ( index < max - 1)
	{
		thisDT = DT_MID ;
	}
	else if ( index == max -1 )
	{
		thisDT = DT_END;
	}
	return thisDT;
}

CMQLinePrimitive* RouteClient::getLineShapeFromRoute(CMQRouteResults& route, ColorCode color)
{
	// Create the routeHighlight to be displayed on the map using the LinePrimitive
	// object.  This object allows you to insert lines of your own creation into the map.
	CMQLinePrimitive* lpRtHlt = new CMQLinePrimitive;
	lpRtHlt->SetColor(color);
	lpRtHlt->SetKey("RouteShape");
	lpRtHlt->SetStyle(CMQPenStyle::SOLID);
	lpRtHlt->SetCoordinateType(CMQCoordinateType::GEOGRAPHIC);
	lpRtHlt->SetDrawTrigger(CMQDrawTrigger::AFTER_ROUTE_HIGHTLIGHT);
	lpRtHlt->SetWidth(100);

	// The Generalize method reduces the amount of shape points used to represent a line.
	// This example combines all shape points within .01 miles of each other to 1 single
	// shape point.  This removes unnecessary shape points and shortens the URL to minimize
	// the possibility of exceeding some browsers' URL size limitations.  There may still
	// be cases where URL length is an issue, in which case you will need to utilize your
	// own server side storage.
	lpRtHlt->GetLatLngs() = route.GetShapePoints();
	lpRtHlt->GetLatLngs().Generalize(0.01);
	return lpRtHlt;
}


void RouteClient::createRouteImage(Solution &solution, string fileName)
{
	// Create DisplayTypes and pointFeatures for the origin and destination locations
	// to be displayed.  For details regarding DisplayTypes and PointFeatures, see the
	// mapWithPoi sample.
	CMQDTStyle* originDTStyle = new CMQDTStyle;
	originDTStyle->SetDT(DT_START);
	originDTStyle->SetSymbolType(CMQSymbolType::RASTER);
	originDTStyle->SetSymbolName("MQ09191");
	originDTStyle->SetVisible(true);
	originDTStyle->SetLabelVisible(false);

	CMQDTStyle* midDTStyle = new CMQDTStyle;
	midDTStyle->SetDT(DT_MID);
	midDTStyle->SetSymbolType(CMQSymbolType::RASTER);
	midDTStyle->SetSymbolName("MQ00031");
	midDTStyle->SetVisible(true);
	midDTStyle->SetLabelVisible(false);

	CMQDTStyle* destDTStyle = new CMQDTStyle;
	destDTStyle->SetDT(DT_END);
	destDTStyle->SetSymbolType(CMQSymbolType::RASTER);
	destDTStyle->SetSymbolName("MQ09192");
	destDTStyle->SetVisible(true);
	destDTStyle->SetLabelVisible(false);

	CMQCoverageStyle* coverageStyle = new CMQCoverageStyle;

	coverageStyle->Add(originDTStyle);
	coverageStyle->Add(destDTStyle);
	coverageStyle->Add(midDTStyle);

	CMQPrimitiveCollection* pcMap = new CMQPrimitiveCollection;
	CMQFeatureCollection* fcRouteNodes = new CMQFeatureCollection;
	Solution::MatchesMap & matches = solution.myMatches;
	CMQLinePrimitive* lpRtHlt;

	size_t matchIter = 0;
	for(Solution::MatchesMap::const_iterator cur_match = matches.begin();
			cur_match != matches.end();
			cur_match++) 
	{
		setLocations(cur_match->second.myRoute);
		CMQRouteResults results = getMQRouteResults();
		//std::cout<<getRouteDirections();

		ColorCode routeColor = colorVector[matchIter++ % colorVector.size()];
		for(size_t ii = 0; ii < cur_match->second.myRoute.numPoints(); ii++)
		{
			CMQPointFeature* ptfLoc = new CMQPointFeature;
			uint32_t thisDT = getDTStyle(ii, routeLocations.GetSize());

			ptfLoc->SetDT(thisDT);
			CMQGeoAddress *loc = (CMQGeoAddress*) routeLocations.GetAt(ii); 
			ptfLoc->SetCenterLatLng(loc->GetLatLng());
			fcRouteNodes->Add(ptfLoc);
			lpRtHlt = getLineShapeFromRoute(results, routeColor);
		}

		pcMap->Add(lpRtHlt);
	}
	
	// Create the MapState object
	CMQMapState* MapState = new CMQMapState;
	MapState->SetWidthPixels(800);
	MapState->SetHeightPixels(640);

	// Create the Session object.
	CMQSession* mqSession = new CMQSession;
	mqSession->AddOne(MapState);
	mqSession->AddOne(fcRouteNodes);
	mqSession->AddOne(coverageStyle);

	// Add the line primitive to a primitiveCollection
	mqSession->AddOne(pcMap);

	// The best fit object is used to draw a map at an appropriate scale determined 
	// by the features you have added to the session, along with the optional primitives.  
	// In this case we want the map to be displayed at a scale that includes the origin 
	// and destination locations (pointFeatures) as well as the routeHighlight(linePrimitive).
	// The scaleAdjustmentFactor is then used to increase the scale by this factor based
	// upon the best fit that was performed.  This results in a border around the edge of
	// the map that does not include any features so the map appears clearer.
	CMQBestFit* bfMap = new CMQBestFit;
	bfMap->SetScaleAdjustmentFactor(1.2);
	bfMap->SetIncludePrimitives(true);
	mqSession->AddOne(bfMap);

	// Generates the actual GIF image resulting from the given Session Object.
	CMQIOMem mapImage;
	try
	{
		mqMapClient.GetMapImageDirectEx(mqSession, mapImage);
	}
	catch (CMQException& e)
	{
		printf("CMQException:%s\n", (const char*)e.GetExceptionString());
		exit(-1);
	}
	printf("\nwriting %s....\n", fileName.c_str());
	FILE *fp = fopen (fileName.c_str(), "wb");
	fwrite((const char*)mapImage, 1, mapImage.size(), fp);
	fclose (fp);

	// Manage pointers so that only 1 collection deletes objects
	delete mqSession;

}

void RouteClient::createRouteImage(CMQRouteResults &routeResults, string fileName)
{
	// Create DisplayTypes and pointFeatures for the origin and destination locations
	// to be displayed.  For details regarding DisplayTypes and PointFeatures, see the
	// mapWithPoi sample.
	CMQDTStyle* originDTStyle = new CMQDTStyle;
	originDTStyle->SetDT(DT_START);
	originDTStyle->SetSymbolType(CMQSymbolType::RASTER);
	originDTStyle->SetSymbolName("MQ09191");
	originDTStyle->SetVisible(true);
	originDTStyle->SetLabelVisible(false);

	CMQDTStyle* midDTStyle = new CMQDTStyle;
	midDTStyle->SetDT(DT_MID);
	midDTStyle->SetSymbolType(CMQSymbolType::RASTER);
	midDTStyle->SetSymbolName("MQ00031");
	midDTStyle->SetVisible(true);
	midDTStyle->SetLabelVisible(false);

	CMQDTStyle* destDTStyle = new CMQDTStyle;
	destDTStyle->SetDT(DT_END);
	destDTStyle->SetSymbolType(CMQSymbolType::RASTER);
	destDTStyle->SetSymbolName("MQ09192");
	destDTStyle->SetVisible(true);
	destDTStyle->SetLabelVisible(false);

	CMQCoverageStyle* coverageStyle = new CMQCoverageStyle;

	coverageStyle->Add(originDTStyle);
	coverageStyle->Add(destDTStyle);
	coverageStyle->Add(midDTStyle);

	// add all points to route image
	CMQFeatureCollection* fcRouteNodes = new CMQFeatureCollection;
	for (size_t ii = 0; ii < (size_t) routeLocations.GetSize(); ii++)
	{
		CMQPointFeature* ptfLoc = new CMQPointFeature;
		uint32_t thisDT = getDTStyle(ii, routeLocations.GetSize());

		ptfLoc->SetDT(thisDT);
		CMQGeoAddress *loc = (CMQGeoAddress*) routeLocations.GetAt(ii); 
		ptfLoc->SetCenterLatLng(loc->GetLatLng());
		fcRouteNodes->Add(ptfLoc);
	}
	
	// Create the MapState object
	CMQMapState* MapState = new CMQMapState;
	MapState->SetWidthPixels(640);
	MapState->SetHeightPixels(480);

	// Create the Session object.
	CMQSession* mqSession = new CMQSession;
	mqSession->AddOne(MapState);
	mqSession->AddOne(fcRouteNodes);
	mqSession->AddOne(coverageStyle);

	// Create the routeHighlight to be displayed on the map using the LinePrimitive
	// object.  This object allows you to insert lines of your own creation into the map.
	CMQLinePrimitive* lpRtHlt = new CMQLinePrimitive;
	lpRtHlt->SetColor(CMQColorStyle::WHITE);
	lpRtHlt->SetKey("RouteShape");
	lpRtHlt->SetStyle(CMQPenStyle::SOLID);
	lpRtHlt->SetCoordinateType(CMQCoordinateType::GEOGRAPHIC);
	lpRtHlt->SetDrawTrigger(CMQDrawTrigger::AFTER_ROUTE_HIGHTLIGHT);
	lpRtHlt->SetWidth(50);

	// The Generalize method reduces the amount of shape points used to represent a line.
	// This example combines all shape points within .01 miles of each other to 1 single
	// shape point.  This removes unnecessary shape points and shortens the URL to minimize
	// the possibility of exceeding some browsers' URL size limitations.  There may still
	// be cases where URL length is an issue, in which case you will need to utilize your
	// own server side storage.
	lpRtHlt->GetLatLngs() = routeResults.GetShapePoints();
	lpRtHlt->GetLatLngs().Generalize(0.01);

	// Add the line primitive to a primitiveCollection
	CMQPrimitiveCollection* pcMap = new CMQPrimitiveCollection;
	pcMap->Add(lpRtHlt);
	mqSession->AddOne(pcMap);

	// The best fit object is used to draw a map at an appropriate scale determined 
	// by the features you have added to the session, along with the optional primitives.  
	// In this case we want the map to be displayed at a scale that includes the origin 
	// and destination locations (pointFeatures) as well as the routeHighlight(linePrimitive).
	// The scaleAdjustmentFactor is then used to increase the scale by this factor based
	// upon the best fit that was performed.  This results in a border around the edge of
	// the map that does not include any features so the map appears clearer.
	CMQBestFit* bfMap = new CMQBestFit;
	bfMap->SetScaleAdjustmentFactor(1.2);
	bfMap->SetIncludePrimitives(true);
	mqSession->AddOne(bfMap);

	// Generates the actual GIF image resulting from the given Session Object.
	CMQIOMem mapImage;
	try
	{
		mqMapClient.GetMapImageDirectEx(mqSession, mapImage);
	}
	catch (CMQException& e)
	{
		printf("CMQException:%s\n", (const char*)e.GetExceptionString());
		exit(-1);
	}
	printf("\nwriting %s....\n", fileName.c_str());
	FILE *fp = fopen (fileName.c_str(), "wb");
	fwrite((const char*)mapImage, 1, mapImage.size(), fp);
	fclose (fp);

	// Manage pointers so that only 1 collection deletes objects
	delete mqSession;

}

/**
 * convertMQResults2Info()
 * params: 
 *   routeResults: a CMQRouteResult object to be converted into a RouteInfo object
 * returns:
 *   RouteInfo object 
 **/
RouteInfo<double> RouteClient::convertMQResults2Info(CMQRouteResults routeResults)
{
	size_t numTreks = routeResults.TrekRoutes().GetSize();
	if (numTreks != routeLocations.size() - 1)
	{
		std::cerr<< "The number of treks did not match locations\n";
		std::cerr<< "There were " << numTreks << " treks but there were "
			<< routeLocations.size() << " locations\n";
	}

	CMQGeoAddress *orig;
	CMQLatLng latlng;
	RouteInfo<double> rInfo(routeResults);

	for (size_t rc = 0; rc < numTreks; rc ++)
	{
		CMQTrekRoute* tr = (CMQTrekRoute*) routeResults.TrekRoutes().GetAt(rc);
		double distance  = tr->GetDistance();
		double time      = tr->GetTime() / 60.0;

		orig = (CMQGeoAddress*) routeLocations.GetAt(rc); 
		latlng = orig->GetLatLng();

		Location<double>  pointLoc(latlng.GetLatitude(), latlng.GetLongitude() );
		PointInfo<double> point(pointLoc, distance, time);
		rInfo.addPointInfo(point);

	}
	// now add the last location with time and distance of 0.0
	orig = (CMQGeoAddress*) routeLocations.GetAt(numTreks); 
	latlng = orig->GetLatLng();

	Location<double>  pointLoc(latlng.GetLatitude(), latlng.GetLongitude() );
	PointInfo<double> point(pointLoc, 0.0, 0.0);
	rInfo.addPointInfo(point);

	return rInfo;
}

void RouteClient::setLocations(Locations locations)
{
	routeLocations.RemoveAll();
	for (size_t ii = 0; ii < locations.size(); ii++)
	{
		addLocation( locations[ii] );
	}
}

void RouteClient::setLocations(const RouteInfo<>& rInfo)
{
	routeLocations.RemoveAll();
	for (size_t ii = 0; ii < rInfo.size(); ii++)
	{
		addLocation( rInfo[ii].loc );
	}
}

void RouteClient::addLocation(Location<double> loc)
{
	CMQLatLng point;
	point.SetLatitude(loc.lat);
	point.SetLongitude(loc.lng);

	CMQGeoAddress* gaddr = new CMQGeoAddress();
	gaddr->SetLatLng(point);
	//std::cout<<"Adding location \t"
	//	<< point.GetLatitude() << " : " << point.GetLongitude() << std::endl;
	routeLocations.Add(gaddr);
}

} // end routes namespace
} // end controller namespace


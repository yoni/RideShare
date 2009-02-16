/******************************************************************************
This simple sample demonstrates how to route between two locations without
utilizing MapQuest's server side session management.  To utilize MapQuest's
server side session management, please view the routeItWithServerSession sample.

For a complete explanation of all objects and their functionality please refer
to the API documentation located in the mq\clients\c++\ directory or
http://support.mapquest.com.

NOTE: These samples are designed to work with sample data sets, so pool names
ports and server IPs may need to be modified for your use.
******************************************************************************/
#include <stdio.h>
#include "ifexec.h"
#include "mqservers.h"

#define originAddress "100 Penn St"
#define originCity "Pittsburgh"
#define originState "PA"
#define originZip ""
#define originCountry "US"

#define destAddress "2015 Saw Mill Run Blvd"
#define destCity "Pittsburgh"
#define destState "PA"
#define destZip ""
#define destCountry "US"

int main(int argc, char *argv[])
{
   // MapQuest.Exec is the MapQuest client object.
   // All server requests, such as Geocode and Search, are part of the Exec object.
   // Client.ServerName refers to the name of the server where the MapQuest server resides.
   // Client.ServerPath refers to the virtual directory where the MapQuest server resides.
   // Client.ServerPort refers to the port the client uses to communicate with the MapQuest
   CMQExec MapClient;
   MapClient.SetServerName(mqMapServerName);
   MapClient.SetServerPath(mqMapServerPath);
   MapClient.SetServerPort(mqMapServerPort);
   MapClient.SetClientId(mqMapServerClientId);
   MapClient.SetPassword(mqMapServerPassword);

   CMQExec GeocodeClient;
   GeocodeClient.SetServerName(mqGeocodeServerName);
   GeocodeClient.SetServerPath(mqGeocodeServerPath);
   GeocodeClient.SetServerPort(mqGeocodeServerPort);
   GeocodeClient.SetClientId(mqGeocodeServerClientId);
   GeocodeClient.SetPassword(mqGeocodeServerPassword);

   CMQExec RouteClient;
   RouteClient.SetServerName(mqRouteServerName);
   RouteClient.SetServerPath(mqRouteServerPath);
   RouteClient.SetServerPort(mqRouteServerPort);
   RouteClient.SetClientId(mqRouteServerClientId);
   RouteClient.SetPassword(mqRouteServerPassword);


   // Create Input Address
   CMQAddress Address;

   // Fill in origin information
   Address.Init();
   Address.SetStreet(originAddress);
   Address.SetCity(originCity);
   Address.SetState(originState);
   Address.SetPostalCode(originZip);
   Address.SetCountry(originCountry);

   // Create LocationCollection for results
   CMQLocationCollection lcOriginResults;

   // Geocode origin location
   try
   {
      GeocodeClient.Geocode(Address, lcOriginResults);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   CMQGeoAddress* gaOrigin = NULL;

   // If the results collection's Count property is zero, no matches could be found for the location
   if (lcOriginResults.GetSize() > 0)
   {
      gaOrigin = (CMQGeoAddress*)lcOriginResults.GetAt(0);
   }
   else
   {
      printf ("The origin could not be geocoded.\n");
      return 1;
   }

   // Fill in destination information
   Address.Init();
   Address.SetStreet(destAddress);
   Address.SetCity(destCity);
   Address.SetState(destState);
   Address.SetPostalCode(destZip);
   Address.SetCountry(destCountry);

   CMQLocationCollection lcDestResults;

   // Geocode destination location
   try
   {
      GeocodeClient.Geocode(Address, lcDestResults);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   CMQGeoAddress* gaDest = NULL;

   // If the results collection's Count property is zero, no matches could be found for the location
   if (lcDestResults.GetSize() > 0)
   {
      gaDest = (CMQGeoAddress*)lcDestResults.GetAt(0);
   }
   else
   {
      printf("Destination could not be geocoded.\n");
      return 1;
   }

   // This is the collection that will hold the geocoded locations to be utilized in the call to DoRoute.
   CMQLocationCollection lcRouteLocations;

   lcRouteLocations.Add(gaOrigin);
   lcRouteLocations.Add(gaDest);

   // Routes may be customized (i.e., shortest or fastest route, whether to avoid
   // toll roads or limited access highways, etc.).  In this sample the number of
   // shape points per maneuver is being set, which provides the detail of the
   // highlight to be drawn. In addition, the CoverageName is also being set, which
   // must match a configured route on the MapQuest server.

   // The RouteOptions object contains information pertaining to the Route to be performed.
   CMQRouteOptions routeOptions;

   routeOptions.SetMaxShapePointsPerManeuver(50);

   // The RouteResults object will contain the results of the DoRoute call.  The
   // results contains information such as the narrative, drive time and distance.
   CMQRouteResults routeResults;

   // This call to the server actually generates the route.
   try
   {
      RouteClient.DoRoute(lcRouteLocations, routeOptions, routeResults, NULL);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   // To see a demonstration of the error handling comment out the call to DoRoute
   if (routeResults.GetResultCode() != CMQRouteResultsCode::SUCCESS)
   {
      for (int i=0, iCount=routeResults.ResultMessages().GetSize(); i < iCount; i++)
      {
         printf("\n", (const char*)routeResults.ResultMessages().GetAt(i));
      }
      return 1;
   }

   // Create DisplayTypes and pointFeatures for the origin and destination locations
   // to be displayed.  For details regarding DisplayTypes and PointFeatures, see the
   // mapWithPoi sample.
   CMQDTStyle* originDTStyle = new CMQDTStyle;
   originDTStyle->SetDT(3073);
   originDTStyle->SetSymbolType(CMQSymbolType::RASTER);
   originDTStyle->SetSymbolName("MQ09191");
   originDTStyle->SetVisible(true);
   originDTStyle->SetLabelVisible(false);


   CMQDTStyle* destDTStyle = new CMQDTStyle;
   destDTStyle->SetDT(3074);
   destDTStyle->SetSymbolType(CMQSymbolType::RASTER);
   destDTStyle->SetSymbolName("MQ09192");
   destDTStyle->SetVisible(true);
   destDTStyle->SetLabelVisible(false);

   CMQCoverageStyle* coverageStyle = new CMQCoverageStyle;

   coverageStyle->Add(originDTStyle);
   coverageStyle->Add(destDTStyle);

   CMQPointFeature* ptfOrigin = new CMQPointFeature;
   ptfOrigin->SetDT(3073);
   ptfOrigin->SetCenterLatLng(gaOrigin->GetLatLng());

   CMQPointFeature* ptfDest = new CMQPointFeature;
   ptfDest->SetDT(3074);
   ptfDest->SetCenterLatLng(gaDest->GetLatLng());

   CMQFeatureCollection* fcRouteNodes = new CMQFeatureCollection;
   fcRouteNodes->Add(ptfOrigin);
   fcRouteNodes->Add(ptfDest);
   // End origin and destination point generation

   // Create the MapState object
   CMQMapState* MapState = new CMQMapState;
   MapState->SetWidthPixels(450);
   MapState->SetHeightPixels(300);

   // Create the Session object.
   CMQSession* mqSession = new CMQSession;
   mqSession->AddOne(MapState);
   mqSession->AddOne(fcRouteNodes);
   mqSession->AddOne(coverageStyle);

   // Create the routeHighlight to be displayed on the map using the LinePrimitive
   // object.  This object allows you to insert lines of your own creation into the map.
   CMQLinePrimitive* lpRtHlt = new CMQLinePrimitive;
   lpRtHlt->SetColor(CMQColorStyle::GREEN);
   lpRtHlt->SetKey("RouteShape");
   lpRtHlt->SetStyle(CMQPenStyle::SOLID);
   lpRtHlt->SetCoordinateType(CMQCoordinateType::GEOGRAPHIC);
   lpRtHlt->SetDrawTrigger(CMQDrawTrigger::AFTER_ROUTE_HIGHTLIGHT);
   lpRtHlt->SetWidth(200);

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
      MapClient.GetMapImageDirectEx(mqSession, mapImage);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }
   printf("\nwriting mapImage.gif....\n");
   FILE *fp = fopen ("mapImage.gif", "wb");
   fwrite((const char*)mapImage, 1, mapImage.size(), fp);
   fclose (fp);

   // Generate the route narrative.
   printf("\nRoute Narrative:\n\n");
   printf("Man #  Narrative                                                Distance   Time\n");

   // Each manuever object contains its own narrative, distance and drive time.
   int mc;
   for (mc=0; mc < routeResults.TrekRoutes().GetAt(0)->GetManeuvers().GetSize(); mc++)
   {
      CMQManeuver* man = (CMQManeuver*)routeResults.TrekRoutes().GetAt(0)->GetManeuvers().GetAt(mc);
      CMQString txtLine;
      txtLine.Format("  %.2d   %-54.54s    %.4f    %.2f\n",mc+1,(const char*)man->GetNarrative(),man->GetDistance(),(man->GetTime() / 60.0));
      printf("%s", (const char*)txtLine);
   }

   // Manage pointers so that only 1 collection deletes objects
   lcRouteLocations.RemoveAll();
   routeResults.GetShapePoints().RemoveAll();
   delete mqSession;

   return 0;
}



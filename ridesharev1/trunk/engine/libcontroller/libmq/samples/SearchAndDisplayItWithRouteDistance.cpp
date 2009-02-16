/*******************************************************************************
This simple sample demonstrates how to search for POIs, display those POIs on a
map, and compare arc distance vs. route distance.

For a complete explanation of all objects and their functionality please refer
to the API documentation located in the mq\clients\c++\ directory or
http://support.mapquest.com.

NOTE: These samples are designed to work with sample data sets, so pool names
ports and server IPs may need to be modified for your use.
*******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ifexec.h"
#include "mqservers.h"


int main(int argc, char *argv[])
{
   try
   {
      // This is a constant used to designate Gas Stations.
      // Our sample database denotes gas stations as having an Id of 3111
      const int GAS_STATIONS = 3111;

      // Search radius and max matches
      const double SEARCH_RADIUS      = 2.5;
      const int    SEARCH_MAX_MATCHES = 15;

      // Origin lat/lng
      CMQLatLng originLatLng(40.4445, -79.995399);

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

      CMQExec RouteClient;
      RouteClient.SetServerName(mqRouteServerName);
      RouteClient.SetServerPath(mqRouteServerPath);
      RouteClient.SetServerPort(mqRouteServerPort);
      RouteClient.SetClientId(mqRouteServerClientId);
      RouteClient.SetPassword(mqRouteServerPassword);

      CMQExec SpatialClient;
      SpatialClient.SetServerName(mqSpatialServerName);
      SpatialClient.SetServerPath(mqSpatialServerPath);
      SpatialClient.SetServerPort(mqSpatialServerPort);
      SpatialClient.SetClientId(mqSpatialServerClientId);
      SpatialClient.SetPassword(mqSpatialServerPassword);

      // The MapState object contains the information necessary to display the map,
      // such as size, scale, and latitude/longitude coordinates for centering the map.
      CMQMapState* MapState = new CMQMapState();

      // Define the width of the map in pixels.
      MapState->SetWidthPixels(420);

      // Define the height of the map in pixels.
      MapState->SetHeightPixels(262);

      // The MapScale property tells the server the scale at which to display the map.
      // Level of detail displayed varies depending on the scale of the map.
      MapState->SetMapScale(100000);

      // Specify the latitude/longitude coordinate to center the map.
      MapState->SetCenter(originLatLng);

      // The MapQuest Session object is composed of multiple objects,
      // such as the MapState and CoverageStyle.
      CMQSession* mqSession = new CMQSession();

      // A DTStyle object is an object that contains graphical information about a
      // point to display on the map.  This information includes, but is not limited to,
      // the symbol for a point, whether to label the point, and if so, the font to use.
      CMQDTStyle* OriginDTStyle = new CMQDTStyle();

      // For a PointFeature to use this DTStyle, the DT Property of the
      // PointFeature must equal the DT assigned to the DTStyle object.  Refer to the
      // API documentation for valid DT ranges of user-defined DTStyle objects.
      OriginDTStyle->SetDT(3150);

      // The SymbolType property defines whether the symbol for display is
      // a GRF (Image type i.e. Bitmap) file defined as mqRaster, or a GMF
      // (Vector data) file defined as mqVector = 1.
      // Utilities are provided with the distribution to create GRF or GMF files.
      // These symbols need to be stored on the MapQuest Server to be used.
      OriginDTStyle->SetSymbolType(CMQSymbolType::VECTOR);

      // The SymbolName property specifies the name of the particular symbol to display
      // when a PointFeature designates using this DTStyle to represent itself.
      // The symbol can be in GRF or GMF format.
      OriginDTStyle->SetSymbolName("MQ00031");

      // This property determines whether or not the symbol should be displayed with a text label.
      OriginDTStyle->SetLabelVisible(false);

      // This property determines whether or not a POI is to be displayed  on the map.
      // It may be useful to hold but not display a POI class
      // until particular time.
      OriginDTStyle->SetVisible(true);

      // A DTStyle object is an object that contains graphical information about a
      // point to display on the map.  This information includes, but is not limited to,
      // the symbol for a point, whether to label the point, and if so, the font to use.
      CMQDTStyle* GasStationDTStyle = new CMQDTStyle();

      // For a PointFeature to use this DTStyle, the DT Property of the
      // PointFeature must equal the DT assigned to the DTStyle object.  Refer to the
      // API documentation for valid DT ranges of user-defined DTStyle objects.
      GasStationDTStyle->SetDT(GAS_STATIONS);

      // The SymbolType property defines whether the symbol for display is
      // a GRF (Image type i.e. Bitmap) file defined as mqRaster, or a GMF
      // (Vector data) file defined as mqVector 1.
      // Utilities are provided with the distribution to create GRF or GMF files.
      // These symbols need to be stored on the MapQuest Server to be used.
      GasStationDTStyle->SetSymbolType(CMQSymbolType::RASTER);

      // The SymbolName property specifies the name of the particular symbol to display
      // when a PointFeature designates using this DTStyle to represent itself.
      // The symbol can be in GRF or GMF format.
      GasStationDTStyle->SetSymbolName("MQ00245");

      // This property determines whether or not the symbol should be displayed with a text label.
      GasStationDTStyle->SetLabelVisible(false);

      // This property determines whether or not a POI is to be displayed  on the map.
      // It may be useful to hold but not display a POI class
      // until particular time.
      GasStationDTStyle->SetVisible(true);

      // The CoverageStyle object contains user-defined DTStyle (Display Type) objects, which can
      // override default styles set in the style pool.
      CMQCoverageStyle* CoverageStyle = new CMQCoverageStyle();

      // This adds a DTStyle object to the CoverageStyle object.  The server will use this
      // to determine how to display the origin point.
      CoverageStyle->Add(OriginDTStyle);

      // This adds a DTStyle object to the CoverageStyle object.  The server will use this
      // to determine how to display the gas station locations.
      CoverageStyle->Add(GasStationDTStyle);

      // A PointFeature object contains information about where to display a
      // POI on a map, as well information about the particular point, such as the
      // distance from the center in a radius search.
      CMQPointFeature* OriginPoint = new CMQPointFeature();

      // This property must coincide with the DT of the DTStyle object we want to use
      // in determining the display characteristics of this PointFeature.
      OriginPoint->SetDT(3150);

      // The CenterLatLng object contains the latitude and longitude coordinate
      ///used to determine where to display the point on a map.
      // In this instance, we are displaying a point representing the center of our search area
      OriginPoint->SetCenterLatLng(originLatLng);

      // Create a DTCollection object.  In the Search method, the DTCollection is intended
      // to be used as the primary filter for retrieving objects whether retrieving them
      // from the mapping data, a user defined feature collection or a database.
      CMQDTCollection DTCollection;

      // Add the ID for gas stations to the DTCollection filter.
      DTCollection.Add(GAS_STATIONS);

      // A DBLayerQuery object uniquely specifies a database table to be used when drawing
      // maps or performing searches. It contains the information necessary to connect to a
      // table within an ODBC datasource. DBLayerQuery points to a DB layer that the
      // MapQuest server has been configured to use.
      CMQDBLayerQuery* DBLayerQuery = new CMQDBLayerQuery();

      // Name of the MapQuest server DBPool to use
      DBLayerQuery->SetDBLayerName("MQA.test");

      // DBLayerQueryCollection object is a collection of DBLayerQuery objects. Use
      // DBLayerQueryCollection objects to create maps with user-supplied features taken
      // from a number of different databases or tables
      CMQDBLayerQueryCollection DBLayerQueryCollection;

      // Add the query to the query collection.
      DBLayerQueryCollection.Add(DBLayerQuery);

      // A RadiusSearchCriteria object specifies the geographic search criteria for a radius search.
      CMQRadiusSearchCriteria RadiusSearchCriteria;

      // Latitude/Longitude of center point for search
      RadiusSearchCriteria.SetCenter(originLatLng);

      // This property specifies the maximum number of features MapQuest should return for the Search method
      RadiusSearchCriteria.SetMaxMatches(SEARCH_MAX_MATCHES);

      // This property specifies the radius of the circular area to be searched. For example,
      // if the radius is 2 miles, MapQuest searches for points within 2 miles of the point
      // described by the Center.Latitude and Center.Longitude properties
      RadiusSearchCriteria.SetRadius(SEARCH_RADIUS);

      // A FeatureCollection object holds a collection of feature objects, potentially
      // containing a mixture of different feature types.
      // This may be a user collection or results from a request such as search.
      CMQFeatureCollection* searchResults = new CMQFeatureCollection();

      // Generates a request to the MapQuest server (as specified by the server name, path, and
      // port number) to perform a search and return the results in a FeatureCollection object.
      // When performing a search against a database, the FeatureCollection will contain PointFeature
      // Objects exclusively.  If you attempt to search the mapping data, the FeatureCollection may
      // contain PointFeatures, LineFeatures, or PolygonFeatures.
      SpatialClient.Search(RadiusSearchCriteria, *searchResults, NULL, &DBLayerQueryCollection, NULL, &DTCollection);

      // Create route matrix location collection and add origin
      CMQGeoAddress* location;
      location = new CMQGeoAddress();
      location->SetLatLng(originLatLng);
      CMQLocationCollection* locations = new CMQLocationCollection();
      locations->Add(location);

      // Print label
      printf("\nGas stations within %.1f miles of origin. Max matches = %d\n", SEARCH_RADIUS, SEARCH_MAX_MATCHES);

      // Display arc distance results in a table
      // Also, populate locations to send to route matrix
      printf("\n>> Arc Distance Results ===================================\n");
      printf(">> Found %d Matches\n", searchResults->GetSize());
      printf("------+-------------------------------+-----------+--------\n");
      printf("Match  Name                            Key         Distance\n");
      printf("------+-------------------------------+-----------+--------\n");
      CMQPointFeature* PointFeature;
      for (int i = 0, n = searchResults->GetSize(); i < n; i++)
      {
         PointFeature = (CMQPointFeature*)searchResults->GetAt(i);
         CMQString txtLine;
         txtLine.Format("  %.2d   %-30.30s  %-10.10s    %.2f\n", i+1, (const char*)PointFeature->GetName(), (const char*)PointFeature->GetKey(), PointFeature->GetDistance());
         printf("%s", (const char*)txtLine);

         location = new CMQGeoAddress();
         location->SetLatLng(PointFeature->GetCenterLatLng());
         locations->Add(location);
      } // end for loop

      // The arc distance features
      CMQFeatureCollection* adFeatures = new CMQFeatureCollection();
      adFeatures->Append(*searchResults);

      // Add the Origin to the FeatureCollection that also contains the returned POIs
      // from the Search method.  Then, pass the FeatureCollection back to the server
      // so the map that is returned to the end user will contain the points.
      adFeatures->Add(OriginPoint);

      // Add objects to the session to be sent to the server.
      mqSession->AddOne(MapState);
      mqSession->AddOne(CoverageStyle);
      mqSession->AddOne(adFeatures);

      // This call generates the actual GIF image resulting from the given Session Object.
      CMQIOMem adMapImage;
      MapClient.GetMapImageDirectEx(mqSession, adMapImage);

      // Write arc distance GIF image to file
      printf("\nwriting adMapImage.gif....\n");
      FILE *fp = fopen ("adMapImage.gif", "wb");
      fwrite((const char*)adMapImage, 1, adMapImage.size(), fp);
      fclose (fp);

      // Calculate one to all route matrix
      CMQRouteMatrixResults routeMatrixResults;
      CMQRouteOptions routeOptions;
      RouteClient.DoRouteMatrix(*locations, false, routeOptions,
         routeMatrixResults);

      // Only keep points within search radius
      double distance;
      CMQFeatureCollection* rdFeatures = new CMQFeatureCollection();
      for (int j = 0, m = searchResults->GetSize(); j < m; j++)
      {
         PointFeature = (CMQPointFeature*)searchResults->GetAt(j);
         distance = routeMatrixResults.GetDistance(0, j+1);

         if (distance <= SEARCH_RADIUS)
         {
            PointFeature->SetDistance(distance);
            rdFeatures->Add(PointFeature);
         } // end if then

      } // end for loop

      // Display route distance results in a table
      printf("\n>> Route Distance Results =================================\n");
      printf(">> Found %d Matches\n", rdFeatures->GetSize());
      printf("------+-------------------------------+-----------+--------\n");
      printf("Match  Name                            Key         Distance\n");
      printf("------+-------------------------------+-----------+--------\n");
      for (int k = 0, p = rdFeatures->GetSize(); k < p; k++)
      {
         PointFeature = (CMQPointFeature*)rdFeatures->GetAt(k);
         CMQString txtLine;
         txtLine.Format("  %.2d   %-30.30s  %-10.10s    %.2f\n", k+1, (const char*)PointFeature->GetName(), (const char*)PointFeature->GetKey(), PointFeature->GetDistance());
         printf("%s", (const char*)txtLine);

      } // end for loop

      // Add the Origin to the FeatureCollection that also contains the returned POIs
      // from the Search method.  Then, pass the FeatureCollection back to the server
      // so the map that is returned to the end user will contain the points.
      rdFeatures->Add(OriginPoint);

      // Add objects to the session to be sent to the server.
      mqSession = new CMQSession();
      mqSession->AddOne(MapState);
      mqSession->AddOne(CoverageStyle);
      mqSession->AddOne(rdFeatures);

      // This call generates the actual GIF image resulting from the given Session Object.
      CMQIOMem rdMapImage;
      MapClient.GetMapImageDirectEx(mqSession, rdMapImage);

      // Write route distance GIF image to file
      printf("\nwriting rdMapImage.gif....\n");
      fp = fopen ("rdMapImage.gif", "wb");
      fwrite((const char*)rdMapImage, 1, rdMapImage.size(), fp);
      fclose (fp);

   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   return 0;
}


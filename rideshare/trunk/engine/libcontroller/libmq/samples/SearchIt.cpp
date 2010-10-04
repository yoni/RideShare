/*******************************************************************************
This simple sample demonstrates how to search for POIs.

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
   // This is a constant used to designate Gas Stations.
   // Our sample database denotes gas stations as having an Id of 3111
   const int GAS_STATIONS = 3111;

   // MapQuest.Exec is the MapQuest client object.
   // All server requests, such as Geocode and Search, are part of the Exec object.
   // Client.ServerName refers to the name of the server where the MapQuest server resides.
   // Client.ServerPath refers to the virtual directory where the MapQuest server resides.
   // Client.ServerPort refers to the port the client uses to communicate with the MapQuest
   CMQExec SpatialClient;
   SpatialClient.SetServerName(mqSpatialServerName);
   SpatialClient.SetServerPath(mqSpatialServerPath);
   SpatialClient.SetServerPort(mqSpatialServerPort);
   SpatialClient.SetClientId(mqSpatialServerClientId);
   SpatialClient.SetPassword(mqSpatialServerPassword);

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

   // Optional extra SQL query information? (used in conjunction with spatial search criteria).
   // Allows user to add further SQL restrictions on the results that would have been
   // returned. This SQL fragment will be appended to the WHERE clause with an "AND"
   // operator. This is to be used in conjunction with the DTCollection, not (usually)
   // in place of.  In this example, DT 3111, GAS_STATIONS signifies Gas Stations so this search
   // will find the 20 closest gas stations, that accept American Express, within 5 miles of our lat/lng.
   // Note:  If utilizing spatial IDs, the extraCriteria will be #AND#ed with each spatial ID being searched
   // for.  This allows for better indexing possibilities as you can generate spatialId_UserDefinedColumn1
   // index for quicker searching.
   DBLayerQuery->SetExtraCriteria("(Variable1 = '1')");

   // DBLayerQueryCollection object is a collection of DBLayerQuery objects. Use
   // DBLayerQueryCollection objects to create maps with user-supplied features taken
   // from a number of different databases or tables
   CMQDBLayerQueryCollection DBLayerQueryCollection;

   // Add the query to the query collection.
   DBLayerQueryCollection.Add(DBLayerQuery);

   // A RadiusSearchCriteria object specifies the geographic search criteria for a radius search.
   CMQRadiusSearchCriteria RadiusSearchCriteria;

   // Latitude/Longitude of center point for search
   RadiusSearchCriteria.SetCenter( CMQLatLng(40.4445, -79.995399) );

   // This property specifies the maximum number of features MapQuest should return for the Search method
   RadiusSearchCriteria.SetMaxMatches(20);

   // This property specifies the radius of the circular area to be searched. For example,
   // if the radius is 5 miles, MapQuest searches for points within 5 miles of the point
   // described by the Center.Latitude and Center.Longitude properties
   RadiusSearchCriteria.SetRadius(5);

   // Show all the parameters used in the radius search
   printf("\nRadius Search Parameters:\n");
   printf("Parameter Name    Value       Description\n");
   printf("Center.Latitude   %.4f     Latitude of center point for search.\n",RadiusSearchCriteria.GetCenter().GetLatitude());
   printf("Center.Longitude  %.4f    Longitude of center point for search.\n",RadiusSearchCriteria.GetCenter().GetLongitude());
   printf("MaxMatches        %d          Maximum number of features that will be returned.\n",RadiusSearchCriteria.GetMaxMatches());
   printf("Radius            %.2f        The radius of the circular area to be searched.\n\n",RadiusSearchCriteria.GetRadius());

   // Generates a request to the MapQuest server (as specified by the server name, path, and
   // port number) to perform a search and return the results in a FeatureCollection object.
   // When performing a search against a database, the FeatureCollection will contain PointFeature
   // Objects exclusively.  If you attempt to search the mapping data, the FeatureCollection may
   // contain PointFeatures, LineFeatures, or PolygonFeatures.

   // A FeatureCollection object holds a collection of feature objects, potentially
   // containing a mixture of different feature types.
   // This may be a user collection or results from a request such as search.
   CMQFeatureCollection SearchResults;

   try
   {
      SpatialClient.Search(RadiusSearchCriteria, SearchResults, NULL, &DBLayerQueryCollection, NULL, &DTCollection);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   // Display the results in a table
   printf("Radius Search Found %d Matches\n", SearchResults.GetSize());
   printf("Match  Name                            Key         Distance\n");

   // The POIs found get stored in the FeatureCollection named SearchResults. Loop
   // through the FeatureCollection to display the information pertaining to the POIs
   // found.  The key is tied to a unique ID in the database.  After a search is
   // performed, the key is used to requery the database through an external mechanism
   // (such as ADO) to retrieve extended information about the given record.

   int i;
   CMQPointFeature* PointFeature;
   for (i = 0; i < SearchResults.GetSize(); i++)
   {
      PointFeature = (CMQPointFeature*)SearchResults.GetAt(i);
      CMQString txtLine;
      txtLine.Format("  %.2d   %-30.30s  %-10.10s    %.2f\n", i+1, (const char*)PointFeature->GetName(), (const char*)PointFeature->GetKey(), PointFeature->GetDistance());
      printf("%s", (const char*)txtLine);
   }


   // Delete the Features from previous search
   SearchResults.DeleteAll();

   // A RectSearchCriteria object specifies the geographic search criteria for a rectangle search.
   CMQRectSearchCriteria RectSearchCriteria;

   // This property specifies the maximum number of features MapQuest should return for the Search method
   RectSearchCriteria.SetMaxMatches(20);

   // Set Latitude/Longitude of the upper left corner of the rectangular area to be searched.
   RectSearchCriteria.SetUpperLeft( CMQLatLng(40.517069, -80.089632) );

   // Set Latitude/Longitude of the lower right corner of the rectangular area to be searched.
   RectSearchCriteria.SetLowerRight( CMQLatLng(40.371931, -79.901166) );

   // Show all the parameters used in the rectangular search
   printf("\n\n");
   printf("Rectangular Search Parameters:\n");
   printf("Parameter Name       Value    Description\n");
   printf("UpperLeft.Latitude   %.4f  Latitude of Upper Left corner of search area.\n",RectSearchCriteria.GetUpperLeft().GetLatitude());
   printf("UpperLeft.Longitude  %.4f Longitude of Upper Left corner of search area.\n",RectSearchCriteria.GetUpperLeft().GetLongitude());
   printf("LowerRight.Latitude  %.4f  Latitude of Lower Right corner of search area.\n",RectSearchCriteria.GetLowerRight().GetLatitude());
   printf("LowerRight.Longitude %.4f Longitude of Lower Right corner of search area.\n",RectSearchCriteria.GetLowerRight().GetLongitude());
   printf("MaxMatches           %d       Maximum number of features that will be returned.\n\n",RectSearchCriteria.GetMaxMatches());

   // Generate a request to the MapQuest server to perform a search and return the
   // results in a FeatureCollection object.  When performing a search against a
   // database, the FeatureCollection will contain PointFeature objects exclusively.
   // If you attempt to search the mapping data, the FeatureCollection may
   // contain PointFeatures, LineFeatures, or PolygonFeatures.
   try
   {
      SpatialClient.Search(RectSearchCriteria, SearchResults, NULL, &DBLayerQueryCollection, NULL, &DTCollection);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   // Display the results in a table
   printf("Rectangular Search Found %d Matches\n", SearchResults.GetSize());
   printf("Match    Name                            Key\n");

   // The POIs found get stored in the FeatureCollection named SearchResults. Loop
   // through the FeatureCollection to display the information pertaining to the POIs
   // found.  The key is tied to a unique ID in the database.  After a search is
   // performed, the key is used to requery the database through an external mechanism
   // (such as ADO) to retrieve extended information about the given record.

   // Notice when performing a rectanglur search, distance is of no use.  This is
   // because a retangular search does not contain a point of reference where as
   // with the radius search a point of reference exists, the center point.

   for (i = 0; i < SearchResults.GetSize(); i++)
   {
      PointFeature = (CMQPointFeature*)SearchResults.GetAt(i);
      CMQString txtLine;
      txtLine.Format("  %.2d     %-30.30s  %-10.10s\n", i+1, (const char*)PointFeature->GetName(), (const char*)PointFeature->GetKey());
      printf("%s", (const char*)txtLine);
   }

   return 0;
}

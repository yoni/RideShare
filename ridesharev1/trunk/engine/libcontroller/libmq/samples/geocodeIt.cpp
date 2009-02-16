/*******************************************************************************
Simple sample to demonstrate how to geocode a location.

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
   // MapQuest.Exec is the MapQuest client object.
   // All server requests, such as Geocode and Search, are part of the Exec object.
   // Client.ServerName refers to the name of the server where the MapQuest server resides.
   // Client.ServerPath refers to the virtual directory where the MapQuest server resides.
   // Client.ServerPort refers to the port the client uses to communicate with the MapQuest
   CMQExec GeocodeClient;
   GeocodeClient.SetServerName(mqGeocodeServerName);
   GeocodeClient.SetServerPath(mqGeocodeServerPath);
   GeocodeClient.SetServerPort(mqGeocodeServerPort);
   GeocodeClient.SetClientId(mqGeocodeServerClientId);
   GeocodeClient.SetPassword(mqGeocodeServerPassword);


   // Create an Address object to contain the location to be geocoded.*/
   CMQAddress OriginAddress;

   // The GeocodeResults collection will contain the results of the geocode. A collection
   // is used so that multiple potential matches or ambiguities can be returned when an
   // exact match cannot be found.
   CMQLocationCollection GeocodeResults;

   // Remove the address number (100 from 100 Penn St) to see multiple matches or
   // ambiguities returned.
   // When geocoding an intersection, separate the streets with an @ symbol
   OriginAddress.SetStreet("100 Penn St");
   OriginAddress.SetCity("Pittsburgh");
   OriginAddress.SetState("Pa");
   OriginAddress.SetPostalCode("15215");
   OriginAddress.SetCountry("US");

   // This is the first communication with the MapQuest server.*/
   try
   {
      GeocodeClient.Geocode (OriginAddress, GeocodeResults);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   if (GeocodeResults.GetSize() == 0)
   {
      printf("ERROR - The address entered could not be geocoded.\n");
   }

   // Location geocoded, so display the match(es).*/
   else
   {
      printf("MapQuest found %i match(es) for the address:\n", GeocodeResults.GetSize());
      printf("%s\n", (const char *)OriginAddress.GetStreet());
      printf("%s,", (const char *)OriginAddress.GetCity());
      printf(" %s", (const char *)OriginAddress.GetState());
      printf("  %s\n\n", (const char *)OriginAddress.GetPostalCode());

      // Output all possible matches returned by the geocoder.
      // Each object in the collection is a potential match.
      // The LocationCollection (GeocodeResults) contains GeoAddress objects.
      // If an exact match is found, the collection will contain only one object.
      for (int i=0, iCount=GeocodeResults.GetSize(); i < iCount; i++)
      {
         CMQGeoAddress* GeoAddress = (CMQGeoAddress*)GeocodeResults.GetAt(i);
         printf("Match # %i\n", i+1);
         printf("\t%s\n", (const char *)GeoAddress->GetStreet());
         printf("\t%s\n", (const char *)GeoAddress->GetCity());
         printf("\t%s\n", (const char *)GeoAddress->GetCounty());
         printf("\t%s\n", (const char *)GeoAddress->GetState());
         printf("\t%s\n", (const char *)GeoAddress->GetCountry());
         printf("\t%s\n", (const char *)GeoAddress->GetPostalCode());
         printf("\t%.6f, ", GeoAddress->GetLatLng().GetLatitude());
         printf("%.6f\n", GeoAddress->GetLatLng().GetLongitude());
         printf("\t%s\n\n", (const char *)GeoAddress->GetResultCode());
      }
   }

   return 0;
}



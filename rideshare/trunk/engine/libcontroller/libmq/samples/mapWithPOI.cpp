/*******************************************************************************
Simple sample to demonstrate how to generate a maps with a POI using server
and client side sessions.

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
   CMQExec MapClient;
   MapClient.SetServerName(mqMapServerName);
   MapClient.SetServerPath(mqMapServerPath);
   MapClient.SetServerPort(mqMapServerPort);
   MapClient.SetClientId(mqMapServerClientId);
   MapClient.SetPassword(mqMapServerPassword);

   // The MapState object contains the information necessary to display the map,
   // such as size, scale, and latitude/longitude coordinates for centering the map.
   CMQMapState* MapState = new CMQMapState();

   // Define the width of the map in pixels.
   MapState->SetWidthPixels(392);

   // Define the height of the map in pixels.
   MapState->SetHeightPixels(245);

   // The MapScale property tells the server the scale at which to display the map.
   // Level of detail displayed varies depending on the scale of the map.
   MapState->SetMapScale(12000);

   // Specify the latitude/longitude coordinate to center the map.
   MapState->SetCenter(CMQLatLng(40.44569, -79.890393));

   // The FeatureCollection object contains Feature objects.  In this example,
   // a PointFeature is added to the collection.
   CMQFeatureCollection* FeatureCollection = new CMQFeatureCollection();

   // A PointFeature object contains information about where to display a
   // POI (Point of Interest) on a map, as well information about the point, such as the
   // distance from the center in a radius search.
   CMQPointFeature* PointFeature = new CMQPointFeature();

   // A DTStyle object is an object that contains graphical information about a
   // point to display on the map.  This information includes, but is not limited to,
   // the symbol for a point, whether to label the point, and if so, the font to use.
   CMQDTStyle* PointDTStyle = new CMQDTStyle();

   // For a PointFeature to use this DTStyle, the DT Property of the
   // PointFeature must equal the DT assigned to the DTStyle object.  Refer to the
   // API documentation for valid DT ranges of user-defined DTStyle objects.
   PointDTStyle->SetDT(3072);

   // The SymbolType property defines whether the symbol for display is
   // a GRF (Image type i.e. Bitmap) file defined as mqRaster, or a GMF
   // (Vector data) file defined as mqVector = 1.
   // Utilities are provided with the distribution to create GRF or GMF files.
   // These symbols need to be stored on the MapQuest Server to be used.
   PointDTStyle->SetSymbolType(CMQSymbolType::VECTOR);

   // The SymbolName property specifies the name of the particular symbol to display
   // when a PointFeature designates using this DTStyle to represent itself.
   // The symbol can be in GRF or GMF format.
   PointDTStyle->SetSymbolName("MQ00031");

   // This property determines whether or not the symbol should be displayed with a text label.
   PointDTStyle->SetLabelVisible(true);

   // This property determines whether or not a POI is to be displayed  on the map.
   // It may be useful to hold but not display a POI class
   // until particular time.
   PointDTStyle->SetVisible(true);

   // The FontStyle property defines the style of the font to use when displaying the
   // label. Refer to the API documentation for valid FontStyle values.
   // Multiple font styles may be used to form different types of label styles.
   // This example produces a boxed font.
   PointDTStyle->SetFontStyle(CMQFontStyle::BOXED);

   // When setting the FontStyle to boxed, a background color must also be defined.
   // The box will not display unless the background color is defined.
   PointDTStyle->SetFontBoxBkgdColor(CMQColorStyle::BLUE);

   // The CoverageStyle object contains user-defined DTStyle (Display Type) objects, which can
   // override default styles set in the style pool.
   CMQCoverageStyle* CoverageStyle = new CMQCoverageStyle();

   // This adds a DTStyle object to the CoverageStyle object.
   CoverageStyle->Add(PointDTStyle);

   // This property must coincide with the DT of the DTStyle object used
   // in determining the display characteristics of this PointFeature.
   PointFeature->SetDT(3072);

   // When a DTStyle object's LabelVisible property is set to true, the Name property
   // is displayed as the label.
   PointFeature->SetName("Hello");

   // The CenterLatLng object contains the latitude/longitude coordinate
   // used to determine where to display the point on a map.
   // In this example, a point is displayed at the center of the map.
   PointFeature->SetCenterLatLng(MapState->GetCenter());

   // This example adds a PointFeature to a FeatureCollection.  The Features in the
   // collection will be added to the map that is returned to the end user.
   FeatureCollection->Add(PointFeature);

   // The MapQuest Session object is composed of multiple objects,
   // such as the MapState and CoverageStyle.
   CMQSession* mqSession = new CMQSession();

   // Add objects to the session.
   mqSession->AddOne(MapState);
   mqSession->AddOne(FeatureCollection);
   mqSession->AddOne(CoverageStyle);

   // Process 1: Server side session

   // Create a new MapQuest session on the server.  This call the MapQuest server creates
   // and stores the MapQuest Session object on the MapQuest server.

   CMQString sessionId;
   try
   {
      sessionId = MapClient.CreateSessionEx(mqSession);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }

   // This call generates the actual GIF image resulting from the given Session Identifier.
   // It generates a GIF image based on the server information set earlier.
   CMQIOMem mapImage1;
   try
   {
      MapClient.GetMapImageFromSession(sessionId, mapImage1);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }
   printf("\nwriting mapImage1.gif....\n");
   FILE *fp = fopen ("mapImage1.gif", "wb");
   fwrite((const char*)mapImage1, 1, mapImage1.size(), fp);
   fclose (fp);

   // Process 2: Client side session or sessionless

   // This call generates the actual GIF image resulting from the given Session Object.
   CMQIOMem mapImage2;
   try
   {
      MapClient.GetMapImageDirectEx(mqSession, mapImage2);
   }
   catch (CMQException& e)
   {
      printf("CMQException:%s\n", (const char*)e.GetExceptionString());
      exit(-1);
   }
   printf("\nwriting mapImage2.gif....\n");
   fp = fopen ("mapImage2.gif", "wb");
   fwrite((const char*)mapImage2, 1, mapImage2.size(), fp);
   fclose (fp);

   // Calling delete on the Session object will call delete on all contained objects
   delete mqSession;

   return 0;
}



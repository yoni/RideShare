/*******************************************************************************
Simple sample to demonstrate how to generate a maps with drawing primitivies
included using server and client side sessions.

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
   // such as size, scale, and latitude/longitude coordinates for centering the map.*/
   CMQMapState* MapState = new CMQMapState();

   // Define the width of the map in pixels.
   MapState->SetWidthPixels(550);

   // Define the height of the map in pixels.
   MapState->SetHeightPixels(350);

   // The MapScale property tells the server the scale at which to display the map.
   // Level of detail displayed varies depending on the scale of the map.
   MapState->SetMapScale(12000);

   // Specify the latitude/longitude coordinate to center the map.
   MapState->SetCenter( CMQLatLng(40.44569, -79.890393) );

   // Create the collection to hold all the individual primitives.
   CMQPrimitiveCollection* Primitives = new CMQPrimitiveCollection();

   // Create one of each kind of primitive and save them to the server
   // so they get drawn on top of the next map.

   CMQEllipsePrimitive* EllipsePrimitive = new CMQEllipsePrimitive();
   EllipsePrimitive->SetColor(CMQColorStyle::GREEN);
   EllipsePrimitive->SetCoordinateType(CMQCoordinateType::GEOGRAPHIC);
   //EllipsePrimitive->SetFillColor(CMQColorStyle::YELLOW);
   //EllipsePrimitive->SetFillStyle(CMQFillStyle::DIAG_CROSS);
   EllipsePrimitive->SetWidth(70);
   EllipsePrimitive->GetUpperLeftPoint().SetXY(20, 20);
   EllipsePrimitive->GetLowerRightPoint().SetXY(150, 150);
   Primitives->Add(EllipsePrimitive);

   CMQLinePrimitive* LinePrimitive = new CMQLinePrimitive();
   LinePrimitive->SetColor(CMQColorStyle::ORANGE);
   LinePrimitive->SetWidth(140);
   LinePrimitive->GetPoints().AddXY(30, 30);
   LinePrimitive->GetPoints().AddXY(100, 100);
   LinePrimitive->GetPoints().AddXY(100, 150);
   LinePrimitive->GetPoints().AddXY(150, 150);
   Primitives->Add(LinePrimitive);

   CMQRectanglePrimitive* RectanglePrimitive = new CMQRectanglePrimitive();
   RectanglePrimitive->SetColor(CMQColorStyle::BLACK);
   RectanglePrimitive->SetCoordinateType(CMQCoordinateType::GEOGRAPHIC);
   RectanglePrimitive->SetWidth(70);
   //RectanglePrimitive->SetFillColor(CMQColorStyle::RED);
   RectanglePrimitive->SetFillStyle(CMQFillStyle::FDIAGONAL);
   RectanglePrimitive->GetUpperLeftPoint().SetXY(250, 20);
   RectanglePrimitive->GetLowerRightPoint().SetXY(400, 200);
   Primitives->Add(RectanglePrimitive);

   CMQTextPrimitive* TextPrimitive = new CMQTextPrimitive();
   TextPrimitive->SetColor(CMQColorStyle::RED);
   TextPrimitive->SetCoordinateType(CMQCoordinateType::DISPLAY);
   TextPrimitive->SetBkgdColor(CMQColorStyle::YELLOW);
   TextPrimitive->SetBoxOutlineColor(CMQColorStyle::BLUE);
   TextPrimitive->SetStyle(CMQFontStyle::BOXED);
   TextPrimitive->SetFontName("Helvetica");           // Unix Server
   //TextPrimitive->SetFontName("Arial"); // Windows Server
   TextPrimitive->SetFontSize(18);
   TextPrimitive->GetUpperLeftPoint().SetXY(250,250);
   TextPrimitive->SetWidth(50);
   TextPrimitive->SetText("Sample Text");
   Primitives->Add(TextPrimitive);

   CMQPolygonPrimitive* PolygonPrimitive = new CMQPolygonPrimitive();
   PolygonPrimitive->SetColor(CMQColorStyle::RED);
   PolygonPrimitive->SetCoordinateType(CMQCoordinateType::DISPLAY);
   PolygonPrimitive->SetFillColor(CMQColorStyle::BLUE);
   PolygonPrimitive->SetFillStyle(CMQFillStyle::SOLID);
   PolygonPrimitive->SetWidth(42);
   PolygonPrimitive->GetPoints().AddXY(50, 200);
   PolygonPrimitive->GetPoints().AddXY(50, 275);
   PolygonPrimitive->GetPoints().AddXY(150, 275);
   PolygonPrimitive->GetPoints().AddXY(150, 200);
   PolygonPrimitive->GetPoints().AddXY(100, 240);
   Primitives->Add(PolygonPrimitive);

   CMQSymbolPrimitive* SymbolPrimitive = new CMQSymbolPrimitive();
   SymbolPrimitive->SetCoordinateType(CMQCoordinateType::GEOGRAPHIC);
   SymbolPrimitive->GetCenterPoint().SetX(450);
   SymbolPrimitive->GetCenterPoint().SetY(250);
   SymbolPrimitive->SetName("MQ00033");
   SymbolPrimitive->SetSymbolType(CMQSymbolType::VECTOR);
   Primitives->Add(SymbolPrimitive);

   // The MapQuest Session object is composed of multiple objects,
   // such as the MapState and CoverageStyle.
   CMQSession* mqSession = new CMQSession();

   // Add objects to the session.
   mqSession->AddOne(MapState);
   mqSession->AddOne(Primitives);

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



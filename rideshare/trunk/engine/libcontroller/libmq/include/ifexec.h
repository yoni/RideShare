/*****************************************************************************
*  Copyright (C) 1992-2002 MapQuest.com/America Online/Time Warner, Inc.
*  All Rights Reserved.
*-----------------------------------------------------------------------------
*  This software is the confidential and proprietary information of
*  MapQuest.com and America Online ("Confidential Information"). You shall
*  not disclose such Confidential Information and shall use it only in
*  accordance with the terms of the license agreement you entered into with
*  MapQuest.com.
*-----------------------------------------------------------------------------
*  MAPQUEST.COM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
*  OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
*  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
*  PURPOSE, OR NON-INFRINGEMENT.  MAPQUEST.COM SHALL NOT BE LIABLE FOR ANY
*  DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
*  DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
*-----------------------------------------------------------------------------
*****************************************************************************/
#ifndef _IFEXEC_H_
// {secret}
#define _IFEXEC_H_

// MapQuest Includes
#include <mqosutil.h>
#include <mqif.h>

/**
 * MapQuest Client class.  This class provide all methods that communicate
 * with the MapQuest server.
 * @ingroup Mapquest
 */
class CMQExec
{
public:
   /**
    * Constructor
    */
   CMQExec();

   /**
    * Constructor
    *
    * @param szServerName        The name of the MapQuest Server which is to
    *                            be used to satisfy this request.
    * @param szServerPath        The path to the server which is to be used
    *                            to satisfy this request.
    * @param sServerPort         The port number of the server which is to be
    *                            used to satisfy this request.
    *                            (Optional.  Defaults to 80.)
    * @param szProxyServerName   The name of the proxy server to use or blank
    * @param sProxyServerPort    The port to access the proxy server by or 0
    */
   CMQExec( const char* szServerName,
            const char* szServerPath      = "",
            const unsigned short sServerPort       = 80,
            const char* szProxyServerName = "",
            const unsigned short sProxyServerPort  = 0);


   /**
    * Destructor
    */
   virtual ~CMQExec();

   /**
    * Uninitializes the Server name, path, and port number.
    */
   virtual void  Init();


   /**
    * Sets the name of the server which is to be used to satisfy this
    * request.
    *
    * The name of the server can be a domain name or an IP address.
    *
    * The name should not contain any leading or trailing slashes ("/").
    *
    * @param  szServerName  The name of the MapQuest Server which is to
    *                           be used to satisfy this request.
    */
   void SetServerName(const char* szServerName);

   /**
    * Returns the name of the server which will be used to satisfy this
    * request.
    *
    * @return The name of the server.
    */
   const CMQString& GetServerName() const;

   /**
    * Sets the path to mqserver.dll on the server.
    *
    * A trailing slash ("/") on the string is optional.
    *
    * Example: "mq/"
    *
    * @param szServerName    The path to the server which is to be used
    *                           to satisfy this request.
    */
   void SetServerPath(const char* szServerName);

   /**
    * Returns the path to the server which will be used to satisfy this
    * request.
    *
    * @return  The path to the server
    */
   const CMQString& GetServerPath() const;

   /**
    * Sets the port number to the server which is to be used to satisfy this
    * request.
    *
    * @param  sServerPort      The port number of the server which is to be
    *                    used to satisfy this request (typically 80).
    */
   void SetServerPort(unsigned short sServerPort = 80);

   /**
    * Returns the port number on the server which will be used to satisfy
    * this request.
    *
    * @return    The port number.
    */
   unsigned short GetServerPort() const;

   /**
    * Sets the socket timeout for read operations to be used when communicating
    * with the server
    *
    * @param  lTimeout      The timeout in seconds (Default = 0) wait indefinitely.
    */
   void SetSocketTimeout(long lTimeout);

   /**
    * Returns the socket timeout for read operations to be used when communicating
    * with the server
    *
    * @return    The Timeout in seconds.
    */
   long GetSocketTimeout() const;

   /**
    * Sets the encryption type to be used while transmitting data
    *
    * @param  lEncryptionType  The type of encryption to be used.
    *  No encryption is used if this property is not set.
    */
   void SetEncryption(const long lEncryptionType);

   /**
    * Returns the encryption type to be used while transmitting data
    *
    * @return    The type of encryption being used.
    */
   long GetEncryption() const;

   /**
    * Sets the name the id of the Client making the requests for Authentication.
    *
    * @param  szClientId  the ClientId
    */
   void SetClientId(const char* szClientId);

   /**
    * Returns   the ClientId established to make server requests with.
    *
    * @return   the ClientId
    */
   const CMQString& GetClientId() const;

   /**
    * Sets the password which is to be used with the Client Id by the server for
    * Authentication of this request.
    *
    * @param szPassword The password.
    */
   void SetPassword(const char* szPassword);
   /**
    * Gets the password which is to be used with the Client Id by the server for
    * Authentication of this request.
    */
    const CMQString& GetPassword() const;

   /**
    * Sets string data to be passed to the server to be logged with any subsequent requests
    * in the transaction log.
    *
    * @param  szXInfo  Transaction Info
    */
   void SetTransactionInfo(const char* szXInfo);

   /**
    * Gets string data to be passed to the server to be logged with any subsequent requests
    * in the transaction log.
    *
    * @return   Transaction Info
    */
   const CMQString& GetTransactionInfo() const;

   /**
    * This is a flag for printing text
    * messages to the console. These text messages echo the HTTP
    * communications between the client library and the server. The
    * messages are mainly used for debugging. Messages which indicate
    * an error are still printed to the console.
    * @return   The Verbose Console Output state.
    */
   bool GetVerboseConsoleOutput()
   {
      return m_bVerboseConsoleOutput;
   }

   /**
    * This is a flag for printing text
    * messages to the console. These text messages echo the HTTP
    * communications between the client library and the server. The
    * messages are mainly used for debugging. Messages which indicate
    * an error are still printed to the console.
    * @param bVal The new Verbose Console Output state.
    */
   void SetVerboseConsoleOutput(bool bVal)
   {
      m_bVerboseConsoleOutput = bVal;
   }

///////////////////////////////////////////////////////////
// Proxy methods

   /**
    * Sets the name or IP  of the proxy server to connect to.
    *
    * The name should not contain any leading or trailing slashes ("/").
    *
    * @param  szServerName  The name of the proxy server.
    */
   void SetProxyServerName(const char* szServerName);
   /**
    * Returns the name or IP  of the proxy server to connect to.
    *
    * @return The name of the proxy server.
    */
   const CMQString& GetProxyServerName() const;

   /**
    * Sets the port to connect to the proxy server with.
    *
    * @param  sServerPort      The proxy server port number
    */
   void SetProxyServerPort(unsigned short sServerPort);
   /**
    * Returns the port number to connect to the proxy server with.
    *
    * @return    The proxy server port number.
    */
   unsigned short GetProxyServerPort() const;

   /**
    * Sets the user name to connect to the proxy server with.
    *
    * @param  szUser  The user name to connect to the proxy server with.
    */
   void SetProxyServerUser(const char* szUser);
   /**
    * Returns the user name to connect to the proxy server with.
    *
    * @return The user name to connect to the proxy server with.
    */
   const CMQString& GetProxyServerUser() const;

   /**
    * Sets the password to connect to the proxy server with.
    *
    * @param  szPassword  The password to connect to the proxy server with.
    */
   void SetProxyServerPassword(const char* szPassword);
   /**
    * Returns The password to connect to the proxy server with.
    *
    * @return The password to connect to the proxy server with.
    */
   const CMQString& GetProxyServerPassword() const;

///////////////////////////////////////////////////////////


   /**
    * Returns the URL string which will generate a map image from
    * specified parameters when used.
    *
    * @param pMapState A MapState object.
    * @param pCovStyle A CoverageStyle object specifying custom styles.
    * @param pDBLayers A DBLayerQueryCollection object for displaying points from a database.
    * @param pFeatures A FeatureCollection of points to display on the map.
    * @param pMapCommand A MapCommand such as CMQBestFit to perform when creating the map image.
    * @param pDisplayState  (optional) DisplayState to use generate the image
    *
    * @return The URL string
    */
   CMQString      GetMapDirectURL(CMQMapState *pMapState = NULL,
                                  CMQCoverageStyle *pCovStyle = NULL,
                                  CMQDBLayerQueryCollection *pDBLayers = NULL,
                                  CMQFeatureCollection *pFeatures = NULL,
                                  CMQMapCommand *pMapCommand = NULL,
                                  CMQDisplayState *pDisplayState = NULL);

   /**
    * Returns the URL string which will generate a map image from
    * specified parameters when used.
    *
    * @param pSession  A Session Object
    * @param pDisplayState  (optional) DisplayState to use generate the image
    *
    * @return The URL string
    */
   CMQString      GetMapDirectURLEx(CMQSession* pSession,
                                    CMQDisplayState *pDisplayState = NULL);

   /**
    * Returns the URL string which will generate a map image from
    * specified parameters stored in a MapQuest session given the session id
    *
    * @param  strSessionUID  The Session's unique identifier.
    * @param pDisplayState  (optional) DisplayState to use generate the image
    *
    * @return The URL string
    */
   CMQString      GetMapFromSessionURL(const CMQString& strSessionUID, CMQDisplayState *pDisplayState = NULL);

   /**
    * Returns the URL string which specifies the server coverage information
    *
    * @param type    Type of info to return, Default is 0.  0=CoverageInfo, 1=DataSelectorInfo
    * @return        The URL string which specifies the server coverage information
    */
   CMQString      GetServerInfoURL(long type = 0);

   // End of methods not requiring access to server


   // Methods requiring access to server

   /**
    * Creates a MapQuest session on the MapQuest server.
    * The session is assigned a unique identifier which is used to
    * access and update the Session information.
    *
    * @param pInMapState  The map state object to store in the session
    * @param pNewMapState (Out) The map state that was stored in the session
    * @param pCovStyle    The coverage style to store in the session
    * @param pDBLayers    The database layer query collection to store in the session
    * @param pFeatures    The feature collection to store in the session
    *
    * @return  The unique Session identifier.
    */
   CMQString      CreateSession(CMQMapState *pInMapState = NULL,
                                CMQMapState *pNewMapState = NULL,
                                CMQCoverageStyle *pCovStyle = NULL,
                                CMQDBLayerQueryCollection *pDBLayers = NULL,
                                CMQFeatureCollection *pFeatures = NULL);

   /**
    * Creates a MapQuest session on the MapQuest server.
    * The session is assigned a unique identifier which is used to
    * access and update the Session information.
    *
    * @param pSession     A Session Object
    *
    * @return  The unique Session identifier.
    */
   CMQString      CreateSessionEx(CMQSession* pSession = NULL);

   /**
    * Returns the map state, coverage style, database layer query
    * collection, and feature collection objects that are stored in a
    * MapQuest session object from the MapQuest server Specified by the
    * session id.
    *
    * @param strSessionUID The unique identifier for the Session
    * @param ppMapState The object into which the values will be placed
    * @param ppCovStyle The object into which the values will be placed
    * @param ppDBLayers The object into which the values will be placed
    * @param ppFeatures The object into which the values will be placed
    * @param ppPrimitives The object into which the values will be placed
    */
   void           GetSession(const CMQString& strSessionUID,
                             CMQMapState** ppMapState = NULL,
                             CMQCoverageStyle** ppCovStyle = NULL,
                             CMQDBLayerQueryCollection** ppDBLayers = NULL,
                             CMQFeatureCollection** ppFeatures = NULL,
                             CMQPrimitiveCollection** ppPrimitives = NULL);

   /**
    * Retrieves the MapQuest session object from the MapQuest server Specified by the
    * session id.
    *
    * @param strSessionUID The unique identifier for the Session
    * @param ppSession  A Session Object
    */
   void           GetSessionEx(const CMQString& strSessionUID,
                               CMQSession** ppSession);

   /**
    * Updates the information in a specified session on the server
    *
    * @param strSessionUID The unique identifier for the Session
    * @param pMapState A new MapState
    * @param pCovStyle A new CoverageStyle
    * @param pDBLayers A new DBLayerQueryCollection
    * @param pFeatures A new FeatureCollection
    * @param pPrimitives A new PrimitiveCollection
    */
   void           UpdateSession(const CMQString strSessionUID,
                                CMQMapState *pMapState = NULL,
                                CMQCoverageStyle *pCovStyle = NULL,
                                CMQDBLayerQueryCollection *pDBLayers = NULL,
                                CMQFeatureCollection *pFeatures = NULL,
                                CMQPrimitiveCollection *pPrimitives = NULL);

   /**
    * Updates the information in a specified session on the server
    *
    * @param strSessionUID The unique identifier for the Session
    * @param pSession  A Session Object
    */
   void           UpdateSessionEx(const CMQString& strSessionUID,
                                  CMQSession* pSession);

   /**
    * Updates the information in a specified session object and returns a session
    * with the updates without saving on server.
    *
    * @param pSession  A Session Object
    * @param pDisplayState  DisplayState to use to process any pixel/LatLng coordinates
    */
   void           UpdateSessionDirect(CMQSession* pSession,
                                      CMQDisplayState *pDisplayState = NULL);


   /**
    * Removes the specified MapQuest session from the MapQuest server.
    *
    * @param strSessionUID The unique identifier for the Session
    */
   void           DeleteSession(const CMQString strSessionUID);


   /**
    * Finds the location of an address/intersection.
    *
    * @param Location Address object to be geocoded
    *
    * @param GeocodeResults A LocationCollection which will hold the
    * results of the Geocode.  It will contain only GeoAddress objects.
    *
    * @param GeocodeOptions  (optional) Either a GeocodeOptionsCollection that
    * specifies the GeocodeOptions or rules to be used in turn or an
    * AutoGeocodeCovSwitch object to select a set of options stored on the
    * server. Leaving this parameter blank will use the default
    * AutoGeocodeCovSwitch object defined on the server.
    *
    */
   void           Geocode( CMQLocation& Location,
                           CMQLocationCollection& GeocodeResults,
                           CMQObject* GeocodeOptions = NULL );

   /**
    * Finds the location of an address/intersection.
    *
    * @param Locations A LocationCollection object filled with Address objects to be geocoded
    *
    * @param GeocodeResults A LocationCollectionCollection which will hold a LocationCollection
    * of results for each Address geocoded.  Each collection will contain only GeoAddress objects.
    *
    * @param GeocodeOptions  (optional) Either a GeocodeOptionsCollection that
    * specifies the GeocodeOptions or rules to be used in turn or an
    * AutoGeocodeCovSwitch object to select a set of options stored on the
    * server. Leaving this parameter blank will use the default
    * AutoGeocodeCovSwitch object defined on the server.
    *
    */
   void      BatchGeocode( CMQLocationCollection& Locations,
                           CMQLocationCollectionCollection& GeocodeResults,
                           CMQObject* GeocodeOptions = NULL );

   /**
    * Find the address at a given latitude/longitude position.
    *
    * @param llOrigin The latitude/longitude position to use for the reverse geocode.
    *
    * @param GeocodeResults A LocationCollection in which to return the
    * results of the reverse geocode.  It will contain only GeoAddress objects.
    *
    * @param lpszMapCovName The name of the mapping coverage to be used for the reverse geocode.
    *
    * @param lpszGeocodeCovName  An optional parameter, specifies the geocode coverage to use
    * for the reverse geocode. If specified, using this geocode coverage, a ZIP code lookup will
    * be performed on the addresses found in the mapping data to verify and fill in the city/state
    * information for the address.  If not specified, only ZIP code and, if available, street
    * information found in the mapping data will be returned.
    *
    * @see Geocode
    */
   void           ReverseGeocode(CMQLatLng& llOrigin,
                                 CMQLocationCollection& GeocodeResults,
                                 const char* lpszMapCovName,
                                 const char* lpszGeocodeCovName = NULL);
   /**
    * Searches for features in a map coverage.
    *
    * @param SearchCriteria Spatial parameters for the search
    *
    * @param SearchResults Search results.
    *
    * @param pszCoverageName The name of the map data coverage if
    * searching for features in the map data.
    *
    * @param pDBLayers Database parameters for the search.
    *
    * @param pFeatures A FeatureCollection to also be searched based on
    * the spatial criteria.
    *
    * @param pDisplayTypes A DTCollection to narrow the search. Only
    * those features with display types corresponding to those in this
    * collection will be returned.
    *
    * @see IdentifyFeature
    */
   void           Search(CMQSearchCriteria& SearchCriteria,
                         CMQFeatureCollection& SearchResults,
                         const char *pszCoverageName = NULL,
                         CMQDBLayerQueryCollection *pDBLayers = NULL,
                         CMQFeatureCollection *pFeatures = NULL,
                         CMQDTCollection *pDisplayTypes = NULL);


   /**
    * Searches for features that are displayed on a map for the given
    * Session Id.
    *
    * @param strSessionUID The unique identifier for the Session.
    *
    * @param IdentifyCriteria An IdentifyCriteria object specifying
    * the search criteria.
    *
    * @param IdentifyResults A FeatureCollection to contain the
    * results.
    *
    * @param pDisplayTypes A DTCollection identifying display types
    * for which to search. To preserve backwards compatibility, if
    * this parameter is null, then only point features in the
    * FeatureCollection and database layers are identified.
    *
    * @see Search
    */
   void           IdentifyFeature(const CMQString& strSessionUID,
                                  CMQIdentifyCriteria& IdentifyCriteria,
                                  CMQFeatureCollection& IdentifyResults,
                                  CMQDTCollection *pDisplayTypes = NULL);

   /**
    * Returns the GEF Id of the closest road segment. This GEF Id
    * can then be used as a routing origin, midpoint, or destination
    *
    * @param strSessionUID The unique Session ID
    * @param x The x coordinate within the current MapState
    * @param y The y coordinate within the current MapState
    * @param DTColl Collection of display types to search for closet segment within
    *
    * @return nReturnValue The GEF Id of the closest road
    *
    * @see IdentifyFeature
    */
   long          GetRoadGefIdXY(const CMQString& strSessionUID,
                         short x,
                         short y,
                         CMQDTCollection *DTColl = NULL);

   /**
    * Returns the GEF Id of the closest road segment. This GEF Id
    * can then be used as a routing origin, midpoint, or destination
    *
    * @param szCoverageName The Coverage for the map
    * @param lat Latitude
    * @param lng Longitude
    * @param DTColl Collection of display types to search for closet segment within
    *
    * @return The GEF Id of the closest road
    *
    * @see Search
    */
   long          GetRoadGefIdLL(CMQString &szCoverageName,
                         double lat,
                         double lng,
                         CMQDTCollection *DTColl = NULL);


   /**
    * Returns a collection of the point features that were displayed on the most
    * recent map draw for the given session id.
    *
    * @param strSessionUID    A String specifying the unique ID of the Session
    *
    * @param DrawnFeatures    A FeatureCollection to hold the results
    */
   void           GetDrawnFeatures(const CMQString& strSessionUID,
                                   CMQFeatureCollection& DrawnFeatures);

  /**
   * Centers the map by updating the map center point in the session.
   *
   * @param strSessionUID The session id
   *
   * @param nMouseX The x coordinate on which to center
   *
   * @param nMouseY The y coordinate on which to center
   *
   * @param pMapState Specifies a map state to be applied to the session
   * before the centering is completed.
   *
   * @param pNewMapState A copy of the new map state after the centering
   * operation has completed
   */
   void           CenterXY(const CMQString& strSessionUID,
                         int nMouseX, int nMouseY,
                         CMQMapState *pMapState = NULL,
                         CMQMapState *pNewMapState = NULL);
   /**
    * Centers the map by updating the map center point in the session.
    *
    * @param strSessionUID The session id
    *
    * @param dLat A double specifying the latitude on which to center
    *
    * @param dLng A double specifying the longitude on which to center
    *
    * @param pMapState Specifies a map state to be applied to the session
    * before the centering is completed.
    *
    * @param pNewMapState A copy of the new map state after the centering
    * operation has completed
    */
   void           CenterLL(const CMQString& strSessionUID,
                         double dLat, double dLng,
                         CMQMapState *pMapState = NULL,
                         CMQMapState *pNewMapState = NULL);
   /**
    * Zooms-in the map by updating the map scale in the session.
    *
    * @param strSessionUID The session id
    *
    * @param pMapState Specifies a map state to be applied to the session
    * before the zoom-in operation is completed.
    *
    * @param pNewMapState A copy of the new map state after the zoom-in
    * operation has completed
    */
   void           ZoomIn(const CMQString& strSessionUID,
                         CMQMapState *pMapState = NULL,
                         CMQMapState *pNewMapState = NULL);

   /**
    * Zooms-in and centers the map by updating the map scale in the session.
    *
    * @param strSessionUID The session id
    *
    * @param nMouseX The x coordinate on which to zoom in
    *
    * @param nMouseY The y coordinate on which to zoom in
    *
    * @param pMapState Specifies a map state to be applied to the session
    * before the zoom-in operation is completed.
    *
    * @param pNewMapState A copy of the new map state after the zoom-in
    * operation has completed
    */
   void           ZoomInXY(const CMQString& strSessionUID,
                         int nMouseX, int nMouseY,
                         CMQMapState *pMapState = NULL,
                         CMQMapState *pNewMapState = NULL);

   /**
    * Zooms-out the map by updating the map scale in the session.
    *
    * @param strSessionUID The session id
    *
    * @param pMapState Specifies a map state to be applied to the session
    * before the zoom-out operation is completed.
    *
    * @param pNewMapState A copy of the new map state after the zoom-out
    * operation has completed
    */
   void           ZoomOut(const CMQString& strSessionUID,
                          CMQMapState *pMapState = NULL,
                          CMQMapState *pNewMapState = NULL);
   /**
    * Zooms-out and centers the map by updating the map scale in the session.
    *
    * @param strSessionUID The session id
    *
    * @param nMouseX The x coordinate on which to zoom out
    *
    * @param nMouseY The y coordinate on which to zoom out
    *
    * @param pMapState Specifies a map state to be applied to the session
    * before the zoom-out operation is completed.
    *
    * @param pNewMapState A copy of the new map state after the zoom-out
    * operation has completed
    */
   void           ZoomOutXY(const CMQString& strSessionUID,
                          int nMouseX, int nMouseY,
                          CMQMapState *pMapState = NULL,
                          CMQMapState *pNewMapState = NULL);

  /**
   * Centers the map on the given rectangle by updating the map scale
   * and center point in the session.
   *
   * @param strSessionUID The session id
   *
   * @param nOriginX The x coordinate of the desired
   * upper left of the map
   *
   * @param nOriginY The y coordinate of the desired
   * upper left of the map
   *
   * @param nHeightPix The y offset from the
   * upper left to be used as the desired y coordinate of the
   * lower right of the map
   *
   * @param nWidthPix The x offset from the
   * upper left to be used as the desired x coordinate of the
   * lower right of the map
   *
   * @param pMapState Specifies a map state to be applied to the session
   * before the zoom-to-rectangle operation is completed.
   *
   * @param pNewMapState A copy of the new map state after the zoom-to-rectangle
   * operation has completed
   */
   void           ZoomToRectangleXY(const CMQString& strSessionUID,
                                  int nOriginX, int nOriginY,
                                  int nHeightPix, int nWidthPix,
                                  CMQMapState *pMapState = NULL,
                                  CMQMapState *pNewMapState = NULL);
  /**
   * Centers the map on the given rectangle by updating the map scale
   * and center point in the session.
   *
   * @param strSessionUID The session id
   *
   * @param dULLat Latitude of the desired upper left of the map
   *
   * @param dULLng Longitude of the desired upper left of the map
   *
   * @param dLRLat Latitude of the desired lower right of the map
   *
   * @param dLRLng Longitude of the desired lower right of the map
   *
   * @param pMapState Specifies a map state to be applied to the session
   * before the zoom-to-rectangle operation is completed.
   *
   * @param pNewMapState A copy of the new map state after the zoom-to-rectangle
   * operation has completed
   */
   void           ZoomToRectangleLL(const CMQString& strSessionUID,
                                  double dULLat, double dULLng,
                                  double dLRLat, double dLRLng,
                                  CMQMapState *pMapState = NULL,
                                  CMQMapState *pNewMapState = NULL);
   /**
    * Pans the map image by the desired x and y coordinates by updating the
    * map center point in the session
    *
    * @param strSessionUID The session id
    *
    * @param nDeltaX  The number of pixels that the map viewport is to be moved
    *                 in the horizontal direction.  Negative indicates movement
    *                 to the left, positive to the right.
    *
    * @param nDeltaY  The number of pixels that the map viewport is to be moved
    *                 in the vertical direction.  Negative indicates movement
    *                 upward, positive downward.
    *
    * @param pMapState Specifies a map state to be applied to the session
    * before the pan operation is completed.
    *
    * @param pNewMapState A copy of the new map state after the pan
    * operation has completed
    */
   void           Pan(const CMQString& strSessionUID, int nDeltaX, int nDeltaY,
                      CMQMapState *pMapState = NULL,
                      CMQMapState *pNewMapState = NULL);

  /**
   * Centers the map on the specified points by updating the map scale and center point in the session.
   *
   * @param strSessionUID    The session id
   *
   * @param pDBLayers        A DBLayerQueryCollection containing DBLayerQuery objects to
   *                         specify any database points that are to be included in the BestFit
   *
   * @param pFeatures        A FeatureCollection containing PointFeature objects to be
   *                         included in the BestFit
   *
   * @param pDisplayTypes    A DTCollection containing display types to narrow the features used
   *                         in determining the BestFit. Only those features in the FeatureCollection
   *                         or returned from the database whose display type is found in this
   *                         collection will be used in determining the BestFit.
   *
   * @param pMapState        The map state to be applied to the session before the operation is completed.
   *
   * @param pNewMapState     A copy of the map state after the operation has been completed.
   */
   void           BestFit(const CMQString& strSessionUID,
                          CMQDBLayerQueryCollection *pDBLayers = NULL,
                          CMQFeatureCollection *pFeatures = NULL,
                          CMQDTCollection* pDisplayTypes = NULL,
                          CMQMapState *pMapState = NULL,
                          CMQMapState *pNewMapState = NULL);

   /**
    * Converts x/y coordinates to Latitude/Longitude coordinates.
    *
    * @param Point            Point of to be converted
    *
    * @param LL               LatLng of converted Point
    *
    * @param MapState         MapState object specifying the current map data
    *                         coverage and specifications
    *
    * @param DisplayState     DisplayState containing DPI used for calculating
    *                         Pixel values.
    */
   void          PixToLL(  const CMQPoint& Point,
                                 CMQLatLng& LL,
                           const CMQMapState& MapState,
                           const CMQDisplayState& DisplayState);

   /**
    * Converts x/y coordinates to Latitude/Longitude coordinates.
    *
    * @param Points           PointCollection to be converted
    *
    * @param LLs              LatLngCollection of converted Points
    *
    * @param MapState         MapState object specifying the current map data
    *                         coverage and specifications
    *
    * @param DisplayState     DisplayState containing DPI used for calculating
    *                         Pixel values.
    */
   void          PixToLL(  const CMQPointCollection& Points,
                                 CMQLatLngCollection& LLs,
                           const CMQMapState& MapState,
                           const CMQDisplayState& DisplayState);

   /**
    * Converts Latitude/Longitude coordinates to x/y coordinates.
    *
    * @param LL               LatLng to be converted
    *
    * @param Point            Point of converted LatLng
    *
    * @param MapState         MapState object specifying the current map data
    *                         coverage and specifications
    *
    * @param DisplayState     DisplayState containing DPI used for calculating
    *                         Pixel values.
    */
   void          LLToPix(  const CMQLatLng& LL,
                                 CMQPoint& Point,
                           const CMQMapState& MapState,
                           const CMQDisplayState& DisplayState);

   /**
    * Converts Latitude/Longitude coordinates to x/y coordinates.
    *
    * @param LLs              LatLngCollection to be converted
    *
    * @param Points           PointCollection of converted LatLngs
    *
    * @param MapState         MapState object specifying the current map data
    *                         coverage and specifications
    *
    * @param DisplayState     DisplayState containing DPI used for calculating
    *                         Pixel values.
    */
   void          LLToPix(  const CMQLatLngCollection& LLs,
                                 CMQPointCollection& Points,
                           const CMQMapState& MapState,
                           const CMQDisplayState& DisplayState);

   /**
    * Calculates a route, returns the route shape points and narrative, and optionally
    * adds the route shape points to a session for automatic route highlight display.
    *
    * @param Locations Collection of location objects. The first member of the
    * collection is the origin, the last member is the destination, and
    * all other members are midpoints.  Each location must be a GeoAddress
    *
    * @param RouteOptions Specifies options for the route (fastest vs. shortest, coverage
    * to use, roads to avoid, etc.).
    *
    * @param RouteResults Contains the route narrative and shape points, as specified
    * in RouteOptions
    *
    * @param szSessionID (optional) specifies a session in which to store the shape points
    * for the route.  The route highlight will automatically appear on any maps
    * subsequently generated from this session.
    *
    * To remove route shape points from a session, see DeleteRoute.
    *
    * If the session id is an empty string, the route shape points will not automatically
    * appear on a map.
    *
    * @see DeleteRoute
    */
   void           DoRoute(const CMQLocationCollection&   Locations,
                          const CMQRouteOptions&         RouteOptions,
                          CMQRouteResults&               RouteResults,
                          const char*                    szSessionID = NULL);

   /**
    * Calculates a route matrix. Either a drive time (many-to-many) or a
    * multi-destination (one-to-many) route.
    *
    * @param   Locations   Collection of location objects. The first member
    *              of the collection is the origin. If allToAll is true then
    *              the last member is the destination. Each location must
    *              be a GeoAddress
    *
    * @param   AllToAll   If true then a matrix of time and distance from
    *              each location to all others is found. If false, time
    *              and distance from the first location (origin) to all
    *              others is found.
    *
    * @param   RouteOptions Specifies options for the route (fastest vs.
    *                      shortest, coverage to use, roads to avoid, etc.).
    *
    * @param   RouteResults Contains the time and distance matrix
    */
   void           DoRouteMatrix(const CMQLocationCollection&   Locations,
                                bool                           AllToAll,
                                const CMQRouteOptions&         RouteOptions,
                                CMQRouteMatrixResults&         RouteResults);

   /**
    * Removes route shape points from the given session.
    *
    * @param szSessionID The session id
    */
   void           DeleteRoute(const char* szSessionID);

   /**
    * Returns a string containing the server coverage information
    *
    * @param type    Type of info to return, Default is 0.  0=CoverageInfo, 1=DataSelectorInfo
    * @return        The string containing the server coverage information
    */
   CMQString      GetServerInfo(long type = 0);

   /**
    * Generates the actual image resulting from the
    * given Session Object.
    *
    * @param  pSession  A Session Object
    * @param  ioImageData  A Reference to a CMQIOMem that will contain the resulting data
    * @param  pDisplayState an optional DisplayState Object
    */
   void      GetMapImageDirectEx(CMQSession* pSession, CMQIOMem& ioImageData,
                                    CMQDisplayState *pDisplayState = NULL);

   /**
    * Generates the actual image resulting from the
    * given Session Identifier.
    *
    * @param  strSessionUID  The Session's unique identifier.
    * @param  ioImageData  A Reference to a CMQIOMem that will contain the resulting data
    * @param  pDisplayState an optional DisplayState Object
    */
   void      GetMapImageFromSession(const CMQString& strSessionUID,  CMQIOMem& ioImageData, CMQDisplayState *pDisplayState = NULL);


   /**
    * Generates a request to the MapQuest server (as specified by the server name, path, and port number) to perform
    * a DB Search based on either the recordIds received or the extraCriteria info of the dblayerquery.
    * The resulting recordset contains fields specified by the scFields param.
    *
    * @param scFields StringCollection containing the names of the fields to return, or blank for all fields.
    *
    * @param DBLayerQuery Contains the name of the dblayer/table to query.
    *        Optionally contains ExtraCriteria.  Utilized only if RecordIds are empty.
    *
    * @param rsResults The Returned RecordSet containg the records and fields matching the input parameters.
    *
    * @param scRecIds  RecordIdentifiers of the records to return stored in a StringCollection.
    */
   void           GetRecordInfo(const CMQStringCollection &scFields,
                              const CMQDBLayerQuery &DBLayerQuery,
                              CMQRecordSet &rsResults,
                              const CMQStringCollection &scRecIds);

protected:
   void           UpdateSession(const CMQString strSessionUID,
                                CMQMapCommand *pMapCommand,
                                CMQMapState *pInMapState = NULL,
                                CMQMapState *pNewMapState = NULL,
                                CMQCoverageStyle *pCovStyle = NULL,
                                CMQDBLayerQueryCollection *pDBLayers = NULL,
                                CMQFeatureCollection *pFeatures = NULL,
                                CMQPrimitiveCollection *pPrimitives = NULL);
                  // CMQMapCommand is reserved for internal use only

   //{secret}
   CMQString         m_strHTTPMapServer;
   //{secret}
   CMQString         m_strPathToServer;
   //{secret}
   unsigned short    m_sHTTPPort;
   //{secret}
   long              m_lEncryptionType;
   //{secret}
   CMQString         m_strClientId;
   //{secret}
   long              m_elTimeout;
    //{secret}
   CMQIOMem          m_IOMem;
    //{secret}
   CMQIOMem          m_IOResponse;
    //{secret}
   CMQSocket*        m_pSocket;

   //{secret}
   CMQString         m_strProxyServerName;
   //{secret}
   unsigned short    m_sProxyPort;
   //{secret}
   CMQString         m_strProxyServerUser;
   //{secret}
   CMQString         m_strProxyServerPassword;

   bool              m_bVerboseConsoleOutput;

protected:
    //{secret}
   static const char* const m_strServer;
    //{secret}
   static const char* const m_strMETHOD_GET;
    //{secret}
   static const char* const m_strMETHOD_POST;
    //{secret}
   static const char        m_cGET;
    //{secret}
   static const char        m_cPOST;
#ifdef MQWIN32
    //{secret}
   static unsigned long              s_ulWSAUseCount;
    //{secret}
   static CMQCriticalSection m_WinsockCS;
    //{secret}
   void                      InitWinsock();
    //{secret}
   void                      UninitWinsock();
#endif
   // {secret}
   bool IsAlive();

   // {secret}
   // Connect to server via socket
   void           MakeConnection();

   // {secret}
   // Close connection to server
   void           CloseConnection();

   // {secret}
   // Obtain authentication
   void           GetAuthentication(CMQAuthentication& Authentication);


   // {secret}
   // HTTP method/action handlers
   void           MethodGET(CMQString *pstrServerAPI);
   CMQIO*         MethodPOST(CMQString *pstrServerAPI, unsigned long* pulContentLength = NULL);


   // {secret}
   // HTTP message handlers
   // Write the request line; strServerAPI is the server API to call
   void           WriteRequestLine(const char* const pMethod,
                                   CMQString& strServerAPI,
                                   CMQString* buffer);

   // {secret}
   // Write the request headers; for now, just Entity-Header fields
   // POST requires a content-length field in the Entity-Header
   void           WriteRequestHeaders(char cMethod, int nSize, CMQString* buffer);

   // {secret}
   // Write the Entity-Body
   void           WriteEntityBody(const char* pBuf, int nSize, CMQString* buffer);

   // {secret}
   // Write to the Socket
   void           WriteToSocket(CMQString& buffer);

   // {secret}
   // Read the response Header
   bool       ReadNextResponseHeader(CMQString &strItem, CMQString &strValue, const char* szDelim = ":");

   // {secret}
   // Read the error description in a Response Entity-Body
   CMQString      ReadEntityBodyError(int nContentLength);

   // {secret}
   // Read the content in a Response Entity-Body
   int ReadEntityBody(void* pData, long lContentLength);

   // End of HTTP message handlers


   // {secret}
   CMQString      absoluteURIbase();


    //{secret}
   CMQString      m_strPassword;
    //{secret}
   CMQString      m_strXInfo;
};

#endif // _IFEXEC_H_



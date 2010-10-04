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
#ifndef _MQDEF_H_
// {secret}
#define _MQDEF_H_

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//  THIS FILE DEPRICATED DO NOT USE THESE CONSTANTS
//  INSTEAD USE CMQXXXX::CLASS_ID and/or CMQXXXX:CLASS_NAME static members
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


/*NO_DOC @defgroup Mapquest Mapquest objects */
/*NO_DOC @defgroup Constants Mapquest constant values */
/*NO_DOC @defgroup TypeIds Object TypeIDs
 *  @ingroup Constants
 */
/*NO_DOC @defgroup ClassNames Object Class Names
 *  @ingroup Constants
 */


/*NO_DOC
 * Id for object CMQPointFeature
 * @ingroup TypeIds
 */
const int         CLASSTYPE_POINTFEATURE                 = 1000;
/*NO_DOC
 * Class Name for object CMQPointFeature
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_POINTFEATURE              = "PointFeature";
/*NO_DOC
 * Id for object CMQDTCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DTCOLLECTION                 = 1040;
/*NO_DOC
 * Class Name for object CMQDTCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DTCOLLECTION              = "DTCollection";
/*NO_DOC
 * Id for object CMQCoverageStyle
 * @ingroup TypeIds
 */
const int         CLASSTYPE_COVERAGESTYLE                = 1050;
/*NO_DOC
 * Class Name for object CMQCoverageStyle
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_COVERAGESTYLE             = "CoverageStyle";
/*NO_DOC
 * Id for object CMQDTStyle
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DTSTYLE                      = 1060;
/*NO_DOC
 * Class Name for object CMQDTStyle
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DTSTYLE                   = "DTStyle";
/*NO_DOC
 * Id for object CMQDTStyleEx
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DTSTYLEEX                    = 1062;
/*NO_DOC
 * Class Name for object CMQDTStyleEx
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DTSTYLEEX                 = "DTStyleEx";
/*NO_DOC
 * Id for object CMQDTFeatureStyleEx
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DTFEATURESTYLEEX             = 1063;
/*NO_DOC
 * Class Name for object CMQDTFeatureStyleEx
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DTFEATURESTYLEEX          = "DTFeatureStyleEx";
/*NO_DOC
 * Id for object CMQAddress
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ADDRESS                      = 1090;
/*NO_DOC
 * Class Name for object CMQAddress
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ADDRESS                   = "Address";
/*NO_DOC
 * Id for object CMQGeoAddress
 * @ingroup TypeIds
 */
const int         CLASSTYPE_GEOADDRESS                   = 1110;
/*NO_DOC
 * Class Name for object CMQGeoAddress
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_GEOADDRESS                = "GeoAddress";
/*NO_DOC
 * Id for object CMQGeocodeOptions
 * @ingroup TypeIds
 */
const int         CLASSTYPE_GEOCODEOPTIONS               = 1130;
/*NO_DOC
 * Class Name for object CMQGeocodeOptions
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_GEOCODEOPTIONS            = "GeocodeOptions";
/*NO_DOC
 * Class Name for object CMQAutoGeocodeCovSwitch
 * @ingroup TypeIds
 */
const int         CLASSTYPE_AUTOGEOCODECOVSWITCH         = 1132;
/*NO_DOC
 * Class Name for object CMQAutoGeocodeCovSwitch
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_AUTOGEOCODECOVSWITCH      = "AutoGeocodeCovSwitch";
/*NO_DOC
 * Id for object CMQLocationCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_LOCATIONCOLLECTION           = 1150;
/*NO_DOC
 * Class Name for object CMQLocationCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_LOCATIONCOLLECTION        = "LocationCollection";
/*NO_DOC
 * Id for object CMQFeatureCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_FEATURECOLLECTION            = 1180;
/*NO_DOC
 * Class Name for object CMQFeatureCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_FEATURECOLLECTION         = "FeatureCollection";
/*NO_DOC
 * Id for object CMQMapState
 * @ingroup TypeIds
 */
const int         CLASSTYPE_MAPSTATE                     = 1190;
/*NO_DOC
 * Class Name for object CMQMapState
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_MAPSTATE                  = "MapState";
/*NO_DOC
 * Id for object CMQRectSearchCriteria
 * @ingroup TypeIds
 */
const int         CLASSTYPE_GEOCODEOPTIONSCOLLECTION     = 1200;
/*NO_DOC
 * Class Name for object CMQGeocodeOptionsCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_GEOCODEOPTIONSCOLLECTION  = "GeocodeOptionsCollection";
const int         CLASSTYPE_RECTSEARCHCRITERIA           = 1210;
/*NO_DOC
 * Class Name for object CMQRectSearchCriteria
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_RECTSEARCHCRITERIA        = "RectSearchCriteria";
/*NO_DOC
 * Id for object CMQRadiusSearchCriteria
 * @ingroup TypeIds
 */
const int         CLASSTYPE_RADIUSSEARCHCRITERIA         = 1220;
/*NO_DOC
 * Class Name for object CMQRadiusSearchCriteria
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_RADIUSSEARCHCRITERIA      = "RadiusSearchCriteria";
/*NO_DOC
 * Id for object CMQCorridorSearchCriteria
 * @ingroup TypeIds
 */
const int         CLASSTYPE_CORRIDORSEARCHCRITERIA       = 1230;
/*NO_DOC
 * Class Name for object CMQCorridorSearchCriteria
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_CORRIDORSEARCHCRITERIA    = "CorridorSearchCriteria";
/*NO_DOC
 * Id for object CMQSession
 * @ingroup TypeIds
 */
const int         CLASSTYPE_SESSIONINFO                  = 1270;
/*NO_DOC
 * Class Name for object CMQSession
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_SESSIONINFO               = "Session";
/*NO_DOC
 * Id for object CMQSessionID
 * @ingroup TypeIds
 */
const int         CLASSTYPE_SESSIONID                    = 1280;
/*NO_DOC
 * Class Name for object CMQSessionID
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_SESSIONID                 = "SessionID";
/*NO_DOC
 * Id for object CMQIdentifyCriteria
 * @ingroup TypeIds
 */
const int         CLASSTYPE_IDENTIFYCRITERIA             = 1300;
/*NO_DOC
 * Class Name for object CMQIdentifyCriteria
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_IDENTIFYCRITERIA          = "IdentifyCriteria";
/*NO_DOC
 * Id for object CMQCenter
 * @ingroup TypeIds
 */
const int         CLASSTYPE_CENTER                       = 1320;
/*NO_DOC
 * Class Name for object CMQCenter
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_CENTER                    = "Center";
/*NO_DOC
 * Id for object CMQCenterLL
 * @ingroup TypeIds
 */
const int         CLASSTYPE_CENTERLL                     = 1330;
/*NO_DOC
 * Class Name for object CMQCenterLL
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_CENTERLL                  = "CenterLL";
/*NO_DOC
 * Id for object CMQZoomIn
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ZOOMIN                       = 1340;
/*NO_DOC
 * Class Name for object CMQZoomIn
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ZOOMIN                    = "ZoomIn";
/*NO_DOC
 * Id for object CMQZoomOut
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ZOOMOUT                      = 1350;
/*NO_DOC
 * Class Name for object CMQZoomOut
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ZOOMOUT                   = "ZoomOut";
/*NO_DOC
 * Id for object CMQZoomToRect
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ZOOMTORECT                   = 1360;
/*NO_DOC
 * Class Name for object CMQZoomToRect
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ZOOMTORECT                = "ZoomToRect";
/*NO_DOC
 * Id for object CMQZoomToRectLL
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ZOOMTORECTLL                 = 1370;
/*NO_DOC
 * Class Name for object CMQZoomToRectLL
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ZOOMTORECTLL              = "ZoomToRectLL";
/*NO_DOC
 * Id for object CMQPan
 * @ingroup TypeIds
 */
const int         CLASSTYPE_PAN                          = 1380;
/*NO_DOC
 * Class Name for object CMQPan
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_PAN                       = "Pan";
/*NO_DOC
 * Id for object CMQBestFit
 * @ingroup TypeIds
 */
const int         CLASSTYPE_BESTFIT                      = 1390;
/*NO_DOC
 * Class Name for object CMQBestFit
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_BESTFIT                   = "BestFit";
/*NO_DOC
 * Id for object CMQBestFitLL
 * @ingroup TypeIds
 */
const int         CLASSTYPE_BESTFITLL                    = 1391;
/*NO_DOC
 * Class Name for object CMQBestFitLL
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_BESTFITLL                 = "BestFitLL";
const int         CLASSTYPE_AUTHENTICATION               = 1400;
const char* const strCLASSTYPE_AUTHENTICATION            = "Authentication";
/*NO_DOC
 * Id for object CMQDBLayerQuery
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DBLAYERQUERY                 = 1410;
/*NO_DOC
 * Class Name for object CMQDBLayerQuery
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DBLAYERQUERY              = "DBLayerQuery";
/*NO_DOC
 * Id for object CMQDBLayerCatToDTMapQuery
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DBLAYERCATTODTMAPQUERY       = 1411;
/*NO_DOC
 * Class Name for object CMQDBLayerCatToDTMapQuery
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DBLAYERCATTODTMAPQUERY    = "DBLayerCatToDTMapQuery";
/*NO_DOC
 * Id for object CMQCatToDTMap
 * @ingroup TypeIds
 */
const int         CLASSTYPE_CATTODTMAP                   = 1412;
/*NO_DOC
 * Class Name for object CMQCatToDTMap
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_CATTODTMAP                = "CatToDTMap";
/*NO_DOC
 * Id for object CMQDBLayerQueryCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DBLAYERQUERYCOLLECTION       = 1420;
/*NO_DOC
 * Class Name for object CMQDBLayerQueryCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DBLAYERQUERYCOLLECTION    = "DBLayerQueryCollection";
/*NO_DOC
 * Id for object CMQCatToDTMapCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_CATTODTMAPCOLLECTION         = 1421;
/*NO_DOC
 * Class Name for object CMQCatToDTMapCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_CATTODTMAPCOLLECTION      = "CatToDTMapCollection";
/*NO_DOC
 * Id for object CMQLineFeature
 * @ingroup TypeIds
 */
const int         CLASSTYPE_LINEFEATURE                  = 1520;
/*NO_DOC
 * Class Name for object CMQLineFeature
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_LINEFEATURE               = "LineFeature";
/*NO_DOC
 * Id for object CMQPolygonFeature
 * @ingroup TypeIds
 */
const int         CLASSTYPE_POLYFEATURE                  = 1530;
/*NO_DOC
 * Class Name for object CMQPolygonFeature
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_POLYFEATURE               = "PolygonFeature";
/*NO_DOC
 * Id for object CMQLatLngCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_LATLNGCOLLECTION             = 1540;
/*NO_DOC
 * Class Name for object CMQLatLngCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_LATLNGCOLLECTION          = "LatLngCollection";
/*NO_DOC
 * Id for object CMQIntCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_INTCOLLECTION                = 1541;
/*NO_DOC
 * Class Name for object CMQIntCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_INTCOLLECTION             = "IntCollection";
/*NO_DOC
 * Id for object CMQStringCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_STRINGCOLLECTION             = 1542;
/*NO_DOC
 * Class Name for object CMQStringCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_STRINGCOLLECTION          = "StringCollection";
/*NO_DOC
 * Id for object CMQPointCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_POINTCOLLECTION              = 1550;
/*NO_DOC
 * Class Name for object CMQPointCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_POINTCOLLECTION           = "PointCollection";
/*NO_DOC
 * Id for object CMQRouteResults
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ROUTERESULTS                 = 1560;
/*NO_DOC
 * Class Name for object CMQRouteResults
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ROUTERESULTS              = "RouteResults";
/*NO_DOC
 * Id for object CMQRouteMatrixResults
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ROUTEMATRIXRESULTS           = 1561;
/*NO_DOC
 * Class Name for object CMQRouteMatrixResults
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ROUTEMATRIXRESULTS        = "RouteMatrixResults";
/*NO_DOC
 * Id for object CMQLinePrimitive
 * @ingroup TypeIds
 */
const int         CLASSTYPE_LINEPRIMITIVE                = 1570;
/*NO_DOC
 * Class Name for object CMQLinePrimitive
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_LINEPRIMITIVE             = "LinePrimitive";
/*NO_DOC
 * Id for object CMQEllipsePrimitive
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ELLIPSEPRIMITIVE             = 1571;
/*NO_DOC
 * Class Name for object CMQEllipsePrimitive
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ELLIPSEPRIMITIVE          = "EllipsePrimitive";
/*NO_DOC
 * Id for object CMQRectanglePrimitive
 * @ingroup TypeIds
 */
const int         CLASSTYPE_RECTPRIMITIVE                = 1572;
/*NO_DOC
 * Class Name for object CMQRectanglePrimitive
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_RECTPRIMITIVE             = "RectanglePrimitive";
/*NO_DOC
 * Id for object CMQTextPrimitive
 * @ingroup TypeIds
 */
const int         CLASSTYPE_TEXTPRIMITIVE                = 1573;
/*NO_DOC
 * Class Name for object CMQTextPrimitive
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_TEXTPRIMITIVE             = "TextPrimitive";
/*NO_DOC
 * Id for object CMQPolygonPrimitive
 * @ingroup TypeIds
 */
const int         CLASSTYPE_POLYGONPRIMITIVE             = 1575;
/*NO_DOC
 * Class Name for object CMQPolygonPrimitive
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_POLYGONPRIMITIVE          = "PolygonPrimitive";
/*NO_DOC
 * Id for object CMQPrimitiveCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_PRIMITIVECOLLECTION          = 1579;
/*NO_DOC
 * Class Name for object CMQPrimitiveCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_PRIMITIVECOLLECTION       = "PrimitiveCollection";
/*NO_DOC
 * Id for object CMQManeuver
 * @ingroup TypeIds
 */
const int         CLASSTYPE_MANEUVER                     = 1600;
/*NO_DOC
 * Class Name for object CMQManeuver
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_MANEUVER                  = "Maneuver";
/*NO_DOC
 * Id for object CMQManeuverCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_MANEUVERCOLLECTION           = 1610;
/*NO_DOC
 * Class Name for object CMQManeuverCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_MANEUVERCOLLECTION        = "ManeuverCollection";
/*NO_DOC
 * Id for object CMQTrekRoute
 * @ingroup TypeIds
 */
const int         CLASSTYPE_TREKROUTE                    = 1620;
/*NO_DOC
 * Class Name for object CMQTrekRoute
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_TREKROUTE                 = "TrekRoute";
/*NO_DOC
 * Id for object CMQTrekRouteCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_TREKROUTECOLLECTION          = 1630;
/*NO_DOC
 * Class Name for object CMQTrekRouteCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_TREKROUTECOLLECTION       = "TrekRouteCollection";
/*NO_DOC
 * Id for object CMQRouteOptions
 * @ingroup TypeIds
 */
const int         CLASSTYPE_ROUTEOPTIONS                 = 1640;
/*NO_DOC
 * Class Name for object CMQRouteOptions
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_ROUTEOPTIONS              = "RouteOptions";
/*NO_DOC
 * Class Name for object CMQAutoRouteCovSwitch
 * @ingroup TypeIds
 */
const int         CLASSTYPE_AUTOROUTECOVSWITCH           = 1642;
/*NO_DOC
 * Class Name for object CMQAutoRouteCovSwitch
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_AUTOROUTECOVSWITCH        = "AutoRouteCovSwitch";
/*NO_DOC
 * Id for object CMQDisplayState
 * @ingroup TypeIds
 */
const int         CLASSTYPE_DISPLAYSTATE                 = 1650;
/*NO_DOC
 * Class Name for object CMQDisplayState
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_DISPLAYSTATE              = "DisplayState";
/*NO_DOC
 * Id for object CMQPolySearchCriteria
 * @ingroup TypeIds
 */
const int         CLASSTYPE_POLYSEARCHCRITERIA           = 1651;
/*NO_DOC
 * Class Name for object CMQPolySearchCriteria
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_POLYSEARCHCRITERIA        = "PolySearchCriteria";
/*NO_DOC
 * Id for object CMQSymbolPrimitive
 * @ingroup TypeIds
 */
const int         CLASSTYPE_SYMBOLPRIMITIVE              = 1652;
/*NO_DOC
 * Class Name for object CMQSymbolPrimitive
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_SYMBOLPRIMITIVE           = "SymbolPrimitive";
/*NO_DOC
 * Id for object CMQFeatureSpecifier
 * @ingroup TypeIds
 */
const int         CLASSTYPE_FEATURESPECIFIER             = 1653;
/*NO_DOC
 * Class Name for object CMQFeatureSpecifier
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_FEATURESPECIFIER          = "FeatureSpecifier";
/*NO_DOC
 * Id for object CMQFeatureSpecifierCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_FEATURESPECIFIERCOLLECTION   = 1654;
/*NO_DOC
 * Class Name for object CMQFeatureSpecifierCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_FEATURESPECIFIERCOLLECTION= "FeatureSpecifierCollection";
/*NO_DOC
 * Id for object CMQAutoMapCovSwitch
 * @ingroup TypeIds
 */
const int         CLASSTYPE_AUTOMAPCOVSWITCH             = 1660;
/*NO_DOC
 * Class Name for object CMQAutoMapCovSwitch
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_AUTOMAPCOVSWITCH          = "AutoMapCovSwitch";
/*NO_DOC
 * Id for object CMQSign
 * @ingroup TypeIds
 */
const int         CLASSTYPE_SIGN                         = 1670;
/*NO_DOC
 * Class Name for object CMQSign
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_SIGN                      = "Sign";
/*NO_DOC
 * Id for object CMQSignCollection
 * @ingroup TypeIds
 */
const int         CLASSTYPE_SIGNCOLLECTION               = 1680;
/*NO_DOC
 * Class Name for object CMQSignCollection
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_SIGNCOLLECTION            = "SignCollection";
/*NO_DOC
 * Id for object CMQLatLng
 * @ingroup TypeIds
 */
const int         CLASSTYPE_LATLNG                       = 1700;
/*NO_DOC
 * Class Name for object CMQLatLng
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_LATLNG                    = "LatLng";
/*NO_DOC
 * Id for object CMQPoint
 * @ingroup TypeIds
 */
const int         CLASSTYPE_POINT                        = 1701;
/*NO_DOC
 * Class Name for object CMQPoint
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_POINT                     = "Point";
/*NO_DOC
 * Id for object CMQRecordSet
 * @ingroup TypeIds
 */
const int         CLASSTYPE_RECORDSET                    = 1710;
/*NO_DOC
 * Class Name for object CMQRecordSet
 * @ingroup ClassNames
 */
const char* const strCLASSTYPE_RECORDSET                 = "RecordSet";


#endif   // _MQDEF_H_



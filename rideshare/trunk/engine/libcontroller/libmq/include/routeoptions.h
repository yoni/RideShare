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
#ifndef _MQROUTEOPTIONS_H_
// {secret}
#define _MQROUTEOPTIONS_H_

#include "mqobject.h"
#include "stringcollection.h"
#include "intcollection.h"
#include "autoroutecovswitch.h"


/**
 * Constants to specify the type of route wanted.
 * @see CMQRouteOptions
 * @ingroup Constants
 */
class CMQRouteType
{
public:
   static const long FASTEST;       /**< Compute fastest route */
   static const long SHORTEST;      /**< Compute shortest route */
   static const long PEDESTRIAN;    /**< Compute pedestrian route */
   static const long OPTIMIZED;     /**< Compute optimized route to set of itineraries */
   static const long SELECT_DATASET_ONLY; /**< Don't Compute route just perform Route data set selection */
};


/**
 * Constants to specify the type of narrative to generate.
 * @see CMQRouteOptions
 * @ingroup Constants
 */
class CMQNarrativeType
{
public:
   static const long DEFAULT; /**< Default (plain text) narrative */
   static const long HTML;    /**< HTML narrative */
   static const long NONE;    /**< No narrative */
};



/**
 * This class is used to set various options
 * that will affect the type of route result returned
 * from the DoRoute function
 * @see CMQRouteType
 * @see CMQNarrativeType
 * @ingroup Mapquest
 */
class CMQRouteOptions : public CMQObject
{
public:
#ifdef _MQ_DEPRECATED_
   static const char* szAttr_LimitedAccess;  /**< @deprecated use AVOID_ATTRIBUTE_LIMITED_ACCESS*/
   static const char* szAttr_TollRoad;       /**< @deprecated use AVOID_ATTRIBUTE_TOLL_ROAD*/
   static const char* szAttr_Ferry;          /**< @deprecated use AVOID_ATTRIBUTE_FERRY*/
   static const char* szAttr_UnpavedRoad;    /**< @deprecated use AVOID_ATTRIBUTE_UNPAVED_ROAD*/
   static const char* szAttr_Seasonal;       /**< @deprecated use AVOID_ATTRIBUTE_SEASONAL*/

   static const long nRouteType_Fastest;     /**< @deprecated use CMQRouteType::FASTEST*/
   static const long nRouteType_Shortest;    /**< @deprecated use CMQRouteType::SHORTEST*/
   static const long nRouteType_Pedestrian;  /**< @deprecated use CMQRouteType::PEDESTRIAN*/
   static const long nRouteType_Optimized;   /**< @deprecated use CMQRouteType::OPTIMIZED*/
   static const long nRouteType_SelectDatasetOnly; /**< @deprecated use CMQRouteType::SELECT_DATASET_ONLY*/

   static const long nNarrType_Default;   /**< @deprecated use CMQNarrativeType::DEFAULT*/
   static const long nNarrType_HTML;      /**< @deprecated use CMQNarrativeType::HTML*/
   static const long nNarrType_None;      /**< @deprecated use CMQNarrativeType::NONE*/

   static const char* szLanguage_English;          /**< @deprecated use LANGUAGE_ENGLISH*/
   static const char* szLanguage_French;           /**< @deprecated use LANGUAGE_FRENCH*/
   static const char* szLanguage_German;           /**< @deprecated use LANGUAGE_GERMAN*/
   static const char* szLanguage_Italian;          /**< @deprecated use LANGUAGE_ITALIAN*/
   static const char* szLanguage_Spanish;          /**< @deprecated use LANGUAGE_SPANISH*/
   static const char* szLanguage_Danish;           /**< @deprecated use LANGUAGE_DANISH*/
   static const char* szLanguage_Dutch;            /**< @deprecated use LANGUAGE_DUTCH*/
   static const char* szLanguage_Norwegian;        /**< @deprecated use LANGUAGE_NORWEGIAN*/
   static const char* szLanguage_Swedish;          /**< @deprecated use LANGUAGE_SWEDISH*/
   static const char* szLanguage_Iberian_Spanish;  /**< @deprecated use LANGUAGE_IBERIAN_SPANISH*/
   static const char* szLanguage_BritishEnglish;   /**< @deprecated use LANGUAGE_BRITISH_ENGLISH*/
   static const char* szLanguage_Iberian_Portuguese; /**< @deprecated use LANGUAGE_IBERIAN_PORTUGUESE*/
#endif

   static const char* AVOID_ATTRIBUTE_LIMITED_ACCESS; /**< Avoid Limited Access Roads */
   static const char* AVOID_ATTRIBUTE_TOLL_ROAD;      /**< Avoid Toll Roads */
   static const char* AVOID_ATTRIBUTE_FERRY;          /**< Avoid Ferries */
   static const char* AVOID_ATTRIBUTE_UNPAVED_ROAD;   /**< Avoid Unpaved Roads */
   static const char* AVOID_ATTRIBUTE_SEASONAL;       /**< Avoid Seasonal Roads */

   static const char* LANGUAGE_ENGLISH;            /**< Narrative in: English */
   static const char* LANGUAGE_FRENCH;             /**< Narrative in: French */
   static const char* LANGUAGE_GERMAN;             /**< Narrative in: German */
   static const char* LANGUAGE_ITALIAN;            /**< Narrative in: Italian */
   static const char* LANGUAGE_SPANISH;            /**< Narrative in: Spanish */
   static const char* LANGUAGE_DANISH;             /**< Narrative in: Danish */
   static const char* LANGUAGE_DUTCH;              /**< Narrative in: Dutch */
   static const char* LANGUAGE_NORWEGIAN;          /**< Narrative in: Norwegian */
   static const char* LANGUAGE_SWEDISH;            /**< Narrative in: Swedish */
   static const char* LANGUAGE_IBERIAN_SPANISH;    /**< Narrative in: Iberian Spanish */
   static const char* LANGUAGE_BRITISH_ENGLISH;    /**< Narrative in: British English */
   static const char* LANGUAGE_IBERIAN_PORTUGUESE; /**< Narrative in: Iberian Portuguese */


public:
   /**
    * Constructor
    */
   CMQRouteOptions();
   /**
    * Destructor
    */
   virtual ~CMQRouteOptions();

   /**
    * Sets the route type.
    * @param nRouteTypeFlag long
    * @see RouteTypes for valid values
    */
   void SetRouteType(long nRouteTypeFlag);
   /**
    * Gets the route type
    * @return long
    * @see RouteTypes for valid values
    */
   long GetRouteType() const;

   /**
    * Sets the narrative type.
    * @param nNarrTypeFlag long
    * @see NarrTypes for valid values
    */
   void SetNarrativeType(long nNarrTypeFlag);
   /**
    * Gets the narrative type
    * @return long
    * @see NarrTypes for valid values
    */
   long GetNarrativeType() const;

   /**
    * Sets the narrative distance units
    * @param nNarrDistanceUnitType long distance units
    * @see CMQDistanceUnits
    */
   void SetNarrativeDistanceUnitType(long nNarrDistanceUnitType);
   /**
    * Gets the narrative distance units
    * @return long
    * @see CMQDistanceUnits for valid values
    */
   long GetNarrativeDistanceUnitType() const;

   /**
    * Sets the maximum shape points for a maneuver.
    * Reducing the number of shape points requested will reduce the amount of
    * data returned from the server.
    * @param nCount long the number of shape points
    */
   void SetMaxShapePointsPerManeuver(long nCount);
   /**
    * Gets the maximum shape points for a maneuver.
    * @return long the number of shape points
    */
   long GetMaxShapePointsPerManeuver() const;

   /**
    * Sets the maximum GEFIDs for a maneuver.
    * Reducing the number of GEFIDs requested will reduce the amount of
    * data returned from the server.
    * @param nCount long the number of GEFIDs
    */
   void SetMaxGEFIDsPerManeuver(long nCount);
   /**
    * Gets the maximum GEFIDs for a maneuver.
    * @return long the number of GEFIDs
    */
   long GetMaxGEFIDsPerManeuver() const;

   /**
    * Sets the language for the narrative.
    * @param szLanguage const char *
    * @see Languages for valid values
    */
   void SetLanguage(const char* szLanguage);
   /**
    * Gets the language for the narrative.
    * @return CMQString
    */
   const CMQString& GetLanguage() const;

   /**
    * Returns a reference to a CMQStringCollection containing Avoids
    * @return CMQStringCollection
    * @see Avoids
    */
   CMQStringCollection& AvoidAttributeList();

   /**
    * Returns a reference to a CMQIntCollection containing GEFIDs.
    * Any GEFID entered in this array will try to be avoided when calculating the route
    * @return CMQIntCollection
    */
   CMQIntCollection& AvoidGefIdList();

   /**
    * Returns a reference to a CMQIntCollection containing GEFIDs
    * Any GEFID entered in this array WILL be avoided when calculating the route.
    * Values entered in this list may cause the route to be incomplete.
    */
   CMQIntCollection& AvoidAbsoluteGefIdList();

   /**
    * Set the coverage name of the routing data to use
    * takes precedence over CovSwitcher
    * @param szCovId   the coverage name
    */
   void              SetCoverageName(const char* szCovId);
   /**
    * Get the coverage name of the routing data to use
    * takes precedence over CovSwitcher
    * @return    the coverage name
    */
   const CMQString&  GetCoverageName() const;

   /**
    * Returns a reference to a CMQAutoRouteCovSwitch object, which when selected
    * will use the name specified in this object to select a Route data selector
    * to automatically select a valid coverage to route on.
    * CoverageName property takes precedence over this object.
    * Leave Coverage name and CovSwitcher blank to use server default switcher
    * If configured.
    */
   CMQAutoRouteCovSwitch& CovSwitcher();

   /**
    * Sets the state boundary display flag.
    * @param  bFlag  true if a state boundary text should be displayed,
    *                false otherwise.
    */
   void SetStateBoundaryDisplay(bool bFlag);
   /**
    * Gets the state boundary display flag.
    * @return true if a state boundary text should be displayed,
    *         false otherwise.
    */
   bool GetStateBoundaryDisplay() const;

   /**
    * Sets the Country boundary display flag.
    * @param  bFlag  true if a Country boundary text should be displayed,
    *                false otherwise.
    */
   void SetCountryBoundaryDisplay(bool bFlag);
   /**
    * Gets the Country boundary display flag.
    * @return true if a Country boundary text should be displayed,
    *         false otherwise.
    */
   bool GetCountryBoundaryDisplay() const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1640};
#else
   static const int   CLASS_ID = 1640;
#endif
   /**
    * Text name of this class
    */
   static const char* CLASS_NAME;

   /**
    * Returns the text name of this class
    * @return Text name of the this object
    */
   virtual const char* GetClassName() const { return CLASS_NAME; };
   /**
    * Returns the numeric id of this class
    * @return Numeric id of this object
    */
   virtual int         GetClassId()   const { return CLASS_ID;   };

   // {secret}
   virtual void LoadMe(CMQIO& io, long lVersion = -1);
   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   long                 m_nRouteType;
   // {secret}
   long                 m_nNarrativeType;
   // {secret}
   long                 m_nNarrativeDistanceUnitType;
   // {secret}
   long                 m_nMaxShape;
   // {secret}
   long                 m_nMaxGEFID;
   // {secret}
   CMQString            m_strLanguage;
   // {secret}
   CMQStringCollection* m_AvoidAttrList;
   // {secret}
   CMQIntCollection*    m_AvoidGefIdList;
   // {secret}
   CMQIntCollection*    m_AvoidAbsGefIdList;
   // {secret}
   CMQString            m_strCoverageName;
   // {secret}
   CMQAutoRouteCovSwitch* m_AutoRouteCovSwitch;
   // {secret}
   bool                 m_bStateBoundaryDisplay;
   // {secret}
   bool                 m_bCountryBoundaryDisplay;
};

#endif   // _MQROUTEOPTIONS_H_



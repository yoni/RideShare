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
#ifndef _MQROUTERESULTS_H_
// {secret}
#define _MQROUTERESULTS_H_

#include "mqobject.h"
#include "trekroutecollection.h"
#include "stringcollection.h"
#include "location.h"


/**
 * Constants used to define return codes from a Route call.
 * @see CMQRouteResults
 * @ingroup Constants
 */
class CMQRouteResultsCode
{
public:
   static const long SUCCESS;          /**< Success */
   static const long INVALID_LOCATION; /**< Invalid Location */
   static const long ROUTE_FAILURE;    /**< Route Failure */
   static const long NOT_SPECIFIED;    /**< Not Specified */
   static const long NO_DATASET_FOUND; /**< Valid Data set not found */
};


/**
 * This class will contain the information returned from
 * a Route call.
 * @see CMQRouteResultsCode
 * @ingroup Mapquest
 */
class CMQRouteResults : public CMQObject
{
public:
#ifdef _MQ_DEPRECATED_
   static const long RC_Success;          /**< @deprecated use CMQRouteResultsCode::SUCCESS*/
   static const long RC_InvalidLocation;  /**< @deprecated use CMQRouteResultsCode::INVALID_LOCATION*/
   static const long RC_RouteFailure;     /**< @deprecated use CMQRouteResultsCode::ROUTE_FAILURE*/
   static const long RC_NotSpecified;     /**< @deprecated use CMQRouteResultsCode::NOT_SPECIFIED*/
   static const long RC_NoDatasetFound;   /**< @deprecated use CMQRouteResultsCode::NO_DATASET_FOUND*/
#endif
   /**
    * Constructor.
    */
   CMQRouteResults();
   /**
    * Constructor.
    * @param Object Object to copy
    */
   CMQRouteResults(const CMQRouteResults& Object);

   /**
    * Destructor.
    */
   virtual ~CMQRouteResults();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQRouteResults& operator=(const CMQRouteResults& Object);

   // {secret}
   void SetResultCode(long lResultCode){m_lResultCode = lResultCode;}
   /**
    * Gets the Result code.
    * When the result code is not SUCCESS ResultMessages may contain a more
    * detailed explanation of the failure.
    */
   long GetResultCode() const {return m_lResultCode;}

   // {secret}
   void              SetCoverageName(const char* szCovId);
   /**
    * Gets the Coverage name used to perform this route.
    */
   const CMQString&  GetCoverageName() const;

   /**
    * Returns a reference to a CMQStringCollection containing error messages.
    * Each result message should contain a unique number followed by
    * a text .  Ex: "200 Unable to calculate route."
    * Messages for invalid options should be numbered 300..399
    * Messages for invalid locations should be numbered 100..199
    * Messages for route failures should be numbered 200..299
    */
   CMQStringCollection& ResultMessages(){return (*m_ResultMessages);}

   /**
    * Returns a reference to the collection of CMQTrekRoute objects (or legs) for this route.
    */
   CMQTrekRouteCollection& TrekRoutes(){return (*m_TrekRouteCollection);}

   /**
    * Get the distance of the entire route.
    */
   double GetDistance();

   /**
    * Get the time to drive the entire route.
    */
   long GetTime();

   /**
    * Returns all shape points from each maneuver in route.
    */
   CMQLatLngCollection& GetShapePoints();

   /**
    * Returns all Locations used in the route.  LatLng may be altered to closest
    * point on found road segment.  Locations may be re-ordered in the case
    * of an optimized route
    */
   CMQLocationCollection& GetLocations();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1560};
#else
   static const int   CLASS_ID = 1560;
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
   long                    m_lResultCode;
   // {secret}
   CMQString               m_strCoverageName;
   // {secret}
   CMQStringCollection*    m_ResultMessages;
   // {secret}
   CMQTrekRouteCollection* m_TrekRouteCollection;

   // {secret}
   double                  m_dDistance;
   // {secret}
   long                    m_lTime;
   // {secret}
   CMQLatLngCollection*    m_ShapePnts;
   // {secret}
   CMQLocationCollection*  m_Locations;
};

#endif   // _MQROUTERESULTS_H_



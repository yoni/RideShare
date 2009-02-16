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
#ifndef _MQROUTEMATRIXRESULTS_H_
// {secret}
#define _MQROUTEMATRIXRESULTS_H_

#include "mqobject.h"
#include "intcollection.h"
#include "stringcollection.h"


/**
 * Constants used to define return codes from a RouteMatrix call.
 * @see CMQRouteMatrixResults
 * @ingroup Constants
 */
class CMQRouteMatrixResultsCode
{
public:
   static const long SUCCESS;          /**< Success */
   static const long INVALID_LOCATION; /**< Invalid Location */
   static const long ROUTE_FAILURE;    /**< Route Failure */
   static const long NOT_SPECIFIED;    /**< Not Specified */
   static const long NO_DATASET_FOUND; /**< Valid Data set not found */
   static const long INVALID_OPTION;   /**< Invalid Option */
   static const long PARTIAL_SUCCESS;  /**< Not all destinations found */
   static const long EXCEEDED_MAX_LOCATIONS; /**< Exceeded maximum location count */
};


/**
 * This class will contain the information returned from
 * a DoRouteMatrix call.
 * @see CMQRouteMatrixResultsCode
 * @ingroup Mapquest
 */
class CMQRouteMatrixResults : public CMQObject
{
public:
#ifdef _MQ_DEPRECATED_
   static const long RC_Success;          /**< @deprecated use CMQRouteMatrixResultsCode::SUCCESS*/
   static const long RC_InvalidLocation;  /**< @deprecated use CMQRouteMatrixResultsCode::INVALID_LOCATION*/
   static const long RC_RouteFailure;     /**< @deprecated use CMQRouteMatrixResultsCode::ROUTE_FAILURE*/
   static const long RC_NotSpecified;     /**< @deprecated use CMQRouteMatrixResultsCode::NOT_SPECIFIED*/
   static const long RC_NoDatasetFound;   /**< @deprecated use CMQRouteMatrixResultsCode::NO_DATASET_FOUND*/
   static const long RC_InvalidOption;    /**< @deprecated use CMQRouteMatrixResultsCode::INVALID_OPTION*/
   static const long RC_PartialSuccess;   /**< @deprecated use CMQRouteMatrixResultsCode::PARTIAL_SUCCESS*/
   static const long RC_ExceededMaxLocations; /**< @deprecated use CMQRouteMatrixResultsCode::EXCEEDED_MAX_LOCATIONS*/
#endif
   /**
    * Constructor.
    */
   CMQRouteMatrixResults();
   /**
    * Copy constructor.
    * @param Object Object to copy
    */
   CMQRouteMatrixResults(const CMQRouteMatrixResults& Object);

   /**
    * Destructor.
    */
   virtual ~CMQRouteMatrixResults();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQRouteMatrixResults& operator=(const CMQRouteMatrixResults& Object);

   // {secret}
   void SetLocationCount(long count)
   {
      m_locationCount = count;
   }
   /**
    * Gets the number of locations.
    *
    * @return   Returns the number of locations.
    */
   long GetLocationCount() const
   {
      return m_locationCount;
   }

   // {secret}
   void SetResultCode(long resultCode)
   {
      m_lResultCode = resultCode;
   }
   /**
    * Gets the Result code.
    * When the result code is not SUCCESS ResultMessages may contain a more
    * detailed explanation of the failure.
    *
    * @return   Returns the result code.
    */
   long GetResultCode() const
   {
      return m_lResultCode;
   }

   // {secret}
   void SetAllToAllFlag(bool bAllToAll)
   {
      m_bAllToAll = bAllToAll;
   }
   /**
    * Gets the all-to-all flag.
    *
    * @return   Returns the allToAll flag. True if the matrix is from each
    *           location to each other, False if from location 0 to all
    *           others.
    */
   bool GetAllToAllFlag() const
   {
      return m_bAllToAll;
   }

   // {secret}
   void SetCoverageName(const char* covID);
   /**
    * Gets the Coverage name used to perform this route.
    *
    * @return   Returns the coverage name string.
    */
   const CMQString& GetCoverageName() const;

   /**
    * Returns a reference to a CMQStringCollection containing error messages.
    * Each result message should contain a unique number followed by
    * a text .  Ex: "200 Unable to calculate route."
    * Messages for invalid options should be numbered 300..399
    * Messages for invalid locations should be numbered 100..199
    * Messages for route failures should be numbered 200..299
    */
   CMQStringCollection& ResultMessages()
   {
      return (*m_ResultMessages);
   }

   /**
    * Get the distance of the specified origin,destination pair
    *
    * @param   from   From index in the location list.
    * @param   to     To index in the location list.
    *
    * @return   Returns the distance
    */
   double GetDistance(const unsigned int from, const unsigned int to);

   /**
    * Get the time (seconds) to drive from the specified origin to
    * the specified destination index.
    *
    * @param   from   From index in the location list.
    * @param   to     To index in the location list.
    *
    * @return   Returns the time in seconds.
    */
   long GetTime(const unsigned int from, const unsigned int to);

   // {secret}
   void AddTimeAndDistance(const unsigned int time, const unsigned int dist);

   // {secret}
   void SetTimeAndDistance(const unsigned int from, const unsigned int to,
                           long time, long dist);
   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1561};
#else
   static const int   CLASS_ID = 1561;
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
   bool                    m_bAllToAll;
   // {secret}
   long                    m_locationCount;
   // {secret}
   CMQString               m_strCoverageName;
   // {secret}
   CMQStringCollection*    m_ResultMessages;
   // {secret}
   CMQIntCollection*       m_distance;
   // {secret}
   CMQIntCollection*       m_time;
};

#endif   // _MQROUTERESULTS_H_



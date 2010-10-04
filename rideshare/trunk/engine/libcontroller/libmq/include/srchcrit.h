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
#ifndef _MQSRCHCRIT_H_
// {secret}
#define _MQSRCHCRIT_H_

#include "mqobject.h"
#include "latlngcollection.h"
#include "featurecollection.h"

/**
 * Base class for search criteria.
 * @ingroup Mapquest
 */
class CMQSearchCriteria : public CMQObject
{
public:

   /**
    * Constructor
    */
   CMQSearchCriteria();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQSearchCriteria &operator=(const CMQSearchCriteria& Object);

   // {secret}
   virtual void LoadMe(CMQIO& io, long lVersion = -1);
   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const;

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Set the maximum number of features to search for
    * @param lMaxMatches   the maximum number of features to search for
    */
   void  SetMaxMatches( long lMaxMatches ) { m_lMaxMatches = lMaxMatches; }
   /**
    * Get the maximum number of features to search for
    * @return    the maximum number of features to search for
    */
   long  GetMaxMatches() const { return m_lMaxMatches; }


   // {secret}
   virtual void  GetBoundingRect(CMQLatLng& /*LLTarget*/, CMQLatLng& /*URTarget*/) const {};
   // {secret}
   virtual void  PreSearch(CMQFeatureCollection& /*fcFound*/) {};
   // {secret}
   virtual unsigned long SelectFeature(CMQFeature* pFeature, CMQFeatureCollection& fcFound) = 0;
   // {secret}
   virtual void  PostSearch(CMQFeatureCollection& /*fcFound*/) {};
   // {secret}
   virtual bool  OkToContinue(CMQFeatureCollection& /*fcFound*/) { return true; };

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   long    m_lMaxMatches;
   // {secret}
   CMQLatLng m_LLTarget;
   // {secret}
   CMQLatLng m_URTarget;
};

/**
 * This object describes a circular area to be searched.
 * @ingroup Mapquest
 */
class CMQRadiusSearchCriteria : public CMQSearchCriteria
{
public:
   /**
    * Constructor
    */
   CMQRadiusSearchCriteria();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQRadiusSearchCriteria(const CMQRadiusSearchCriteria& Object);

   /**
    * Destructor
    */
   virtual ~CMQRadiusSearchCriteria();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQRadiusSearchCriteria &operator=(const CMQRadiusSearchCriteria& Object);

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1220};
#else
   static const int   CLASS_ID = 1220;
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


   /**
    * Set the origin to search from.
    * @param LatLong Lat/Long Object that specifies the origin location.
    */
   void SetCenter( const CMQLatLng &LatLong ) { (*m_llCenter) = LatLong; }
   /**
    * Get the origin to search from.
    * @return Lat/Long Object that specifies the origin location.
    */
   CMQLatLng &GetCenter() { return ( (*m_llCenter) ); }
   /**
    * Set radius to search from the origin.
    * @param dRadius radius to search from the origin
    * @param lUnits    the units type to return
    * @see CMQDistanceUnits
    */
   void SetRadius(const double dRadius, long lUnits = CMQDistanceUnits::MILES);
   /**
    * Get radius to search from the origin
    * @param lUnits    the units type to return
    * @return radius to search from the origin
    * @see CMQDistanceUnits
    */
   double GetRadius(long lUnits = CMQDistanceUnits::MILES) const;

   // {secret}
   virtual void  GetBoundingRect(CMQLatLng &LLTarget, CMQLatLng &URTarget) const;
   // {secret}
   virtual void  PreSearch(CMQFeatureCollection& fcFound);
   // {secret}
   virtual unsigned long SelectFeature(CMQFeature* pFeature, CMQFeatureCollection& fcFound);
   // {secret}
   virtual void  PostSearch(CMQFeatureCollection& fcFound);

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   virtual unsigned long SelectLineFeature(CMQLatLngCollection &llColl, double& dDistance, CMQLatLng& llClosest);
   // {secret}
   virtual unsigned long SelectPtFeature(CMQLatLng &ll, double& dDistance);
   // {secret}
   virtual unsigned long SelectPolyFeature(CMQLatLngCollection &llColl, double& dDistance, CMQLatLng& llClosest);

   // {secret}
   class CMQFeatCompare
   {
   public:
      bool operator() (CMQFeature* pFeat1, CMQFeature* pFeat2)
      {
         return pFeat1->GetDistance() < pFeat2->GetDistance();
      };
   };

protected:
   // {secret}
   CMQLatLng* m_llCenter;
   // {secret}
   double    m_dRadius;
};


/**
 * Criteria defining a rectangular area to search.
 * @ingroup Mapquest
 */
class CMQRectSearchCriteria : public CMQSearchCriteria
{
public:
   /**
    * Constructor
    */
   CMQRectSearchCriteria();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQRectSearchCriteria(const CMQRectSearchCriteria& Object);

   /**
    * Destructor
    */
   virtual ~CMQRectSearchCriteria();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQRectSearchCriteria &operator=(const CMQRectSearchCriteria& Object);

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1210};
#else
   static const int   CLASS_ID = 1210;
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

   /**
    * Set UL corner of the bounding rectangle.
    * @param ll   UpperLeft corner of bounding rectangle.
    */
   void SetUpperLeft(const CMQLatLng& ll) { (*m_llUL) = ll;}
   /**
    * Get UL corner of the bounding rectangle.
    * @return  UpperLeft corner of bounding rectangle.
    */
   CMQLatLng& GetUpperLeft() { return ( (*m_llUL) ); }
   /**
    * Set LR corner of the bounding rectangle.
    * @param ll   LowerRight corner of bounding rectangle.
    */
   void SetLowerRight(const CMQLatLng& ll) {(*m_llLR) = ll;}
   /**
    * Get LR corner of the bounding rectangle.
    * @return  LowerRight corner of bounding rectangle.
    */
   CMQLatLng& GetLowerRight() { return ( (*m_llLR) ); }

   // {secret}
   virtual void  GetBoundingRect(CMQLatLng &LLTarget, CMQLatLng &URTarget) const;
   // {secret}
   virtual void  PreSearch(CMQFeatureCollection& fcFound);
   // {secret}
   virtual unsigned long SelectFeature(CMQFeature* pFeature, CMQFeatureCollection& fcFound);
   // {secret}
   virtual bool  OkToContinue(CMQFeatureCollection& fcFound);

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   virtual unsigned long SelectLineFeature(CMQLatLngCollection &llColl);
   // {secret}
   virtual unsigned long SelectPtFeature(CMQLatLng &ll);
   // {secret}
   virtual unsigned long SelectPolyFeature(CMQLatLngCollection &llColl);

protected:
   // {secret}
   CMQLatLng* m_llUL;
   // {secret}
   CMQLatLng* m_llLR;
   // {secret}
   CMQLatLngCollection m_llColl;
};


/**
 * Criteria defining a polygonal area to search.
 * @ingroup Mapquest
 */
class CMQPolySearchCriteria : public CMQSearchCriteria
{
public:
   /**
    * Constructor
    */
   CMQPolySearchCriteria();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQPolySearchCriteria(const CMQPolySearchCriteria& Object);

   /**
    * Destructor
    */
   virtual ~CMQPolySearchCriteria();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQPolySearchCriteria &operator=(const CMQPolySearchCriteria& Object);

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1651};
#else
   static const int   CLASS_ID = 1651;
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

   /**
    * Get the LatLng Collection of Shape points  representing the polygon to search.
    * @return CMQLatLngCollection of shape points.
    */
   CMQLatLngCollection &ShapePoints() { return (*m_llColl); }

   // {secret}
   virtual void  GetBoundingRect(CMQLatLng &LLTarget, CMQLatLng &URTarget) const;
   // {secret}
   virtual void  PreSearch(CMQFeatureCollection& fcFound);
   // {secret}
   virtual unsigned long SelectFeature(CMQFeature* pFeature, CMQFeatureCollection& fcFound);
   // {secret}
   virtual bool  OkToContinue(CMQFeatureCollection& fcFound);

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   virtual unsigned long SelectLineFeature(CMQLatLngCollection &llColl);
   // {secret}
   virtual unsigned long SelectPtFeature(CMQLatLng &ll);
   // {secret}
   virtual unsigned long SelectPolyFeature(CMQLatLngCollection &llColl);

protected:
   // {secret}
   CMQLatLngCollection* m_llColl;
};


double MQ_GetDistanceFromPolyline(CMQLatLngCollection& llColl,      // (IN) Polyline
                                  CMQLatLng llTarget,               // (IN) Target point.
                                  CMQLatLng* pllNearest,            // (OUT) Nearest intersect point.
                                  int* pIndex);                     // (OUT) Index to closest arc.


/**
 * Criteria defining a corridor area to search.
 * @ingroup Mapquest
 */
class CMQCorridorSearchCriteria : public CMQSearchCriteria
{
public:
   /**
    * Constructor
    */
   CMQCorridorSearchCriteria();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQCorridorSearchCriteria(const CMQCorridorSearchCriteria& Object);

   /**
    * Destructor
    */
   virtual ~CMQCorridorSearchCriteria();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1230};
#else
   static const int   CLASS_ID = 1230;
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

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQCorridorSearchCriteria &operator=(const CMQCorridorSearchCriteria& Object);

   /**
    * Get the LatLng Collection of Shape points  representing the polygon to search.
    * @return CMQLatLngCollection of shape points.
    */
   CMQLatLngCollection &ShapePoints() { return (*m_llColl); }
   // {secret}
   CMQLatLngCollection &GenShapePoints() { return (*m_llCollGen); }
   // {secret}
   CMQLatLngCollection &llBRs() { return (*m_llBRs); }

   /**
    * Sets the width of corridor to search.
    * @param dCorrWidth width of corridor to search.
    * @param lUnits    the units type to return.
    * @see CMQDistanceUnits
    */
   void SetCorridorWidth(const double dCorrWidth, long lUnits = CMQDistanceUnits::MILES);
   /**
    * Gets the radius to search from the origin.
    * @param lUnits    the units type to return.
    * @return width of corridor to search.
    * @see CMQDistanceUnits
    */
   double GetCorridorWidth(long lUnits = CMQDistanceUnits::MILES) const;

   /**
    * Sets the width of corridor buffer to search.
    * @param dCorrBufferWidth width of corridor buffer to search.
    * @param lUnits    the units type to return.
    * @see CMQDistanceUnits
    */
   void SetCorridorBufferWidth(const double dCorrBufferWidth, long lUnits = CMQDistanceUnits::MILES);
   /**
    * Gets the width of corridor buffer to search.
    * @param lUnits    the units type to return.
    * @return width of corridor buffer to search.
    * @see CMQDistanceUnits
    */
   double GetCorridorBufferWidth(long lUnits = CMQDistanceUnits::MILES) const;

   /**
    * Sets the flag to disable/enable shape point generalization.
    * @param bCorrExactLinks    bool to represent this flag
    */
   void SetCorridorExactLinks( bool bCorrExactLinks ) { m_bCorrExactLinks = bCorrExactLinks; }
   /**
    * Gets the flag to disable/enable shape point generalization.
    * @return bool to represent this flag
    */
   bool GetCorridorExactLinks()      const { return m_bCorrExactLinks; }

   // {secret}
   virtual bool  OkToContinue(CMQFeatureCollection& fcFound);
   // {secret}
   virtual unsigned long SelectFeature(CMQFeature* pFeature, CMQFeatureCollection& fcFound);
   // {secret}
   virtual void  PreSearch(CMQFeatureCollection& fcFound);
   // {secret}
   virtual void  GetBoundingRect(CMQLatLng &LLTarget, CMQLatLng &URTarget) const;
   // {secret}
   bool GenerateCorridorRects();

   virtual void  PostSearch(CMQFeatureCollection& fcFound);
// Private data.
protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   enum { MIN_BUFFER_WIDTH          = 0,
         MAX_BUFFER_WIDTH          = 2,
         NUM_VERTICES_FOR_CORRIDOR = 5,
         MAXEL_NUMERIC             = 20,
         REAL_LONG_DISTANCE               = 1000000,
         NUM_ADJACENT_CHECKED_SEGMENTS    = 1};

   // {secret}
   void ConstructWideSegment( const CMQLatLng & dllPoint1,
                              const CMQLatLng & dllPoint2,
                              CMQLatLngCollection & llP);

   // {secret}
   class CMQFeatCompare
   {
   public:
      bool operator() (CMQFeature* pFeat1, CMQFeature* pFeat2)
      {
         return pFeat1->GetGEFID() < pFeat2->GetGEFID();
      };
   };

   // {secret}
   class CMQLatLngCollectionEx : public CMQLatLngCollection
   {
   public:
      unsigned long GetOriginalIndex(const unsigned long lIndex) const
      {
         if(m_pDerivedPoints)
            return m_pDerivedPoints[lIndex].ulOriginalPoint;
         else
            return 0;
      };
   };
   // {secret}
   double withinBuffer(CMQLatLng& llF, unsigned long& ulClosestOrigVertice);

   // {secret}
   virtual unsigned long SelectPtFeature(CMQLatLng &ll, double& dDistance, unsigned long& ulClosestOrigVertice);

   // {secret}
   CMQLatLngCollection* m_llColl;
   // {secret}
   CMQLatLngCollectionEx* m_llCollGen;
   // {secret}
   CMQLatLngCollection* m_llBRs;
   // {secret}
   double           m_dCorrWidth;
   // {secret}
   double           m_dCorrBufferWidth;
   // {secret}
   bool        m_bCorrExactLinks;
   // {secret}
   long         m_maxQueryLength;
   CMQDistanceApproximation m_da;

};

#endif   // _MQSRCHCRIT_H_



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
#ifndef _MQLATLNGCOLLECTION_H_
// {secret}
#define _MQLATLNGCOLLECTION_H_

#include "mqobject.h"
#include "latlng.h"
#include "objectcollection.h"

/**
 * Collection to hold CMQLatLng Objects
 * @see CMQObjectCollection
 * @ingroup Mapquest
 */
class CMQLatLngCollection : public CMQObjectCollection<CMQLatLng*>
{
public:
   /**
    * Constructor
    */
   CMQLatLngCollection();
   virtual ~CMQLatLngCollection();

   // {secret}
   virtual bool ValidObject(CMQObject* pObject);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1540};
#else
   static const int   CLASS_ID = 1540;
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
    * Returns lat/lng bounding rectangle of all points in the latlng
    * collection
    * @param UL UpperLeft
    * @param LR LowerRight
    * @return success
    */
   bool GetBoundingRect(CMQLatLng& UL, CMQLatLng& LR);
   /**
    * Expands the given lat/lng bounding rectangle, if necessary, to
    * encompass all points in the latlng collection.
    * @param UL UpperLeft
    * @param LR LowerRight
    * @return success
    */
   bool ExpandBoundingRect(CMQLatLng& UL, CMQLatLng& LR);

   /**
    * Calculate arc distance between all Lat/Lng pairs contained in this collection.
    * @param lUnits     the units type to return
    * @see CMQDistanceUnits
    * @return     the distance in the requested unit type
    */
   double ArcDistance(long lUnits = CMQDistanceUnits::MILES);

   /**
    * Adds an item to the collection created with the new values.
    * @param dLat  the Latitude of the new object
    * @param dLng  The Longitude of the new object
    */
   void AddLatLng(const double dLat, const double dLng);

   /**
    * Generalizes the collection by removing Lat/Lng's within the deviance.
    * @param dDeviance  the deviance
    */
   void Generalize(double dDeviance = 0.25);

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   struct SOrigPoint
   {
      CMQLatLng *pLL;     // Decimal position of the point.
      double dSegmentLength;      // Length of segment that begins here.
      double dPriorLength;        // Accum. length of prior segments.
   };

   struct SDerivedPoint
   {
      CMQLatLng *pLL;     // Decimal position of the point.
      unsigned long ulOriginalPoint;      // Number of original point.
   };

   SDerivedPoint* m_pDerivedPoints;
   CMQDistanceApproximation m_da;
   bool IsEverybodyWithinDeviation(const SOrigPoint* pOrigPoints,const unsigned long & ulOrigStartPoint,const unsigned long & ulOrigEndPoint,const double & dMaxDeviation);

   long m_lPrecision;
};

#endif   // _MQLATLNGCOLLECTION_H_



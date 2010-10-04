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
#ifndef MQLATLNG_H
// {secret}
#define MQLATLNG_H

#include "mqobject.h"


/**
 * Class to encapsulate the Lat/Long Object.
 * @ingroup Mapquest
 */
class CMQLatLng : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQLatLng()
   {
      Init();
   };
   /**
    * Constructor
    * @param aLatLng Object to copy
    */
   CMQLatLng(const CMQLatLng& aLatLng)
   {
      Init();
      *this = aLatLng;
   };
   /**
    * Constructor
    * @param aLatitude value for the Latitude
    * @param aLongitude value for the Longitude
    */
   CMQLatLng(const double aLatitude, const double aLongitude)
   {
      Init();
      SetLatLng(aLatitude, aLongitude);
   };
   /**
    * Destructor
    */
   virtual ~CMQLatLng() {};

   /**
    * Returns the Latitude value.
    * @return the latitude value
    */
   double GetLatitude() const
   {
      return latitude;
   };

   /**
    * Sets the Latitude value
    * @param aLatitude double value for the Latitude
    */
   void SetLatitude(const double aLatitude)
   {
      latitude = aLatitude;

      if (latitude >  90.0)
         latitude =  90.0;
      if (latitude < -90.0)
         latitude = -90.0;
   };

   /**
    * Returns the Longitude value
    * @return the longitude value
    */
   double GetLongitude() const
   {
      return longitude;
   };

   /**
    * Sets the Longitude value
    * @param aLongitude double value for the Longitude
    */
   void SetLongitude(const double aLongitude)
   {
      longitude = aLongitude;

      while (longitude >  180.0)
         longitude -= 360.0;
      while (longitude < -180.0)
         longitude += 360.0;
   };

   /**
    * Sets the Latitude and Longitude values
    * @param aLatitude value for the Latitude
    * @param aLongitude value for the Longitude
    */
   void  SetLatLng(const double aLatitude, const double aLongitude)
   {
      SetLatitude(aLatitude);
      SetLongitude(aLongitude);
   };

   /**
    * assignment operator
    * @param aLatLng Object to copy
    */
   CMQLatLng& operator=(const CMQLatLng& aLatLng)
   {
      latitude  = aLatLng.GetLatitude();
      longitude = aLatLng.GetLongitude();
      return *this;
   };

   /**
    * equality operator
    * @param aLatLng Object to compare
    */
   bool operator==(const CMQLatLng& aLatLng) const
   {
      double dNum = GetLatitude()  - aLatLng.GetLatitude();

      if (-0.000001 < dNum && dNum < 0.000001)
      {
         dNum = GetLongitude() - aLatLng.GetLongitude();
         if(-0.000001 < dNum && dNum < 0.000001)
            return true;
      }

      return false;
   };

   /**
    * inequality operator
    * @param aLatLng Object to compare
    */
   bool operator!=(const CMQLatLng& aLatLng) const
   {
      return !(*this == aLatLng);
   }

   /**
    * greater than or equal to operator
    * @param aLatLng Object to compare
    */
   bool operator>=(const CMQLatLng& aLatLng) const
   {
      return ( GetLatitude()  >= aLatLng.GetLatitude()   &&
               GetLongitude() >= aLatLng.GetLongitude()  );
   };

   /**
    * less than or equal to operator
    * @param aLatLng Object to compare
    */
   bool operator<=(const CMQLatLng& aLatLng) const
   {
      return ( GetLatitude() <= aLatLng.GetLatitude()    &&
               GetLongitude() <= aLatLng.GetLongitude()  );
   };

   /**
    * Boolean check for validity of all values
    */
   bool Valid() const
   {
      return ( fabs(latitude  - INVALID) > 0.000001 &&
               fabs(longitude - INVALID) > 0.000001 );
   };

   /**
    * Calculates the distance between two lat/lng's in miles or meters.
    *
    * @param   ll2   Second lat,lng position to calculate distance to.
    * @param   lUnits Units to calculate distace, defaults to miles
    *
    * @return  Returns the distance in meters or miles.
    */
   double ArcDistance(const CMQLatLng& ll2,
                      long lUnits = CMQDistanceUnits::MILES) const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init()
   {
      CMQObject::Init();

      latitude  = INVALID;
      longitude = INVALID;
   };

   const static double INVALID;     /**< value of an invalid Lat/Lng */

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1700};
#else
   static const int   CLASS_ID = 1700;
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
   double latitude;
   // {secret}
   double longitude;
};

#endif   // MQLATLNG_H



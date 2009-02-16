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
#ifndef _MQDISTANCEAPPROXIMATION_H
// {secret}
#define _MQDISTANCEAPPROXIMATION_H

class CMQDistanceApproximation
{
public:
   CMQDistanceApproximation();
   virtual ~CMQDistanceApproximation();

   const static double MILES_PER_LATITUDE;
   const static double KILOMETERS_PER_MILE;
   const static double m_milesPerLngDeg[91];

   void SetTestPoint(const double lat, const double lng);

   // Approximate arc distance between 2 lat,lng positions using miles per
   //    latitude and longitude degree
   double GetDistanceSq(const double lat, const double lng) const;

   // Approximate arc distance between a segment (with lat,lng endpoints) and
   //    the test position
   double GetDistanceSq(const double lat1, const double lng1,
                        const double lat2, const double lng2) const;

   // Return the number of miles per degree of longitude
   double GetMilesPerLngDeg(const double lat);

private:
   double m_testLat;
   double m_testLng;
   double m_mpd;
};

#endif   // _MQDISTANCEAPPROXIMATION_H

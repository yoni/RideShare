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
#ifndef _MQTREKROUTE_H_
// {secret}
#define _MQTREKROUTE_H_

#include "mqobject.h"
#include "maneuvercollection.h"

/**
 * This object represents 1 leg of the RouteResults.
 * @ingroup Mapquest
 */
class CMQTrekRoute : public CMQObject
{
public:
   /**
    * Constructor.
    */
   CMQTrekRoute();
   /**
    * Constructor.
    * @param src Object to copy
    */
   CMQTrekRoute(const CMQTrekRoute &src);

   /**
    * Destructor.
    */
   virtual ~CMQTrekRoute();

   /**
    * assignment operator
    * @param src Object to copy
    */
   CMQTrekRoute& operator=(const CMQTrekRoute& src);

   /** Fills a CMQManeuverCollection with this object's Maneuver List.
    *  @param ppmlist double referenced pointer to the Collection to be filled
    */
   void GetManeuvers(CMQManeuverCollection** ppmlist);
   /** Returns a reference to a CMQManeuverCollection with this object's Maneuver List.
    *  @return  a reference to the internal maneuver collection.
    */
   CMQManeuverCollection& GetManeuvers() {return (*maneuverList);}

   /** Returns the distance of the route.
    */
   double GetDistance();

   /** Returns the estimated time in seconds to drive this leg of the route.
    */
   long GetTime();

   /**
    * Returns all shape points from each maneuver in this leg of the route.
    */
   CMQLatLngCollection& GetShapePoints();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1620};
#else
   static const int   CLASS_ID = 1620;
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

private:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQManeuverCollection* maneuverList;

   // {secret}
   double                  m_dDistance;
   // {secret}
   long                    m_lTime;
   // {secret}
   CMQLatLngCollection*    m_ShapePnts;
};

#endif   // _MQTREKROUTE_H_



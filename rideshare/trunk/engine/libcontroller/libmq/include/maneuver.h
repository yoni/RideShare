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
#ifndef _MQMANEUVER_H_
// {secret}
#define _MQMANEUVER_H_

#include "mqobject.h"
#include "latlngcollection.h"
#include "intcollection.h"
#include "signcollection.h"
#include "stringcollection.h"

/**
 * This object will hold each maneuver of a trekroute returned from a route
 * @ingroup Mapquest
 */
class CMQManeuver : public CMQObject
{
public:
#ifdef _MQ_DEPRECATED_
   static const int NULL_HEADING;             /**< @deprecated use HEADING_NULL */
   static const int NORTH_HEADING;            /**< @deprecated use HEADING_NORTH */
   static const int NORTH_WEST_HEADING;       /**< @deprecated use HEADING_NORTH_WEST */
   static const int NORTH_EAST_HEADING;       /**< @deprecated use HEADING_NORTH_EAST */
   static const int SOUTH_HEADING;            /**< @deprecated use HEADING_SOUTH */
   static const int SOUTH_EAST_HEADING;       /**< @deprecated use HEADING_SOUTH_EAST */
   static const int SOUTH_WEST_HEADING;       /**< @deprecated use HEADING_SOUTH_WEST */
   static const int WEST_HEADING;             /**< @deprecated use HEADING_WEST */
   static const int EAST_HEADING;             /**< @deprecated use HEADING_EAST */
#endif
   static const int HEADING_NULL;             /**< Directions: Null */
   static const int HEADING_NORTH;            /**< Directions: North */
   static const int HEADING_NORTH_WEST;       /**< Directions: North West */
   static const int HEADING_NORTH_EAST;       /**< Directions: North East */
   static const int HEADING_SOUTH;            /**< Directions: South */
   static const int HEADING_SOUTH_EAST;       /**< Directions: South East */
   static const int HEADING_SOUTH_WEST;       /**< Directions: South West */
   static const int HEADING_WEST;             /**< Directions: West */
   static const int HEADING_EAST;             /**< Directions: East */

   static const int TURN_TYPE_STRAIGHT;       /**< TurnType: straight */
   static const int TURN_TYPE_SLIGHT_RIGHT;   /**< TurnType: slight right */
   static const int TURN_TYPE_RIGHT;          /**< TurnType: right */
   static const int TURN_TYPE_SHARP_RIGHT;    /**< TurnType: sharp right */
   static const int TURN_TYPE_REVERSE;        /**< TurnType: reverse */
   static const int TURN_TYPE_SHARP_LEFT;     /**< TurnType: sharp left */
   static const int TURN_TYPE_LEFT;           /**< TurnType: left */
   static const int TURN_TYPE_SLIGHT_LEFT;    /**< TurnType: slight left */
   static const int TURN_TYPE_RIGHT_UTURN;    /**< TurnType: right u-turn */
   static const int TURN_TYPE_LEFT_UTURN;     /**< TurnType: left u-turn */
   static const int TURN_TYPE_RIGHT_MERGE;    /**< TurnType: right merge */
   static const int TURN_TYPE_LEFT_MERGE;     /**< TurnType: left merge */
   static const int TURN_TYPE_RIGHT_ON_RAMP;  /**< TurnType: right on ramp */
   static const int TURN_TYPE_LEFT_ON_RAMP;   /**< TurnType: left on ramp */
   static const int TURN_TYPE_RIGHT_OFF_RAMP; /**< TurnType: right off ramp */
   static const int TURN_TYPE_LEFT_OFF_RAMP;  /**< TurnType: left off ramp */
   static const int TURN_TYPE_RIGHT_FORK;     /**< TurnType: right fork */
   static const int TURN_TYPE_LEFT_FORK;      /**< TurnType: left fork */
   static const int TURN_TYPE_STRAIGHT_FORK;  /**< TurnType: straight fork */

   /// Attribute: portions toll
   static const int ATTRIBUTE_PORTIONS_TOLL;

   /// Attribute: portions unpaved
   static const int ATTRIBUTE_PORTIONS_UNPAVED;

   /// Attribute: possible seasonal road closure
   static const int ATTRIBUTE_POSSIBLE_SEASONAL_ROAD_CLOSURE;

   /// Attribute: gate
   static const int ATTRIBUTE_GATE;

   /// Attribute: ferry
   static const int ATTRIBUTE_FERRY;


public:
   /**
    * Constructor
    */
   CMQManeuver();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQManeuver(const CMQManeuver& Object);
   /**
    * Destructor
    */
   virtual ~CMQManeuver();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQManeuver& operator=(const CMQManeuver& Object);

   /**
    * Get the turn type.
    * @return  Turn Types
    */
   long GetTurnType() const;
   /**
    * Set the turn type.
    * @param type  Turn Types
    */
   void SetTurnType(long type);

   /**
    * Get the distance.
    * @return  the distance
    */
   double GetDistance() const;
   /**
    * Set the distance.
    * @param dDistance the distance of the maneuver
    */
   void SetDistance(double dDistance);

   /**
    * Get the approximate time in seconds to drive the maneuver
    * @return the time in seconds
    */
   long GetTime() const;
   /**
    * Set the approximate time in seconds to drive the maneuver
    * @param seconds the time in seconds
    */
   void SetTime(long seconds);

   /**
    * Get the direction
    * @return the direction constant
    */
   long GetDirection() const;
   /**
    * Set the direction constant.
    * @param lDirection  the direction constant
    */
   void SetDirection(long lDirection);
   /**
    * Gets the direction in string form
    * return string representation of direction
    */
   const char* GetDirectionName() const;

   /**
    * Get the street name list.
    * @return the street name list.
    */
   CMQStringCollection& GetStreets();

   /**
    * Get the narrative
    * @return the string narrative line for this maneuver
    */
   const CMQString& GetNarrative() const;
   /**
    * Set the narrative
    * @param szNarrative the string narrative line for this maneuver
    */
   void SetNarrative(const char* szNarrative);

   /**
    * Get the Lat/Lngs representing this maneuver.
    * @return the shape of this maneuver
    */
   CMQLatLngCollection& GetShapePoints();

   /**
    * Get the GEFIDs representing this maneuver
    * @return the GEFIDs of the links included in this maneuver
    */
   CMQIntCollection& GetGEFIDs();

   /**
    * Get the User Data Pointer.
    * @return a pointer to a user assigned block of data
    */
   void* GetUserData();
   /**
    * Set the User Data Pointer
    * Allows the User to add information to this object.  This information is not serialized
    * or used by the server.  The user is responsible for creating and freeing this any memory stored here.
    * @param pUserData a pointer to some block of data the User may want to associate with this maneuver
    */
   void SetUserData(void* pUserData);

   /**
    * Get the attributes associated with this maneuver.
    * @return or'ed list of attributes associated with this maneuver.
    */
   long GetAttributes() const;
   /**
    * Set the attributes associated with this maneuver.
    * @param  attributes  an or'ed list of attributes associated with this
    *                     maneuver.
    */
   void SetAttributes(long attributes);

   /**
    * Get the Signs present in this maneuver.
    * @return the Signs included in this maneuver.
    */
   CMQSignCollection& GetSigns();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1600};
#else
   static const int   CLASS_ID = 1600;
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
   CMQString m_strNarrative;
   // {secret}
   CMQStringCollection* m_Streets;
   // {secret}
   long m_lTurnType;
   // {secret}
   double m_dDistance;
   // {secret}
   long m_lTime;
   // {secret}
   long m_lDirection;
   // {secret}
   CMQLatLngCollection* m_ShapePoints;
   // {secret}
   CMQIntCollection* m_GEFIds;
   // {secret}
   void* m_pUserData;
   // {secret}
   long m_lAttributes;
   // {secret}
   CMQSignCollection* m_Signs;
};

#endif   // _MQMANEUVER_H_



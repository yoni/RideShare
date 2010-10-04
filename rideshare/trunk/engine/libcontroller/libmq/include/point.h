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
#ifndef __CMQPOINT__
// {secret}
#define __CMQPOINT__

#include "mqobject.h"

/**
 * This class represents a point.
 * @ingroup Mapquest
 */
class CMQPoint : public CMQObject
{
public:
   /**
    * Constructor.
    */
   CMQPoint();
   /**
    * Constructor.
    * @param nX long value for the x coordinate
    * @param nY long value for the y coordinate
    */
   CMQPoint(const long nX, const long nY);
   /**
    * Copy constructor.
    * @param point CMQPoint& constant source point to copy from
    */
   CMQPoint(const CMQPoint &point);
   /**
    * Destructor.
    */
   virtual ~CMQPoint();

   /**
    * assignment operator.
    * @param point CMQPoint& constant source point to copy from
    */
   CMQPoint& operator=(const CMQPoint& point);
   /**
    * equality operator.
    * @param point CMQPoint& constant source to compare to
    */
   bool operator==(const CMQPoint& point) const;

   /**
    * Set the values for this object.
    * @param nX long value for the x coordinate
    * @param nY long value for the y coordinate
    */
   void SetXY(const long nX, const long nY);

   /**
    * Sets the x coordinate value.
    * @param sX long value for the x coordinate
    */
   void SetX(const long sX);
   /**
    * Sets the y coordinate value.
    * @param sY long value for the y coordinate
    */
   void SetY(const long sY);
   /**
    * Get the x coordinate.
    * @return x coordinate as a long integer
    */
   long GetX() const;
   /**
    * Get the y coordinate.
    * @return y coordinate as a long integer
    */
   long GetY() const;

   /**
    * Boolean check for validity of all values.
    */
   bool Valid() const;

   /**
    * default value of an invalid X/Y coordinate.
    * @ingroup Constants
    */
   const static long INVALID;

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1701};
#else
   static const int   CLASS_ID = 1701;
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
   long m_x;
   // {secret}
   long m_y;
};

#endif



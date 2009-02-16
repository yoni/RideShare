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
#ifndef _MQIDENTIFYCRITERIA_H_
// {secret}
#define _MQIDENTIFYCRITERIA_H_

#include "mqobject.h"
#include "point.h"

/**
 * describes how many features should be returned for the Identify method.
 * @ingroup Mapquest
 */
class CMQIdentifyCriteria : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQIdentifyCriteria();
   CMQIdentifyCriteria( const CMQIdentifyCriteria &IdentifyCriteria );

   /**
    * Destructor
    */
   virtual ~CMQIdentifyCriteria();

   CMQIdentifyCriteria& operator=( const CMQIdentifyCriteria &IdentifyCriteria );
   bool operator==( const CMQIdentifyCriteria &IdentifyCriteria );
   bool operator!=( const CMQIdentifyCriteria &IdentifyCriteria );

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1300};
#else
   static const int   CLASS_ID = 1300;
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
    * origin to search from.
    * @param pt Display Point Object that specifies the origin location
    */
   void              SetCenter(const CMQPoint& pt)  { (*m_CenterPoint) = pt; }
   /**
    * origin to search from.
    * @return Point Object that specifies the origin location
    */
   CMQPoint&   GetCenter() { return (*m_CenterPoint); }
   /**
    * radius to search from the origin.
    * @param nRadius radius to search from the origin
    */
   void              SetRadius( int nRadius ) { m_nRadius = nRadius; }
   /**
    * radius to search from the origin.
    * @return radius to search from the origin
    */
   int               GetRadius()  const { return m_nRadius; }
   /**
    * Set the maximum number of features to search for.
    * @param lMaxMatches   the maximum number of features to search for
    */
   void              SetMaxMatches(long lMaxMatches)  { m_lMaxMatches = lMaxMatches; }
   /**
    * Get the maximum number of features to search for.
    * @return    the maximum number of features to search for
    */
   long              GetMaxMatches() const { return m_lMaxMatches; }


protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQPoint* m_CenterPoint;
   // {secret}
   int      m_nRadius;
   // {secret}
   long    m_lMaxMatches; /// maximum number of matches to return
};

#endif   // _MQIDENTIFYCRITERIA_H_



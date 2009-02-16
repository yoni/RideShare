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
#ifndef _MQAUTOGEOCODECOVSWITCH_H_
// {secret}
#define _MQAUTOGEOCODECOVSWITCH_H_

#include "mqobject.h"

/**
 * Stores geocode coverage switching parameters.
 * @ingroup Mapquest
 */
class CMQAutoGeocodeCovSwitch : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQAutoGeocodeCovSwitch();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQAutoGeocodeCovSwitch& operator=(const CMQAutoGeocodeCovSwitch& Object);

   /**
    * Destructor
    */
   virtual ~CMQAutoGeocodeCovSwitch();

   /**
    * Sets the name of the coverage switching rules to use.  Names of
    * coverage switching rules are defined in the mqserver.ini file.
    * @param szName Name of coverage switching rules to use.
    */
   void              SetName(const char* szName);
   /**
    * Gets the name of the coverage switching rules being used.
    * @return Name
    */
   const CMQString&  GetName() const;

   /**
    * Sets the maximum number of matches to return, in case the address is
    * ambiguous and multiple matches are possible.
    *
    * @param lMaxMatches The maximum number of matches to return.
    */
   void SetMaxMatches(long lMaxMatches);
   /**
    * Gets the maximum number of matches to return.
    *
    * @return The maximum number of matches to return
    */
   long GetMaxMatches() const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1132};
#else
   static const int   CLASS_ID = 1132;
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
   CMQString     m_strName;
   // {secret}
   long          m_lMaxMatches;
};

#endif   // _MQAUTOGEOCODECOVSWITCH_H_



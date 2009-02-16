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
#ifndef _MQGEOCODEOPTIONS_H_
// {secret}
#define _MQGEOCODEOPTIONS_H_

#include "mqobject.h"
#include "cstring.h"

/**
 * Class for specifying geocode parameters.
 * @ingroup Mapquest
 */
class CMQGeocodeOptions : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQGeocodeOptions();
   /**
    * Destructor
    */
   virtual ~CMQGeocodeOptions() {};

   /**
    * Sets the type of geocoding to perform
    *
    * @param type  The type of geocode to perform
    * @see CMQMatchType
    */
   void SetMatchType(long type);
   /**
    * Gets the match type.
    * @see CMQMatchType
    */
   long GetMatchType() const;
   /**
    * Sets the desired quality of the results returned by the geocoder
    *
    * @param type The desired quality of the results returned by the geocoder
    * @see CMQQualityType
    */
   void SetQualityType(long type);
   /**
    * Gets the desired quality of the results returned by the geocoder
    *
    * @return The desired quality of the results returned by the geocoder
    * @see CMQQualityType
    */
   long GetQualityType() const;
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
    * Sets the name of the coverage that this option applies to.
    *
    * @param szCoverageName The name of the coverage
    */
   void SetCoverageName(const char* szCoverageName);
   /**
    * Gets the name of the coverage that this option applies to.
    *
    * @return The name of the coverage that these options apply to
    */
   const CMQString& GetCoverageName() const;
   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1130};
#else
   static const int   CLASS_ID = 1130;
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
   long          m_lQualityType;
   // {secret}
   long          m_lMaxMatches;
   // {secret}
   long          m_lMatchType;
   // {secret}
   CMQString     m_strCoverageName;
};

#endif   // _MQGEOCODEOPTIONS_H_



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
#ifndef _MQDISPLAYSTATE_H_
// {secret}
#define _MQDISPLAYSTATE_H_

#include "mqobject.h"
/**
 * Class needed to request the output format of a map
 * @ingroup Mapquest
 * @see CMQContentType
 */
class CMQDisplayState : public CMQObject
{
public:
#ifdef _MQ_DEPRECATED_
   static long const mqContentTypeGIF;    /**< @deprecated use CMQContentType::GIF*/
   static long const mqContentTypeEPS;    /**< @deprecated use CMQContentType::EPS*/
   static long const mqContentTypeAIEPS;  /**< @deprecated use CMQContentType::AIEPS*/
   static long const mqContentTypePNG;    /**< @deprecated use CMQContentType::PNG*/
   static long const mqContentTypeWBMP;   /**< @deprecated use CMQContentType::WBMP*/
#endif
   /**
    * Constructor
    */
   CMQDisplayState();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQDisplayState(const CMQDisplayState& Object);

   /**
    * Destructor
    */
   virtual ~CMQDisplayState();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQDisplayState& operator=(const CMQDisplayState& Object);

   /**
    * Sets the content type.
    * @param contentType  The content type. to be return see constants of this class for available types
    * @see CMQContentType
    */
   void SetContentType(const long contentType);
   /**
    * Gets the content type.
    * @return The content type
    * @see CMQContentType
    */
   long GetContentType() const;
   /**
    * Sets the DPI used to draw the map (Default=72).
    * @param newDPI the DPI to be used when creating this map
    */
   void SetDPI(long newDPI);
   /**
    * Gets the DPI used to draw the map.
    * @return the DPI to be used when creating this map
    */
   long GetDPI() const;
   /**
    * Sets anti-alias flag, for use with PNG and GIF
    * default is on or true
    * @param bAA the anti-alias flag
    */
   void SetAntiAlias(bool bAA);
   /**
    * Gets the anti-alias flag
    * @return bAA the anti-alias flag
    */
   bool GetAntiAlias() const;
   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1650};
#else
   static const int   CLASS_ID = 1650;
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
   long m_ContentType;
   // {secret}
   long m_DPI;
   // {secret}
   bool m_bAA;
};

#endif   // _MQDISPLAYSTATE_H_



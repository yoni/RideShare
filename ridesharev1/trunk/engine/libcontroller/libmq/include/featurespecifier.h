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
#ifndef _MQFEATURESPECIFIER_H_
// {secret}
#define _MQFEATURESPECIFIER_H_

#include "mqobject.h"

/**
 * Class to define attribute and value pairs of specific features to be drawn differently.
 * @see CMQFeatureSpeciferAttributeType
 * @see CMQFeatureSpecifierCollection
 * @see CMQDTFeatureStyleEx
 * @see CMQCoverageStyle
 * @ingroup Mapquest
 */
class CMQFeatureSpecifier : public CMQObject
{
protected:
   // {secret}
   long              m_lType;
   // {secret}
   CMQString         m_strValue;

public:
   /**
    * Constructor
    */
   CMQFeatureSpecifier();
   /**
    * Destructor
    */
   virtual ~CMQFeatureSpecifier();
   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Set the Attribute Type to match this feature on.
    * @param lType   the Attribute Type of this feature specifier
    */
   void              SetAttributeType(const long lType);
   /**
    * Get the Attribute Type to match this feature on.
    * @return    the Attribute Type of this feature specifier
    */
   const long&       GetAttributeType() const;

   /**
    * Set the Value of the Attribute Type to be matched on.
    * @param szValue   the Attribute Value
    */
   void              SetAttributeValue(const char*  szValue);
   /**
    * Get the Value of the Attribute Type to be matched on.
    * @return    the Attribute Value
    */
   const CMQString&  GetAttributeValue() const;

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1653};
#else
   static const int   CLASS_ID = 1653;
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
};

#endif   // _MQFEATURESPECIFIER_H_



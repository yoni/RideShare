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
#ifndef _MQOBJECT_H_
// {secret}
#define _MQOBJECT_H_

// This tag defines all deprecated methods, undef it to build with all deprecated methods removed
// enable after code updates for final linking
#define _MQ_DEPRECATED_

#include <mqosutil.h>

#include "mqconstants.h"

/**
 * Base class for all MapQuest objects.  Not Createable.
 * @ingroup Mapquest
 */
class CMQObject : public IMQUnknown
{
protected:
   /**
    * Constructor
    */
   CMQObject();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQObject(const CMQObject& Object);
public:
   /**
    * Destructor
    */
   virtual ~CMQObject();
   /**
    * assignment operator.
    * @param Object Object to copy
    */
   CMQObject& operator=(const CMQObject& Object);

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Return the text name of this class.  Implemented by all derived classes.
    * @return Text name of the this object.
    */
   virtual const char* GetClassName() const = 0;
   /**
    * Return the numeric id of this class.  Implemented by all derived classes.
    * @return numeric id of this object.
    */
   virtual int         GetClassId()   const = 0;

#ifdef _MQ_DEPRECATED_
   /**
    * @deprecated  Use GetClassName
    * @see GetClassName
    */
   const char* GetTypeName() const { return GetClassName(); };
   /**
    * @deprecated  Use GetClassId
    * @see GetClassId
    */
   int         GetTypeId()   const { return GetClassId();   };
#endif

   // {secret}
   long            GetObjectVersion() const         { return m_lVersion;    };
   // {secret}
   void            SetObjectVersion(long lVersion)  { m_lVersion = lVersion;};


   // {secret}
   virtual void LoadMe(CMQIO& io, long lVersion = -1);
   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const;

   // {secret}
           void LoadXML(const char* szTag, CMQXMLFormatter& io, long lVersion = -1, bool bOptional = false);
   // {secret}
           void SaveXML(const char* szTag, CMQXMLFormatter& io, bool bSaveClassType = true) const;

   // {secret}
           void SaveJSON(const char* szTag, CMQJSONFormatter& io, bool bSaveClassType = true) const;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1) {};
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const {};
   // {secret}
   virtual void WriteStartObjectXML(const char* szTag, CMQXMLFormatter& io) const;
   // {secret}
   virtual void WriteEndObjectXML(const char* szTag, CMQXMLFormatter& io) const;

   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const {};
   // {secret}
   virtual void WriteStartObjectJSON(const char* szTag, CMQJSONFormatter& io) const;
   // {secret}
   virtual void WriteEndObjectJSON(const char* szTag, CMQJSONFormatter& io) const;

   // {secret}
   virtual void CopyMemberData(const CMQObject* pObj);

   // {secret}
   long         m_lVersion;
};

#endif   // _MQOBJECT_H_



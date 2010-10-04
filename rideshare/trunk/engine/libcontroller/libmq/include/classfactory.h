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
#ifndef _MQCLASSFACTORY_H_
// {secret}
#define _MQCLASSFACTORY_H_

#include "mqobject.h"

class CMQClassFactory
{
public:
   CMQClassFactory();
   virtual ~CMQClassFactory() { }

   virtual char   GetClassTypeForm() { return m_cClassTypeForm; }
   virtual void   SetClassTypeForm(char cNumOrText = MQ_TEXT)  { m_cClassTypeForm = cNumOrText; }

   virtual CMQObject* CreateObject(int nID,                long lVersion = -1);
   virtual CMQObject* CreateObject(const char* szTypeName, long lVersion = -1);
   virtual CMQObject* CreateObject(const CMQClassType& aClassType);
   virtual CMQObject* CreateObject(CMQIO& io);
   virtual CMQObject* CreateObject(CMQXMLFormatter& io);

   virtual void   SaveObject(CMQIO& io, CMQObject& aMQObject, bool bSaveClassType = true);
   virtual void   SaveObject(CMQJSONFormatter& io, CMQObject& aMQObject, bool bSaveClassType = true);
   virtual void   SaveObject(CMQXMLFormatter& io, CMQObject& aMQObject, bool bSaveClassType = true);

   virtual void   WriteClassType(CMQIO& io, const CMQClassType& aClassType);

   virtual CMQClassType ReadClassType(CMQIO& io);

   virtual int    Encase(const char *pStr, int nLen);

protected:
   char           m_cClassTypeForm;
};

#endif   // _MQCLASSFACTORY_H_



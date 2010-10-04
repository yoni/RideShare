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
#ifndef _IMQUNKNOWN_H_
// {secret}
#define _IMQUNKNOWN_H_


////////////////////////////////////////////////////////////////////////////////
// IUnknown
class CMQString;

class IMQUnknown
{
public:
   IMQUnknown();
   virtual ~IMQUnknown();

// virtual unsigned long QueryInterface(REFIID riid, void** ppv) { return 0L; };

   virtual unsigned long AddRef();
   virtual unsigned long Release();

   static bool& UseRefCnt();

   CMQString* GetUUID();
   void SetUUID(CMQString* newuuid);

protected:
   int m_ulRefCnt;
   static bool bUseRefCnt;
   CMQString *uuid;
};

#endif

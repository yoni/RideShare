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
#ifndef _CRITICALSECTION_H_
// {secret}
#define _CRITICALSECTION_H_

#ifdef MQWIN32
#include "windows.h"
#elif MQUNIX
#include "mtq.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// CMQCriticalSection

class CMQCriticalSection
{
public:
   CMQCriticalSection();
   ~CMQCriticalSection();

   void Enter();
   void Leave();

protected:
#ifdef MQWIN32
   CRITICAL_SECTION cs;
#elif MQUNIX
   pthread_mutex_t  cs;
#endif
};


////////////////////////////////////////////////////////////////////////////////
// CMQSemaphore

class CMQSemaphore
{
public:
   CMQSemaphore();
   ~CMQSemaphore();

   void Initialize(unsigned int nItems);
   void Uninitialize();
   bool Acquire(long lTimeout);
   void Release();

protected:
#ifdef MQWIN32
   HANDLE            m_Semaphore;
#elif MQUNIX
   CMQMtQueue<int>   *m_Semaphore;
#endif
};

#endif   // _CRITICALSECTION_H_

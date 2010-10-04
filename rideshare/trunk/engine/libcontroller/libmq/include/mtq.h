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
#ifndef ___MTQ_H
// {secret}
#define ___MTQ_H

#include <queue>

#ifdef MQWIN32
// Implementation uses semaphores.  Do not change to
// use PulseEvent() or SetEvent(), since these are
// proven to be unreliable on the windows platform.

template<class TYPE>
class CMQMtQueue
{
public:
   CMQMtQueue<TYPE>()
   {
      InitializeCriticalSection(&m_mutex);
      m_available = CreateSemaphore( 0, 0, LONG_MAX, 0 );
      m_shutdown = 0;
   }
   virtual ~CMQMtQueue<TYPE>()
   {
      DeleteCriticalSection(&m_mutex);
      CloseHandle(m_available);
   }

   TYPE Pop();
   TYPE Pop(long timeout_msec);
   int  Push(TYPE);
   int  Size();
   int  Shutdown();

protected:
   CRITICAL_SECTION  m_mutex;
   HANDLE            m_available;
   std::queue<TYPE>  m_queue;
   int               m_shutdown;

private:
   CMQMtQueue(const CMQMtQueue& copy){}
   CMQMtQueue& operator=(const CMQMtQueue& copy){}
};

template<class TYPE>
TYPE CMQMtQueue<TYPE>::Pop()
{
   // Wait for signal from pusher for up to timeout_msec
   WaitForSingleObject(m_available, INFINITE);

   // If shutting down, propogate signal and return NULL
   if (m_shutdown)
   {
      ReleaseSemaphore (m_available, 1, 0);
      return 0;
   }

   // Lock the queue
   EnterCriticalSection(&m_mutex);

   // Get and pop queue front if queue not empty
   TYPE p = NULL;
   if (m_queue.empty() == false)
   {
      p = m_queue.front();
      m_queue.pop();
   }

   // Unlock the queue
   LeaveCriticalSection(&m_mutex);

   // Return item
   return p;
}

template<class TYPE>
TYPE CMQMtQueue<TYPE>::Pop(long timeout_msec)
{
   // Wait for signal from pusher for up to timeout_msec
   WaitForSingleObject(m_available, timeout_msec);

   // If shutting down, propogate signal and return NULL
   if (m_shutdown)
   {
      ReleaseSemaphore (m_available, 1, 0);
      return 0;
   }

   // Lock the queue
   EnterCriticalSection(&m_mutex);

   // Get and pop front if queue not empty
   TYPE p = NULL;
   if (m_queue.empty() == false)
   {
      p = m_queue.front();
      m_queue.pop();
   }

   // Unlock the queue
   LeaveCriticalSection(&m_mutex);

   // Return item
   return p;
}

template<class TYPE>
int CMQMtQueue<TYPE>::Push(TYPE p)
{
   int rc;

   // Lock the queue
   EnterCriticalSection(&m_mutex);

   // Enqueue if not shutting down
   if (!m_shutdown)
   {
      m_queue.push(p);
      rc = 1;
   }
   else
   {
      rc = 0;
   }

   // Release the queue
   LeaveCriticalSection(&m_mutex);

   // Signal queue entry to waiting threads
   ReleaseSemaphore (m_available, 1, 0);

   // Return 1 for enqueud, 0 otherwise
   return rc;
}

template<class TYPE>
int CMQMtQueue<TYPE>::Shutdown()
{
   // Shutting down
   m_shutdown = 1;

   // Signal waiting threads
   ReleaseSemaphore (m_available, 1, 0);

   // Return
   return 1;
}

template<class TYPE>
int CMQMtQueue<TYPE>::Size()
{
   return m_queue.size();
}


#elif MQUNIX

#include <pthread.h>
#include <errno.h>

template<class TYPE>
class CMQMtQueue
{
public:
   CMQMtQueue<TYPE>();
   virtual ~CMQMtQueue<TYPE>();

   TYPE Pop();
   TYPE Pop(long timeout_msec, bool* pbTimedOut = NULL);
   int  Push(TYPE);
   int  Size();
   int  Shutdown();

protected:
   pthread_mutex_t  m_mutex;
   pthread_cond_t   m_available;
   std::queue<TYPE> m_queue;
   int              m_shutdown;

private:
    CMQMtQueue(const CMQMtQueue& copy);
    CMQMtQueue& operator=(const CMQMtQueue& copy);
};

template<class TYPE>
CMQMtQueue<TYPE>::CMQMtQueue()
{
   pthread_mutex_init(&m_mutex, NULL);
   pthread_cond_init(&m_available, NULL);

   m_shutdown = 0;
}

template<class TYPE>
CMQMtQueue<TYPE>::~CMQMtQueue()
{
   pthread_mutex_destroy(&m_mutex);
   pthread_cond_destroy(&m_available);
}

template<class TYPE>
TYPE CMQMtQueue<TYPE>::Pop()
{
   if (0 != pthread_mutex_lock(&m_mutex))
      return 0;

   while (m_queue.empty() == true && !m_shutdown)
      if (0 != pthread_cond_wait(&m_available, &m_mutex))
      {
         pthread_mutex_unlock(&m_mutex);
         return 0;
      }

   TYPE p = NULL;
   if (m_queue.empty() == false)
   {
      p = m_queue.front();
      m_queue.pop();
   }

   pthread_mutex_unlock(&m_mutex);
   return p;
}

template<class TYPE>
TYPE CMQMtQueue<TYPE>::Pop(long timeout_msec, bool* pbTimedOut)
{
   // Get current time
   time_t ct;
   time(&ct);

   // always a multiple of 1000 because defined as seconds
   const struct timespec ts={ ct+(timeout_msec/1000),    //tv_sec, time in seconds
                              0 };                    //tv_nsec, time in nanoseconds

   if (0 != pthread_mutex_lock(&m_mutex))
      return 0;

   while (m_queue.empty() == true && !m_shutdown)
   {
      int rc=0;
      if ((rc = pthread_cond_timedwait(&m_available, &m_mutex, &ts)) != 0)
      {
         pthread_mutex_unlock(&m_mutex);
         if(rc == ETIMEDOUT && pbTimedOut)
         {
            *pbTimedOut = true;
         }
         return 0;
      }
   }

   TYPE p = 0;
   if (m_queue.empty() == false)
   {
      p = m_queue.front();
      m_queue.pop();
   }

   pthread_mutex_unlock(&m_mutex);
   return p;
}

template<class TYPE>
int CMQMtQueue<TYPE>::Push(TYPE p)
{
   if (0 != pthread_mutex_lock(&m_mutex))
      return 0;

   int rc;

   if (!m_shutdown)
   {
      m_queue.push(p);
      rc = 1;
   }
   else
      rc = 0;

   pthread_cond_signal(&m_available);
   pthread_mutex_unlock(&m_mutex);

   return rc;
}

template<class TYPE>
int CMQMtQueue<TYPE>::Shutdown()
{
   if (0 != pthread_mutex_lock(&m_mutex))
      return 0;

   m_shutdown = 1;

   pthread_cond_broadcast(&m_available);
   pthread_mutex_unlock(&m_mutex);

   return 1;
}

template<class TYPE>
int CMQMtQueue<TYPE>::Size()
{
   return m_queue.size();
}

#endif   // MQUNIX


#endif   // __MTQ_H



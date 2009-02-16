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
#ifndef __CMQHTTPEXCEPTION__
// {secret}
#define __CMQHTTPEXCEPTION__

#include "exception.h"

/*
 * thrown when bad requests are made to the server
 * the status string contains the server code and the content has the specific error text
 * @ingroup Mapquest
 */
class CMQHTTPException : public CMQException
{
public:
   /**
    * Constructors
    */
   CMQHTTPException();
   /**
    * Constructors
    * @param szStatus the status code
    */
   CMQHTTPException(const char* szStatus);
   /**
    * Constructors
    * @param szStatus the status code
    * @param szContent A description of the exception
    */
   CMQHTTPException(const char* szStatus, const char* szContent);

   /**
    * Set the composite error string
    * @param szException   the composite error string
    */
   virtual void SetExceptionString(const char* szException);
   /**
    * Get the composite error string
    * @return    the composite error string
    */
   virtual const CMQString& GetExceptionString() const;

   /**
    * Set the status code
    * @param szStatus   the status code
    */
   void SetStatusString(const char* szStatus);
   /**
    * Get the status code
    * @return    the status code
    */
   const CMQString& GetStatusString() const;

   /**
    * Set the content of the error
    * @param szContent   the content of the error
    */
   void SetContentString(const char* szContent);
   /**
    * Get the content of the error
    * @return    the content of the error
    */
   const CMQString& GetContentString() const;

protected:
   // {secret}
    void BuildExceptionString();

   // {secret}
    CMQString m_strStatus;
   // {secret}
    CMQString m_strContent;
};

#endif



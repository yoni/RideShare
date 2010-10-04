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
#ifndef __CMQEXCEPTION__
// {secret}
#define __CMQEXCEPTION__

#include "cstring.h"

/**
 * Base class for all Mapquest exceptions.
 * @ingroup Mapquest
 */
class CMQException
{
public:
   /**
    * Constructor
    */
   CMQException();
   /**
    * Constructor
    * @param szException A description of the exception
    */
   CMQException(const char *szException);
   /**
    * Constructor
    * @param szException A description of the exception
    * @param szStatus HTTP Status Code
    */
   CMQException(const char* szStatus, const char* szException);

   /**
    * Destructor
    */
   virtual ~CMQException() {};

   /**
    * Sets a description of the exception.
    *
    * @param szException A description of the exception
    */
   virtual void SetExceptionString(const char* szException);

   /**
    * Gets a description of the exception.
    *
    * @return A description of the exception
    */
   virtual const CMQString& GetExceptionString() const;

   /**
    * Set the status code
    * @param szStatus   the status code
    */
   virtual void SetStatusCode(const char* szStatus);
   /**
    * Get the status code
    * @return   the status code
    */
   virtual const CMQString& GetStatusCode() const;

   /**
    * Constant for generic "500 Server Error"
    */
   static const char* SERVER_ERROR;

protected:
   // {secret}
   CMQString m_strStatus;
   // {secret}
   CMQString m_strException;
};


/**
 * Exception thrown when bad requests are made to the server.
 * Usually a mismatch in configuration and request or just a
 * malformed request.
 * @ingroup Mapquest
 */
class CMQBadRequestException : public CMQException
{
public:
   /**
    * Constructor
    */
   CMQBadRequestException();
   /**
    * Constructor
    * @param szException A description of the exception
    */
   CMQBadRequestException(const char *szException);
   /**
    * Constructor
    * @param szException A description of the exception
    * @param szStatus HTTP Status Code
    */
   CMQBadRequestException(const char* szStatus, const char* szException);

   /**
    * Constant for generic "400 Bad Request"
    */
   static const char* BAD_REQUEST;
};

#endif   // __CMQEXCEPTION__



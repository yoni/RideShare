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
#ifndef _CMQIO_H_
// {secret}
#define _CMQIO_H_

// {secret}
const char MQ_NUM    = '\1';
// {secret}
const char MQ_TEXT   = '\2';
// {secret}
const char MQ_NUMTXT = '\3';

#include <sys/types.h>

#define GEO_SUCCESS  0
#define GEO_FAIL     1

class CMQIOBufferSemaphore;
class CMQString;

#include "mq_os.h"
#include "cstring.h"
#include "classtype.h"
#include "ioformat.h"


////////////////////////////////////////////////////////////////////////////////
// CMQIO - Base class of all MQ i/o

class CMQIO
{
public:
   CMQIO() { m_pIOFormatter = NULL; }
   CMQIO(CMQIOFormatter& /*ioFormatter*/) {};
   virtual ~CMQIO() {};

   virtual int read(void* buf, size_t len);
   virtual int write(const void* buf, size_t len);
   virtual off_t lseek(off_t /*offset*/, int /*whence*/) { return 0; }
   virtual off_t tell()  { return 0; };
   virtual void close() = 0;

   virtual void setFormatter(CMQIOFormatter& /*ioFormatter*/) {};
   virtual CMQIOFormatter* getFormatter();
   virtual void unsetFormatter();

   int write(const CMQString& aString,bool writeLength=false);
   int write(float aFloat);
   int write(long aLong);
   int write(int aInt);
   int write(short aShort);
   int write(char aChar);
   int write(unsigned char aChar);
   int write(bool aBool);
   int write(double aDouble);
   int write(const CMQClassType& aClassType, char cNumOrText = MQ_TEXT);

   int read(CMQString& aString,bool readLength=false);
   int read(float& aFloat);
   int read(long& aLong);
   int read(int& aInt);
   int read(short& aShort);
   int read(char& aChar);
   int read(unsigned char& aChar);
   int read(bool& aBool);
   int read(double& aDouble);
   int read(CMQClassType& aClassType, char cNumOrText = MQ_TEXT);

   int SizeOf(const CMQString& aString) const;
   int SizeOf(float aFloat) const;
   int SizeOf(long aLong) const;
   int SizeOf(int aInt) const;
   int SizeOf(short aShort) const;
   int SizeOf(char aChar) const {return sizeof(aChar);}
   int SizeOf(double aDouble) const;
   int SizeOf(const CMQClassType& aClassType, char cNumOrText = MQ_TEXT) const;

   const CMQString& GetLastError() const { return m_strLastError; }

protected:
   void SetLastError(const char *szError) { m_strLastError = szError; }

   // Low-Level read & write must be implemented in ALL derived classes
   virtual int llread(void* buf, size_t len) = 0;
   virtual int llwrite(const void* buf, size_t len) = 0;

   CMQIOFormatter *m_pIOFormatter; // binary or URL
   CMQString m_strLastError;
};

#endif   // _CMQIO_H_



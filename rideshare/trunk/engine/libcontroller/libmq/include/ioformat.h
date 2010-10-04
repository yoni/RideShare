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
#ifndef _CMQIOFORMATTER_H_
// {secret}
#define _CMQIOFORMATTER_H_


#include <sys/types.h>

class CMQString;    // #include <cstring.h>
class CMQClassType; // #include <classtype.h>
class CMQIO;        // #include <cio.h>


class CMQIOFormatter
{

public:
   /**
    * Constructor
    */
   CMQIOFormatter() { m_pCMQIO = NULL; }
   /**
    * Destructor
    */
   virtual ~CMQIOFormatter() {}

   virtual int write(const void* buff, size_t len) = 0;
   virtual int write(const CMQString& aString, bool writeLength=false) = 0;
   virtual int write(float aFloat) = 0;
   virtual int write(long aLong) = 0;
   virtual int write(int aInt) = 0;
   virtual int write(short aShort) = 0;
   virtual int write(char aChar) = 0;
   virtual int write(unsigned char aChar) = 0;
   virtual int write(bool aBool)=0;
   virtual int write(double aDouble) = 0;
   virtual int write(const CMQClassType& aClassType, char cNumOrText = MQ_TEXT) = 0;


   virtual int read(void* buff, size_t len) = 0;
   virtual int read(CMQString& aString, bool readLength=false) = 0;
   virtual int read(float& aFloat) = 0;
   virtual int read(long& aLong) = 0;
   virtual int read(int& aInt) = 0;
   virtual int read(short& aShort) = 0;
   virtual int read(char& aChar) = 0;
   virtual int read(unsigned char& aChar) = 0;
   virtual int read(bool& aBool)=0;
   virtual int read(double& aDouble) = 0;
   virtual int read(CMQClassType& aClassType, char cNumOrText = MQ_TEXT) = 0;

   // New Interface
   virtual void Init() {};

   void   SetIO(CMQIO& aCMQIO) { m_pCMQIO = &aCMQIO; Init(); };
   CMQIO* GetIO()              { return m_pCMQIO; };

protected:
   CMQIO *m_pCMQIO;
};


#endif   // _CMQIOFORMATTER_H_


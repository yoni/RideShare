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
#ifndef _JSONFORMAT_H_
// {secret}
#define _JSONFORMAT_H_

#include "cio.h"
#include "ioformat.h"
#include "exception.h"

/*
 * JSON IO Formatter class
 * @ingroup Mapquest
 */
class CMQJSONFormatter : public CMQIOFormatter //public CMQIO
{

public:
   /**
    * Constructor
    */
   CMQJSONFormatter() {}
   CMQJSONFormatter(CMQIO& io) { m_pCMQIO = &io; Init(); }
   /**
    * Destructor
    */
   virtual ~CMQJSONFormatter() {}

   virtual int write(const void*, size_t);

   // Old Interface -- not implemented in this class
   virtual int write(const CMQString&, bool) { return 0; };
   virtual int write(float) { return 0; };
   virtual int write(long) { return 0; };
   virtual int write(int) { return 0; };
   virtual int write(short) { return 0; };
   virtual int write(char) { return 0; };
   virtual int write(unsigned char) { return 0; };
   virtual int write(bool) { return 0; };
   virtual int write(double) { return 0; };
   virtual int write(const CMQClassType&, char cNumOrText) { return 0; };

   virtual int read(void*, size_t) { return 0; };
   virtual int read(CMQString&, bool) { return 0; };
   virtual int read(float&) { return 0; };
   virtual int read(long&) { return 0; };
   virtual int read(int&) { return 0; };
   virtual int read(short&) { return 0; };
   virtual int read(char&) { return 0; };
   virtual int read(unsigned char&) { return 0; };
   virtual int read(bool&) { return 0; };
   virtual int read(double&) { return 0; };
   virtual int read(CMQClassType&, char) { return 0; };


   // New Interface
   virtual void Init();

   virtual void WriteProperty(const char* szTag, const CMQString& aString, bool bWriteLength=false);
   virtual void WriteProperty(const char* szTag, float aFloat);
   virtual void WriteProperty(const char* szTag, long aLong);
   virtual void WriteProperty(const char* szTag, int aInt);
   virtual void WriteProperty(const char* szTag, short aShort);
   virtual void WriteProperty(const char* szTag, char aChar);
   virtual void WriteProperty(const char* szTag, unsigned char aChar);
   virtual void WriteProperty(const char* szTag, bool aBool);
   virtual void WriteProperty(const char* szTag, double aDouble);
   virtual void WriteObjectStart(const char* szTag, const CMQClassType& aClassType);
   virtual void WriteObjectEnd(const char* szTag, const char* aClassType);
   virtual void WriteObjectCollectionStart(const char* szTag, const CMQClassType& aClassType);
   virtual void WriteObjectCollectionEnd(const char* szTag, const char* aClassType);

   // All read not implemented in JSON
   virtual void ReadProperty(const char* szTag, CMQString& aString, bool bReadLength=false) {};
   virtual void ReadProperty(const char* szTag, float& aFloat) {};
   virtual void ReadProperty(const char* szTag, long& aLong) {};
   virtual void ReadProperty(const char* szTag, int& aInt) {};
   virtual void ReadProperty(const char* szTag, short& aShort) {};
   virtual void ReadProperty(const char* szTag, char& aChar) {};
   virtual void ReadProperty(const char* szTag, unsigned char& aChar) {};
   virtual void ReadProperty(const char* szTag, bool& aBool) {};
   virtual void ReadProperty(const char* szTag, double& aDouble) {};
   virtual void ReadObject(const char* szTag, CMQClassType& aClassType) {};

   // Local
   int _WriteStartTag(const char* szTag);
   int _WriteEndTag(const char* szTag);
   int _WriteObjectStartTag(const char* szTag);
   int _WriteObjectEndTag(const char* szTag);
   int _WriteObjectCollectionStartTag(const char* szTag);
   int _WriteObjectCollectionEndTag(const char* szTag);
   int _WriteAttribute(const char* szName, const char* szValue);
   int _WriteSeparater();
   void _AddCallback();

protected:
   int EncodedWrite();
   bool m_bNextSeparator;
   CMQString m_strIOString;
};

#endif // _JSONFORMAT_H_


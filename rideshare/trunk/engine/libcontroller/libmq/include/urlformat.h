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
#ifndef _URLFORMAT_H_
// {secret}
#define _URLFORMAT_H_

#include "ioformat.h"


class CMQURLFormatter : public CMQIOFormatter
{
public:
   /**
    * Constructor
    */
   CMQURLFormatter();
   /**
    * Destructor
    */
   virtual ~CMQURLFormatter();

   void Init();
   int  GetSize() const;

   int write(const void* buff, size_t len);
   int write(const CMQString& aString, bool writeLength=false);
   int write(float aFloat);
   int write(long aLong);
   int write(int aInt);
   int write(short aShort);
   int write(char aChar);
   int write(unsigned char aChar);
   int write(bool aBool);

   int write(double aDouble);
   int write(const CMQClassType& aClassType, char cNumOrText = MQ_TEXT);

   int read(void* buff, size_t len);
   int read(CMQString& aString, bool readLength=false);
   int read(float& aFloat);
   int read(long& aLong);
   int read(int& aInt);
   int read(short& aShort);
   int read(char& aChar);
   int read(unsigned char& aChar);
   int read(bool& aBool);

   int read(double& aDouble);
   int read(CMQClassType& aClassType, char cNumOrText = MQ_TEXT);

private:
   static const char m_cSeparator;
   static const char m_cEquator;
   static const char m_cVersionDelimiter;
   int EncodedWrite(char cSeparator = m_cSeparator);
   int DecodedRead(char cSeparator = m_cSeparator);

   CMQString   m_strIOString;
};


#endif // _URLFORMAT_H_



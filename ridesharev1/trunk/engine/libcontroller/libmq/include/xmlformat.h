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
#ifndef _XMLFORMAT_H_
// {secret}
#define _XMLFORMAT_H_

#include "cio.h"
#include "ioformat.h"
#include "exception.h"

/*
 * XML IO Formatter class
 * @ingroup Mapquest
 */
class CMQXMLFormatter : public CMQIOFormatter
{

public:
   /**
   * Constructor
   */
   CMQXMLFormatter();
   CMQXMLFormatter(CMQIO& io);
   /**
   * Destructor
   */
   virtual ~CMQXMLFormatter();

   static const char amp_ch;
   static const char lt_ch;
   static const char gt_ch;
   static const char qt_ch;
   static const char apos_ch;

   static const char sl_ch;
   static const char sp_ch;
   static const char eq_ch;

   /**
    * XML Encode data. turns "&,<,>" into &amp;,&lt;,&gt; etc.
    */
   static CMQString XMLEncode(const CMQString& data);

   virtual int write(const void* buff, size_t len);

   // Old Interface
   virtual int write(const CMQString& aString, bool writeLength=false); //writeLength always ignored
   virtual int write(float aFloat);
   virtual int write(long aLong);
   virtual int write(int aInt);
   virtual int write(short aShort);
   virtual int write(char aChar);
   virtual int write(unsigned char aChar);
   virtual int write(bool aBool);
   virtual int write(double aDouble);
   virtual int write(const CMQClassType& aClassType, char cNumOrText = MQ_TEXT);

   // All read not implemented
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
   virtual void Init() {};

   virtual void WriteProperty(const char* szTag, const CMQString& aString, const char* DefVal = "");
   virtual void WriteProperty(const char* szTag, float aFloat, float DefVal = 0.0);
   virtual void WriteProperty(const char* szTag, long aLong, long DefVal = 0);
   virtual void WriteProperty(const char* szTag, int aInt, int DefVal = 0);
   virtual void WriteProperty(const char* szTag, short aShort, short DefVal = 0);
   virtual void WriteProperty(const char* szTag, char aChar, char DefVal = 0);
   virtual void WriteProperty(const char* szTag, unsigned char aChar, unsigned char DefVal = 0);
   virtual void WriteProperty(const char* szTag, bool aBool, bool DefVal = false);
   virtual void WriteProperty(const char* szTag, double aDouble, double DefVal = 0.0);
   virtual void WriteObjectStart(const char* szTag, const CMQClassType& aClassType);
   virtual void WriteObjectEnd(const char* szTag, const char* aClassType);
   virtual void WriteObjectCollectionStart(const char* szTag, const CMQClassType& aClassType) { WriteObjectStart(szTag, aClassType); };
   virtual void WriteObjectCollectionEnd(const char* szTag, const char* aClassType) { WriteObjectEnd(szTag, aClassType); };

   virtual void ReadProperty(const char* szTag, CMQString& aString);
   virtual void ReadProperty(const char* szTag, float& aFloat);
   virtual void ReadProperty(const char* szTag, long& aLong);
   virtual void ReadProperty(const char* szTag, int& aInt);
   virtual void ReadProperty(const char* szTag, short& aShort);
   virtual void ReadProperty(const char* szTag, char& aChar);
   virtual void ReadProperty(const char* szTag, unsigned char& aChar);
   virtual void ReadProperty(const char* szTag, bool& aBool);
   virtual void ReadProperty(const char* szTag, double& aDouble);
   virtual bool ReadObject(const char* szTag, CMQClassType& aClassType, bool bChangeCurrentNode = true);

   // Local
   int  _WriteStartTagWithAttributes(const char* szTag, int numattr,...);
   int  _WriteStartTag(const char* szTag);
   int  _WriteEndTag(const char* szTag);
   int  _WriteAttribute(const char* szName, const char* szValue);
   CMQString _GetAttributeValue(const char* szAttribute);
   void _SetCollectionIndex(long lCollIndex) { m_lCollIndex = lCollIndex; }
   bool _AppendCurNodePath(const char* szTag);
   bool _SetCurNodeToParent();
   bool _SetCurNodeToFirstChildElement();
   bool _SetCurNodeToNextElement();
   bool _SetCurNodeToPrevElement();

protected:
   int EncodedWrite();
   int DecodedRead();
   CMQString GetNodeValue(const char* szTag);
   void LoadDocument();
   void* GetNodeSet(void* doc, void* xpath);

   CMQString m_strIOString;
   void* m_doc;
   void* m_curNode;
   void* m_context;
   long m_lCollIndex;
};

#endif // _XMLFORMAT_H_



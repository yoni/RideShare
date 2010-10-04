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
#ifndef _CMQXMLIOMEM_H_
// {secret}
#define _CMQXMLIOMEM_H_

#include "xmlformat.h"
#include "ciomem.h"

class CMQXMLIOMem : public CMQIOMem
{
public:
   CMQXMLIOMem(){ setFormatter(m_xmlFormatter); };
   virtual ~CMQXMLIOMem(){ unsetFormatter(); };

   int writeNode(const char* tagname, const CMQString& mqsTagValue);
   int writeNode(const char* tagname, int iTagValue);
   int writeNode(const char* tagname, long lTagValue);
   int writeNode(const char* tagname, float fTagValue, int precision=-1);
   int writeNode(const char* tagname, double dTagValue, int precision=-1);
   int writeNodeWithAttributes(const char* tagname, CMQString& tagvalue,int numattr,...);
   int writeStartTag(const char* tagname);
   int writeEndTag(const char* tagname);
   int writeAttribute(const char* name, const char* value);

protected:
   CMQXMLFormatter m_xmlFormatter;
};

#endif   // _CMQXMLIOMEM_H_



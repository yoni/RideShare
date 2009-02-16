/*****************************************************************************
*  Copyright (C) 1992-2005 MapQuest.com/America Online/Time Warner, Inc.
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
#ifndef _URLENCODER_H_
// {secret}
#define _URLENCODER_H_


/*
 *  This class implements the encoding scheme for URLs (as defined
 *  by <A HREF="http://www.w3.org/Addressing/rfc1738.txt">RFC 1738</A>)
 */
class CMQURLEncoder
{
public:
   /**
    * Encode a URL (as defined by
    * <A HREF="http://www.w3.org/Addressing/rfc1738.txt">RFC 1738</A>)
    *
    * @param URL  The URL string to encode
    *
    * @return  A NULL terminated character buffer containing the encoded URL
    *
    * The memory for the string is allocated by this method and must be
    * manually deleted by the calling function
    */
   static char* Encode(const char* URL);

   /**
    * Decode a URL (as defined by
    * <A HREF="http://www.w3.org/Addressing/rfc1738.txt">RFC 1738</A>)
    *
    * @param URL  The URL string to decode.  The results of the decoding are
    *             returned in this buffer
    */
   static void  Decode(char* URL);
};


#endif // _URLENCODER_H_



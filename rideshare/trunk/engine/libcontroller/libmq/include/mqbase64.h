/*****************************************************************************
* Copyright (C) 1992-2002 MapQuest.com/America Online/Time Warner, Inc.
* All Rights Reserved.
*-----------------------------------------------------------------------------
* This software is the confidential and proprietary information of
* MapQuest.com and America Online ("Confidential Information"). You shall
* not disclose such Confidential Information and shall use it only in
* accordance with the terms of the license agreement you entered into with
* MapQuest.com.
*-----------------------------------------------------------------------------
* MAPQUEST.COM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
* OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE, OR NON-INFRINGEMENT.  MAPQUEST.COM SHALL NOT BE LIABLE FOR ANY
* DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
* DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
*-----------------------------------------------------------------------------
*****************************************************************************/
#ifndef CMQBASE64_H
// {secret}
#define CMQBASE64_H

#include "cstring.h"

/*
 * This class provides Base64 encoding and decoding
 *
 * @see CMQExec
 * @ingroup Mapquest
 */
class CMQBase64
{
public:

  /**
   * Encode a string to Base64 representation
   *
   * @param plainText  The string to encode
   * @return  The Base64 representation of the string
   */
   static CMQString encode(const CMQString& plainText);
  /**
   * Encode a buffer of data to Base64 representation
   *
   * @param data  The data buffer (can be binary) to encode
   * @param length  The length of the data buffer to encode
   * @return  The Base64 representation of the string
   */
   static CMQString encode(const unsigned char* data, long length);

  /**
   * Decode a Base64 string
   *
   * @param encodedText  The Base64 encoded string
   * @return  The plain text representation of the string
   */
   static CMQString decode(const CMQString& encodedText);

private:
   static const char ALPHABET[];
   static const int LUT[];
};

#endif  // CMQBASE64_H



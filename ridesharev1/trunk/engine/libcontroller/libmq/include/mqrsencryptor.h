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
#ifndef CMQRANDOMSHUFFLEENCRYPTOR_H
// {secret}
#define CMQRANDOMSHUFFLEENCRYPTOR_H

#include <string>
#include "mqrandom.h"
#include "cstring.h"

/*
 *  An interface to the new MapQuest encryption and decryption routines
 */
class CMQRandomShuffleEncryptor
{
   public:
   /**
    *  Encrypt a character string.  The encrypted string will then be
    *  optionally URL encoded to create a legal string that can be passed in
    *  a URL
    *
    *  @param phrase     The string to encrypt
    *  @param URLEncode  URL encode the phrase after encrypting
    *
    *  @return  The encrypted/encoded input string
    */
   static CMQString encrypt(const CMQString& phrase, bool URLEncode = true);

   /**
    *  Decrypt a character string.  This will also optionally URL decode the
    *  string
    *
    *  @param phrase     The string to decrypt
    *  @param URLDecode  URL decode the phrase before decrypting.  This is
    *                    REQUIRED for proper decrypting if the phrase was
    *                    URL encoded after encryption
    *
    *  @return  The decrypted/decoded input string
    */
   static CMQString decrypt(const CMQString& encodedPhrase, bool URLDecode = true);

private:
  static CMQString encryptKey(unsigned long mask, unsigned long key);
  static unsigned long extractDecryptedKey(const CMQString& phrase);
  static CMQString scrambleKey(const CMQString& encryptedKey);
  static CMQString descrambleKey(const CMQString& scrambledKey);
  static CMQString scrambleIndices(const CMQString& key);
};

#endif  //  CMQRANDOMSHUFFLEENCRYPTOR_H


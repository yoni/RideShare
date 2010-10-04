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
#ifndef MQSTRINGTOKENIZER_H
// {secret}
#define MQSTRINGTOKENIZER_H

#include "cstring.h"
#include <vector>

/*
 * Internal class for parsing delimited strings into tokens
 * @ingroup Mapquest
 */
class CMQStringTokenizer
{
public:
   /**
    * Constructor
    */
   CMQStringTokenizer();

   /**
    * Constructor
    *
    * @param strToParse    The string to parse
    */
   CMQStringTokenizer(const CMQString& strToParse);

   /**
    * Constructor
    *
    * @param strToParse    The string to parse
    * @param strDelimiter  The delimiter that separates tokens.
    *                      Default is '|'
    * @param strEscape     The escape character.  Default is "" meaning that
    *                      tokens are not escaped
    */
   CMQStringTokenizer(const CMQString& strToParse,
                      const char* strDelimiter,
                      const char* strEscape = "");

   /**
    * Destructor
    */
   ~CMQStringTokenizer();

   /**
    * Get the total count of tokens in the string
    * @return  The number of tokens in the string
    */
   size_t getTokenCount();

   /**
    * Get the number of tokens remaining in the string
    * @return  The number of tokens remaining in the string
    */
   size_t getRemainingTokenCount();

   /**
    * Get the next token in the string
    * @param strHolder  The next token
    * @return  True if a token was found, false otherwise
    */
   bool getNextToken(CMQString& strHolder);

   /**
    * Get the n-th token in the string.  The index begins with 0
    * @param strToken  The n-th token
    * @param nIndex    The index of the token to retrieve
    * @return  True is a token was retrieved, false if the token index was
    *          out of range
    */
   bool getNthToken(CMQString& strToken, size_t nIndex);

   /**
    * Get the current string that contains tokens
    * @return  The current string
    */
   const CMQString& getCurrentString();

   /**
    * Set the string to tokenizer
    * @param str  The string to tokenize
    */
   void setCurrentString(const CMQString& str);

   /**
    * Set the value of the delimiter string
    * @param szDelim  The new string delimiter
    */
   void setTokenDelimiter(const char* szDelim);

   /**
    * Set the value of the escape string
    * @param szEscape  The new escape string
    */
   void setEscapeString(const char* szEscape) { m_strEscape = szEscape; }

private:
   CMQString m_strParse;
   CMQString m_strTokenDelimiter;
   CMQString m_strEscape;
   size_t    m_nTokenIdx;
   bool      m_bParsed;
   std::vector<CMQString> m_vTokens;

   /**
    * Parse the string into a set of tokens
    */
   void parseString();

   /**
    * Clear the tokenizer to start parsing again.  This is done automatically
    * when the parser state has been changed by changing the string,
    * delimiter or escape string
    */
   void clear();

   //  Don't allow the compiler to write these
   CMQStringTokenizer operator=(CMQStringTokenizer right);
   CMQStringTokenizer(const CMQStringTokenizer& right);
};
#endif   // MQSTRINGTOKENIZER_H



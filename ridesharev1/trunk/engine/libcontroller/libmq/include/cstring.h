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
#ifndef CMQSTRING_H
// {secret}
#define CMQSTRING_H

#ifdef MQWIN32
#pragma warning( disable : 4018 )
#endif

#include <fstream>

/**
 * The Mapquest C++ string class.
 * @ingroup Mapquest
 */
class CMQString
{
public:
   /**
    * Constructor
    */
   CMQString();
   /**
    * Constructor
    * @param aCMQString CMQString& a string object to copy from
    */
   CMQString(const CMQString& aCMQString);
   /**
    * Constructor
    * @param aCstring const char * a string to create this string from
    * @param nchars int number of characters to use from the string or -1 use strlen
    */
   CMQString(const char* aCstring, long nchars = -1);
   /**
    * Constructor
    * @param aDouble double value to create a string from
    */
   CMQString(double aDouble);
   /**
    * Constructor
    * @param aFloat float value to create a string from
    */
   CMQString(float aFloat);
   /**
    * Constructor
    * @param aLong long value to create a string from
    */
   CMQString(long aLong);
   /**
    * Constructor
    * @param aLong long value to create a string from
    */
   CMQString(unsigned long aLong);
   /**
    * Constructor
    * @param aInt int value to create a string from
    */
   CMQString(int aInt);
   /**
    * Constructor
    * @param aShort short value to create a string from
    */
   CMQString(short aShort);
   /**
    * Constructor
    * @param aShort short value to create a string from
    */
   CMQString(unsigned short aShort);
   /**
    * Constructor
    * @param aChar char value to create a string from
    */
   CMQString(char aChar);
   /**
    * Constructor
    * @param auChar unsigned char value to create a string from
    */
   CMQString(unsigned char auChar);

   /**
    * Destructor
    */
   ~CMQString();

   /**
    * Assignment operator
    * @param aCString const char * Source string to copy from
    */
   CMQString& operator=(const char* aCString);
   /**
    * Assignment operator
    * @param aCMQString CMQString& source string to copy from
    */
   CMQString& operator=(const CMQString& aCMQString);
   /**
    * Assignment operator
    * @param aDouble double Source to copy from
    */
   CMQString& operator=(double aDouble);
   /**
    * Assignment operator
    * @param aFloat float Source to copy from
    */
   CMQString& operator=(float aFloat);
   /**
    * Assignment operator
    * @param aLong long Source to copy from
    */
   CMQString& operator=(long aLong);
   /**
    * Assignment operator
    * @param aLong long Source to copy from
    */
   CMQString& operator=(unsigned long aLong);
   /**
    * Assignment operator
    * @param aInt int Source to copy from
    */
   CMQString& operator=(int aInt);
   /**
    * Assignment operator
    * @param aShort short Source to copy from
    */
   CMQString& operator=(short aShort);
   /**
    * Assignment operator
    * @param aShort short Source to copy from
    */
   CMQString& operator=(unsigned short aShort);
   /**
    * Assignment operator
    * @param aChar char Source to copy from
    */
   CMQString& operator=(char aChar);
   /**
    * Assignment operator
    * @param auChar unsigned char Source to copy from
    */
   CMQString& operator=(unsigned char auChar);
   /**
    * Copy const char* string into string with optional length
    * @param szString const char * Source string to copy from
    * @param len  number of characters to copy from the string or -1 use strlen
    */
   CMQString& Copy(const char* szString, int len = -1);

   /**
    * inequality operator
    * @param aCMQString CMQString& source string for comparison
    */
   bool operator!=(const CMQString&  aCMQString) const;
   /**
    * inequality operator
    * @param aCString const char * Source string for comparison
    */
   bool operator!=(const char* aCString) const;
   /**
    * equality operator
    * @param aCMQString CMQString& source string for comparison
    */
   bool operator==(const CMQString&  aCMQString) const;
   /**
    * equality operator
    * @param aCString const char * Source string for comparison
    */
   bool operator==(const char* aCString) const;

   /**
    * less-than operator
    * @param aCString const char * Source string for comparison
    */
   bool operator<(const char* aCString) const;
   /**
    * greater-than operator
    * @param aCString const char * Source string for comparison
    */
   bool operator>(const char* aCString) const;

   /**
    * concatenation operator
    * @param aCString const char * Source for concatenation
    */
   CMQString& operator+=(const char* aCString);
   /**
    * concatenation operator
    * @param aCMQString CMQString& source for concatenation
    */
   CMQString& operator+=(const CMQString& aCMQString);
   /**
    * concatenation operator
    * @param c char source for concatenation
    */
   CMQString& operator+=(char c);
   /**
    * Copy const char* string into string with optional length
    * @param szString const char * Source for concatenation
    * @param len  number of characters to append from the string or -1 use strlen
    */
   CMQString& Append(const char* szString, int len = -1);

   /**
    * Subscript operator
    * @param nIndex Index of char to extract
    */
   char operator[](int nIndex) const;
   /**
    * Subscript operator
    * @param nIndex Index of char to extract
    */
   char operator[](long nIndex) const;

   /**
    * extract sub string from left
    * @param nchars number of chars to extract
    */
   CMQString Left(long nchars) const;
   /**
    * extract sub string from a starting point
    * @param begin zero based starting point
    * @param nchars number of chars to extract, or -1 use strlen
    */
   CMQString Mid(long begin, long nchars = -1) const;
   /**
    * extract sub string from right
    * @param nchars number of chars to extract
    */
   CMQString Right(long nchars) const;


   /**
    * Trim leading and trailing white space
    */
   CMQString& Trim();
   /**
    * Trim leading white space
    */
   CMQString& TrimLeading();
   /**
    * Trim trailing white space
    */
   CMQString& TrimTrailing();
   /**
    * Remove all instances of specified string
    * @param szRemoveString string to remove
    */
   CMQString& RemoveChars(const char* szRemoveString);

   /**
    * Make string upper case
    */
   CMQString& MakeUpper();
   /**
    * Make string lower case
    */
   CMQString& MakeLower();

   /**
    * Compare string case sensitive
    * @param aCString const char * Source string for comparison
    */
   int Compare(const char* aCString) const;
   /**
    * Compare string case insensitive
    * @param aCString const char * Source string for comparison
    */
   int CompareNoCase(const char* aCString) const;

   /**
    * Find first occurrence of input string and return index
    * @param aCString string to search for
    * @param nStart index to start search
    */
   int Find(const char* aCString, int nStart = 0) const;

   /**
    * Find first occurrence of a character and return index
    * @param ch character to search for
    * @param nStart index to start search
    */
   int Find(const char ch, int nStart = 0) const;

   /**
    * Find last occurrence of a character and return index
    * @param ch character to search for
    */
   int ReverseFind(const char ch) const;

   /**
    * Checks if string is empty
    */
   bool IsEmpty() const;

   /**
    * Creates formatted string following the ANSI printf standards
    * @param fmt const char * format string of how to format data
    */
   void Format(const char* fmt, ...);

   /**
    * returns a const char * version of this string
    * @return const char* string array
    */
   operator const char*() const;
   /**
    * returns a const char * version of this string
    * @return const char* string array
    */
   const char* Cstring() const;

   /**
    * Returns the length of the string
    * @return the string length
    */
   long Length() const;

   // {secret}
   /*
    * sets all comparison functions to become case sensitive
    * Remarks: true=case sensitive, false=insensitive
    */
   void CaseSensitive(bool flag);

   /**
    * Substitutes all occurrences of one character with another
    * @param oldChar  character to find
    * @param newChar  character that will replace all occurrences of find character
    */
   void Substitute(const char oldChar, const char newChar)
   {
      if (m_szBuffer)
         for (long i = 0; i < Length(); i++)
            if (m_szBuffer[i] == oldChar)
               m_szBuffer[i] = newChar;
   }
   /**
    * Substitutes all occurrences of one string with another
    * @param pszFind     string to find
    * @param pszReplace  string that will replace all occurrences of find string
    * @return true if any substitutions were made, false otherwise
    */
   bool Substitute(const char* pszFind, const char* pszReplace);

   /**
    * Chop a string to a new length.
    * @param newLength  index of string to truncate at.
    */
   bool Chop(const long newLength)
   {
      if (!m_szBuffer || newLength > Length())
         return false;

      m_szBuffer[newLength] = '\0';
      m_lLength = newLength;
      return true;
   }

   // {secret}
   /*
    * dump to stream
    * @param os ostream& output stream
    * @param aCMQString CMQString& this object
    */
   friend std::ostream& operator<<(std::ostream& os, const CMQString& aCMQString);
   /*
    * extract from stream
    * @param is istream& input stream
    * @param aCMQString CMQString& this object
    */
   friend std::istream& operator>>(std::istream& is, CMQString& aCMQString);

private:
   // {secret}
   void Init();

protected:
   // {secret}
   void FreeSpace();
   // {secret}
   void AllocSpace(long size);
   // {secret}
   void ReallocSpace(long size);

protected:
   // {secret}
   char* m_szBuffer;
   // {secret}
   long  m_lBufSize;
   // {secret}
   long  m_lLength;
   // {secret}
   bool  m_bUseCase;
   // {secret}
   long  m_lGrowthFactor;
};


inline CMQString operator+(const CMQString& aCgsString1, const CMQString& aCgsString2)
{
   CMQString clNewString(aCgsString1);
   clNewString += aCgsString2;
   return clNewString;
};

inline CMQString operator+(const CMQString& aCgsString, const char* aCstring)
{
   CMQString clNewString(aCgsString);
   clNewString += aCstring;
   return clNewString;
};

inline CMQString operator+(const char* aCstring, const CMQString& aCgsString)
{
   CMQString clNewString(aCstring);
   clNewString += aCgsString;
   return clNewString;
};


#endif // CMQSTRING_H



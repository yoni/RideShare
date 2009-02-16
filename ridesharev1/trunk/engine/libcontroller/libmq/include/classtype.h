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
#ifndef _MQCLASSTYPE_H_
// {secret}
#define _MQCLASSTYPE_H_

/*
 * This class is used for versioning aspects of the C++ API objects
 * @ingroup Mapquest
 */
class CMQClassType
{
public:
   // Description:  constructor
   // @param nID int unique class type ID
   // @param strID const char * Name of the class
   // @param lVersion long Version of the class
   CMQClassType(int nID = -1, const char* strID = NULL, long lVersion = 0);
   // Description: destructor
   ~CMQClassType();

   // Description: equality operator
   // @param clCT CMQClassType reference to another classtype for comparison
   bool operator==(const CMQClassType& clCT) const;
   // Description: inequality operator
   // @param clCT CMQClassType reference to another classtype for comparison
   bool operator!=(const CMQClassType& clCT) const;

   // Description: Returns a unique class type ID for the object
   int isA() const;
   // Description: Returns the Name of the object
   const CMQString& Name() const;
   // Description: Returns the Version of the object
   long Version() const;
   // Description: Sets appropriate values for this object
   // @param n short unique class type ID
   // @param pstr const char * Name of the class
   // @param lVersion Version of the class
   void SetClassType(int nID, const char* pstr, long lVersion = 0);
   void SetClassType(int nID,             long lVersion = 0);
   void SetClassType(const char* pstr,       long lVersion = 0);

protected:
   //{secret}
   int m_nID;
   //{secret}
   CMQString m_strID;
   //{secret}
   long m_lVersion;
};

#endif   // _MQCLASSTYPE_H_

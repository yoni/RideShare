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
#ifndef _MQRECORDSET_H_
// {secret}
#define _MQRECORDSET_H_

#ifdef MQWIN32
#pragma warning( disable : 4786)
#endif

#include "mqobject.h"
#include "stringcollection.h"

#include <map>

typedef std::map<int,CMQStringCollection*> IntStringColMap;
typedef std::map<CMQString,int> StringIntMap;

/**
 * class for retrieving record attribute information.
 * @ingroup Mapquest
 */
class CMQRecordSet : public CMQObject
{
public:
   /**
    * Constructor.
    */
   CMQRecordSet();

   /**
    * Destructor.
    */
   virtual ~CMQRecordSet();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQRecordSet &operator=(const CMQRecordSet& Object);

   /**
    * Sets the cursor to the first record in the record set.
    */
   void MoveFirst();

   /**
    * Sets the cursor to the last record in the record set.
    */
   void MoveLast();

   /**
    * Sets the cursor to the next record in the record set.
    * If the cursor is currently set to the last record,
    * A call to MoveNext sets EOF to true
    */
   void MoveNext();

   /**
    * Set to true when the cursor is passed the end of the record set
    * @return     end record set flag
    */
   bool IsEOF() { return m_bEOF; };

   /**
    * Set to true when the cursor is before the beginning of the record set
    * @return     beginning record set flag
    */
   bool IsBOF() { return m_bBOF; };

   /**
    * Get the field value by field name
    * @param szFieldName   the field name
    */
   CMQString GetField(const char* szFieldName) const;

   /**
    * Get the list of available field names
    * @return the list of field names
    */
   const CMQStringCollection& GetFieldNames() const
   {
      return (*m_scFields);
   };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1710};
#else
   static const int   CLASS_ID = 1710;
#endif
   /**
    * Text name of this class
    */
   static const char* CLASS_NAME;

   /**
    * Returns the text name of this class
    * @return Text name of the this object
    */
   virtual const char* GetClassName() const { return CLASS_NAME; };
   /**
    * Returns the numeric id of this class
    * @return Numeric id of this object
    */
   virtual int         GetClassId()   const { return CLASS_ID;   };

   // {secret}
   virtual void LoadMe(CMQIO& io, long lVersion = -1);
   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   bool m_bEOF;
   // {secret}
   bool m_bBOF;

   // {secret}
   CMQStringCollection* m_scFields;
   // {secret}
   StringIntMap m_mFieldNames;
   // {secret}
   IntStringColMap m_mRecordSet;
   // {secret}
   int m_curRec;
};

#endif // _MQRECORDSET_H_

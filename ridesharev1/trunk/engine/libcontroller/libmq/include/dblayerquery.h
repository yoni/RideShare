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
#ifndef _MQDBLAYERQUERY_H_
// {secret}
#define _MQDBLAYERQUERY_H_

#include "mqobject.h"
#include "dbtodtmap.h"

/**
 * defines a specific dblayer to search
 * @see CMQDBLayerQueryCollection
 * @ingroup Mapquest
 */
class CMQDBLayerQuery : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQDBLayerQuery();
   /**
    * Destructor
    */
   virtual ~CMQDBLayerQuery();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1410};
#else
   static const int   CLASS_ID = 1410;
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
   virtual void   LoadMe(CMQIO& io, long lVersion = -1);
   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const;

   /**
    * Sets extra criteria.
    * Optional additional criteria.  Allows the user to further add SQL restrictions on the results
    * that would have been returned.  This SQL fragment will be appended to the WHERE clause with
    * an "AND" operator.
    * @param szCriteria the additional criteria to be added
    */
   void              SetExtraCriteria(const char* szCriteria);
   /**
    * Gets extra criteria.
    * Optional additional criteria.  Allows the user to further add SQL restrictions on the results
    * that would have been returned.  This SQL fragment will be appended to the WHERE clause with
    * an "AND" operator.
    * @return the additional criteria to be added
    */
   const CMQString&  GetExtraCriteria() const;

   /**
    * Set the name of the database layer to search.
    * @param szName   The name of the database layer to search
    */
   void              SetDBLayerName(const char* szName);
   /**
    * Get the name of the database layer to search.
    * @return     The name of the database layer to search
    */
   const CMQString&  GetDBLayerName() const;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQString   m_strExtraCriteria;
   // {secret}
   CMQString   m_strName;
};


/**
 * This class represents a DBLayerQuery that allows mapping of categories to DT's used by the Mapquest C++ API objects
 * @ingroup Mapquest
 */
class CMQDBLayerCatToDTMapQuery : public CMQDBLayerQuery
{
public:
   /**
    * Constructor
    */
   CMQDBLayerCatToDTMapQuery();
   /**
    * Destructor
    */
   virtual ~CMQDBLayerCatToDTMapQuery();

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1411};
#else
   static const int   CLASS_ID = 1411;
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

   /**
    * Set the name of the category field in the database.
    * @param strCategoryField the FieldName
    * @see CMQDBFieldType
    */
   void SetCategoryField(const CMQString strCategoryField) { m_strCategoryField = strCategoryField; };
   /**
    * Get the name of the category field in the database.
    * @return    the category field
    * @see CMQDBFieldType
    */
   CMQString GetCategoryField() { return m_strCategoryField; };
   /**
    * Set the data type of the Category field.
    * @param lCategoryFieldType the field type
    * @see CMQDBFieldType
    */
   void SetCategoryFieldType(long lCategoryFieldType) { m_lCategoryFieldType = lCategoryFieldType; };
   /**
    * Get the data type of the Category field.
    * @return   the field type
    * @see CMQDBFieldType
    */
   long GetCategoryFieldType() { return m_lCategoryFieldType; };
   /**
    * Get the collection that stores the name-value pairs for the category-DT pairs
    * @return   the collection
    */
   CMQCatToDTMapCollection &GetCatToDTMapCollection() { return (*m_CatToDTMapColl); } ;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQString               m_strCategoryField;
   // {secret}
   long                    m_lCategoryFieldType;
   // {secret}
   CMQCatToDTMapCollection* m_CatToDTMapColl;
};

#endif   // _MQDBLAYERQUERY_H_



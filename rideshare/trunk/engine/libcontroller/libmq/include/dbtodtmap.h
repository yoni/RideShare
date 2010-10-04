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
#ifndef _MQDBTODTMAP_H_
// {secret}
#define _MQDBTODTMAP_H_

#include "mqobject.h"
#include "objectcollection.h"

/**
 * This class represents a Category to DT map for a dbquery used by the Mapquest C++ API objects
 * @ingroup Mapquest
 */
class CMQCatToDTMap : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQCatToDTMap();
   /**
    * Constructor
    * @param szCategory  value of the mapping field to which a DT needs to be assigned
    * @param nDT         value of the DT to be assigned to the field
    */
   CMQCatToDTMap(const char* szCategory, int nDT );
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQCatToDTMap(const CMQCatToDTMap& Object);

   /**
    * Destructor
    */
   virtual ~CMQCatToDTMap();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQCatToDTMap& operator=(const CMQCatToDTMap& Object);

   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQCatToDTMap& Object);

   /**
    *  Initializes the object to the default values
    *  Initializes the Mapping field to ""
    *  Initializes the DT to a DT_NULL
    */
   void Init();

   /**
    *  Initializes the object
    * @param szCategory  value of the mapping field to which a DT needs to be assigned
    * @param nDT         value of the DT to be assigned to the field
    */
   void Init(const char* szCategory, const int nDT = 0xFFFC/*DT_NULL*/ );

   /**
    * Get the category.
    * @return    the category
    */
   const CMQString& GetCategory() const;
   /**
    * Set the category.
    * @param szCategory  the category
    */
   void SetCategory(const char* szCategory);

   /**
    * Get the DT to be assigned to the Category.
    * @return the DT
    */
   int GetDT();
   /**
    * Set the DT to be assigned to the Category.
    * @param nDT the DT
    */
   void SetDT( const int nDT );

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1412};
#else
   static const int   CLASS_ID = 1412;
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
   CMQString      m_strCategory;
   // {secret}
   int            m_nDT;
};


/**
 * This class represents a collection to hold CatToDTMap objects used by the Mapquest C++ API objects
 * @see CMQCatToDTMap
 * @ingroup Mapquest
 */
class CMQCatToDTMapCollection : public CMQObjectCollection< CMQCatToDTMap *>
{
public:
   /**
    * Constructor
    */
   CMQCatToDTMapCollection();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1421};
#else
   static const int   CLASS_ID = 1421;
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
   virtual bool ValidObject(CMQObject* pObject);
};

#endif   // _MQDBTODTMAP_H_



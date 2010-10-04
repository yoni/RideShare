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
#ifndef _MQOBJECTCOLLECTION_H_
// {secret}
#define _MQOBJECTCOLLECTION_H_

#include "mqobject.h"
#include "classfactory.h"
#include <vector>


/**
 * Template for collections of pointers.
 * This template is the basis for all the various object pointer collections
 * @ingroup Mapquest
 */
template<class TYPE>
class CMQObjectCollection : public CMQObject, public std::vector<TYPE>
{
public:
   /**
    * Constructor
    */
   CMQObjectCollection()
   {
      Init();
   }
   /**
    * Constructor
    * @param src Object to copy
    */
   CMQObjectCollection(const CMQObjectCollection& src)
   : CMQObject(src)
   {
      DeepCopy(src);
   }

   /**
    * Destructor
    */
   virtual ~CMQObjectCollection()
   {
      DeleteAll();
   }

   /**
    * assignment operator
    * @param src Object to copy
    */
   CMQObjectCollection& operator=(const CMQObjectCollection& src)
   {
      CMQObject::operator=(src);
      DeepCopy(src);
      return *this;
   }

   /**
    * Initialize all properties to default values.
    */
   virtual void Init()
   {
      CMQObject::Init();

      DeleteAll();
   }

   /**
    * Return the number of elements in the collection
    * @return the number of elements in the collection
    */
   long GetSize() const
   {
      return (long)this->size();
   }

   /**
    * Retrieve an object pointer from the collection
    * @param lIndex   Index of object pointer to retrieve
    * @return pointer to an object at requested index
    */
   virtual TYPE GetAt(long lIndex) const
   {
      if (lIndex <= (long)this->size()-1 && lIndex >= 0)
      {
         return (*this)[lIndex];
      }
      else
      {
         throw CMQException("Index out of bounds");
      }
   }

   /**
    * Add an object pointer to collection
    * @param newElement   Object pointer to add.
    */
   virtual void Add(TYPE newElement)
   {
      _Add(newElement);
   }

   // {secret}
   virtual bool ValidObject(CMQObject* /*pObject*/)
   {
      return true;
   }

   /**
    * Remove an Object pointer from the collection.
    * @param lIndex   Index of pointer to be removed
    */
   virtual void Remove(long lIndex)
   {
      if (lIndex <= (long)this->size()-1 && lIndex >= 0)
      {
         this->erase(this->begin()+lIndex);
      }
      else
      {
         throw CMQException("Index out of bounds");
      }
   }

   /**
    * Remove all Object pointers from the collection.
    */
   virtual void RemoveAll()
   {
      this->clear();
   }

   /**
    * Delete an Objects from the collection.
    * @param lIndex   Index of object to be deleted
    */
   void Delete(long lIndex)
   {
      if (lIndex <= (long)this->size()-1 && lIndex >= 0)
      {
         TYPE pObj = (*this)[lIndex];
         pObj->Release();
         this->erase(this->begin()+lIndex);
      }
      else
      {
         throw CMQException("Index out of bounds");
      }
   }

   /**
    * Delete all Objects in the collection.
    */
   virtual void DeleteAll()
   {
      for(long i=0, iCount=(long)this->size(); i < iCount; i++)
      {
         TYPE pObj = (*this)[i];
         pObj->Release();
      }
      this->clear();
   }

   /**
    * Append to this collection only object pointer are appended
    * @param src   the collection to copy from
    */
   void Append(const CMQObjectCollection& src)
   {
      for (long i=0, iCount=(long)src.size(); i < iCount; i++)
         Add(src.GetAt(i));
   }

   /**
    * Copy to this collection only object pointer are copied
    * @param src   the collection to copy from
    */
   void Copy(const CMQObjectCollection& src)
   {
      this->clear();
      Append(src);
   }

   /**
    * Append to this collection making new copies of all object in src.
    * @param src   the collection to copy from
    */
   void DeepAppend(const CMQObjectCollection& src)
   {
      CMQClassFactory cf;
      for (long i=0, iCount=(long)src.size(); i < iCount; i++)
      {
         TYPE pObj = src.GetAt(i);
         TYPE pNewObj = (TYPE)cf.CreateObject(pObj->GetClassId());
         *pNewObj = *pObj;

         Add(pNewObj);
      }
   }

   /**
    * Copy to this collection making new copies of all object in src/
    * @param src   the collection to copy from
    */
   void DeepCopy(const CMQObjectCollection& src)
   {
      DeleteAll();
      DeepAppend(src);
   }

   // {secret}
   virtual void LoadMe(CMQIO& io, long lVersion = -1)
   {
      try
      {
         CMQObject::LoadMe(io, lVersion);

         long lCount;
         if (GEO_SUCCESS != io.read(lCount))
            throw CMQException(CMQString("Count:") += io.GetLastError());

         CMQClassFactory cf;
         for (long i = 0; i < lCount; i++)
         {
            CMQObject* pObj = cf.CreateObject(io);
            if (pObj)
            {
               try
               {
                  _Add((TYPE)pObj, false); /// Add Validates Object Types
               }
               catch (CMQException& e)
               {
                  if (pObj)
                     pObj->Release();
                  throw e;
               }
            }
            else
            {
               throw CMQException(CMQString("Missing Object:") += io.GetLastError());
            }
         }
      }
      catch (CMQException& e)
      {
         CMQString strErr;
         strErr.Format("%s:LoadMe:%s", GetClassName(), (const char*)e.GetExceptionString());
         e.SetExceptionString(strErr);
         throw e;
      }
   }

   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const
   {
      try
      {
         CMQObject::SaveMe(io, bSaveClassType);

         long lCount = (long)this->size();
         if (GEO_SUCCESS != io.write(lCount))
            throw CMQException(CMQString("Count:") += io.GetLastError());

         CMQClassFactory cf;
         for(long i = 0; i < lCount; i++)
         {
            cf.SaveObject(io, *(CMQObject*)(*this)[i]);
         }
      }
      catch (CMQException& e)
      {
         CMQString strErr;
         strErr.Format("%s:SaveMe:%s", GetClassName(), (const char*)e.GetExceptionString());
         e.SetExceptionString(strErr);
         throw e;
      }
   }

protected:

   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1)
   {
      CMQObject::ReadPropertiesXML(io, lVersion);

      CMQClassFactory cf;
      long i = 1;
      while (i)
      {
         io._SetCollectionIndex(i);

         CMQObject* pObj = cf.CreateObject(io);
         if (pObj)
         {
            try
            {
               _Add((TYPE)pObj, false); /// Add Validates Object Types
            }
            catch (CMQException& e)
            {
               if (pObj)
                  pObj->Release();
               throw e;
            }
         }
         else
            break;

         i++;
      }
      io._SetCollectionIndex(-1);
      if (i > 1)
         io._SetCurNodeToParent();
   }

   // {secret}
   virtual void WriteStartObjectXML(const char* szTag, CMQXMLFormatter& io) const
   {
      CMQString strTag = (szTag[0] != 0) ? szTag : GetClassName();

      char szCount[12];
      sprintf(szCount,"%ld", GetSize());

      // Write Version if > 0
      if (m_lVersion > 0)
      {
         char szVersion[10];
         sprintf(szVersion,"%ld", m_lVersion);

         if (GEO_SUCCESS != io._WriteStartTagWithAttributes(strTag, 2, "Version", szVersion, "Count", szCount))
            throw CMQException("ClassType");
      }
      else
      {
         if (GEO_SUCCESS != io._WriteStartTagWithAttributes(strTag, 1, "Count", szCount))
            throw CMQException("ClassType");
      }
   }

   // {secret}
   virtual void WriteEndObjectXML(const char* szTag, CMQXMLFormatter& io) const
   {
      io.WriteObjectCollectionEnd(szTag, GetClassName());
   }

   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const
   {
      CMQObject::WritePropertiesXML(io);

      long lCount = (long)this->size();

      CMQClassFactory cf;
      for (long i = 0; i < lCount; i++)
      {
         cf.SaveObject(io, *(CMQObject*)(*this)[i]);
      }
   }


   // {secret}
   virtual void WriteStartObjectJSON(const char* szTag, CMQJSONFormatter& io) const
   {
      io.WriteObjectCollectionStart(szTag, CMQClassType(GetClassId(), GetClassName(), m_lVersion));
   }

   // {secret}
   virtual void WriteEndObjectJSON(const char* szTag, CMQJSONFormatter& io) const
   {
      io.WriteObjectCollectionEnd(szTag, GetClassName());
   }

   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const
   {
      CMQObject::WritePropertiesJSON(io);

      long lCount = (long)this->size();

      for (long i = 0; i < lCount; i++)
      {
         (*this)[i]->SaveJSON(">*CM*<", io);
      }
   }


   // {secret}
   virtual void _Add(TYPE newElement, bool bAddRef = true)
   {
      if       (newElement == NULL)
      {
         throw CMQException("Cannot add a NULL object to the collection.");
      }
      else if  (!ValidObject((CMQObject*)newElement))
      {
         throw CMQException("Invalid type object for this collection.");
      }

      if (bAddRef)
         newElement->AddRef();

      this->push_back(newElement);
   }

};


/**
 * Template for collections of simple types.
 * This template is the basis for all the various simple type collections
 * @ingroup Mapquest
 */
template<class TYPE>
class CMQSimpleCollection : public CMQObject, public std::vector<TYPE>
{
public:
   /**
    * Constructor
    */
   CMQSimpleCollection()
   {
      Init();
   }
   /**
    * Constructor
    * @param src Object to copy
    */
   CMQSimpleCollection(const CMQSimpleCollection& src)
   : CMQObject(src)
   {
      Copy(src);
   }

   /**
    * Destructor
    */
   virtual ~CMQSimpleCollection()
   {
      RemoveAll();
   }

   /**
    * assignment operator
    * @param src Object to copy
    */
   CMQSimpleCollection& operator=(const CMQSimpleCollection& src)
   {
      CMQObject::operator=(src);
      Copy(src);
      return *this;
   }

   /**
    * Initialize all properties to default values
    */
   virtual void Init()
   {
      CMQObject::Init();

      RemoveAll();
   }

   /**
    * Return the number of elements in the collection
    * @return the number of elements in the collection
    */
   long GetSize() const
   {
      return (long)this->size();
   }

   /**
    * Retrieve an object from the collection
    * @param lIndex   Index of object to retrieve
    * @return the object at the requested index
    */
   virtual TYPE GetAt(long lIndex) const
   {
      if (lIndex <= (long)this->size()-1 && lIndex >= 0)
      {
         return (*this)[lIndex];
      }
      else
      {
         throw CMQException("Index out of bounds");
      }
   }

   /**
    * Add an object to the collection
    * @param newElement   Object to add.
    */
   virtual void Add(const TYPE& newElement)
   {
      this->push_back(newElement);
   }

   /**
    * Remove an Object from the collection.
    * @param lIndex   Index of object to be removed
    */
   virtual void Remove(long lIndex)
   {
      if (lIndex <= (long)this->size()-1 && lIndex >= 0)
      {
         this->erase(this->begin()+lIndex);
      }
      else
      {
         throw CMQException("Index out of bounds");
      }
   }

   /**
    * Remove all Objects from the collection.
    */
   virtual void RemoveAll()
   {
      this->clear();
   }

   /**
    * Append to this collection.
    * @param src   the collection to copy from
    */
   void Append(const CMQSimpleCollection& src)
   {
      for (long i=0, iCount=(long)src.size(); i < iCount; i++)
         this->push_back(src.GetAt(i));
   }

   /**
    * Copy to this collection.
    * @param src   the collection to copy from
    */
   void Copy(const CMQSimpleCollection& src)
   {
      this->clear();
      Append(src);
   }

   // {secret}
   virtual void LoadMe(CMQIO& io, long lVersion = -1)
   {
      try
      {
         CMQObject::LoadMe(io, lVersion);

         long lCount;
         if (GEO_SUCCESS != io.read(lCount))
            throw CMQException(CMQString("Count:") += io.GetLastError());

         for (long i = 0; i < lCount; i++)
         {
            TYPE Obj;
            if (GEO_SUCCESS != io.read(Obj))
               throw CMQException(CMQString("Item:") += io.GetLastError());
            Add(Obj);
         }
      }
      catch (CMQException& e)
      {
         CMQString strErr;
         strErr.Format("%s:LoadMe:%s", GetClassName(), (const char*)e.GetExceptionString());
         e.SetExceptionString(strErr);
         throw e;
      }
   }

   // {secret}
   virtual void SaveMe(CMQIO& io, bool bSaveClassType = true) const
   {
      try
      {
         CMQObject::SaveMe(io, bSaveClassType);

         long lCount = (long)this->size();
         if (GEO_SUCCESS != io.write(lCount))
            throw CMQException(CMQString("Count:") += io.GetLastError());

         for(long i = 0; i < lCount; i++)
         {
            if (GEO_SUCCESS != io.write((*this)[i]))
               throw CMQException(CMQString("Item:") += io.GetLastError());
         }
      }
      catch (CMQException& e)
      {
         CMQString strErr;
         strErr.Format("%s:SaveMe:%s", GetClassName(), (const char*)e.GetExceptionString());
         e.SetExceptionString(strErr);
         throw e;
      }
   }

protected:

   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1)
   {
      CMQObject::ReadPropertiesXML(io, lVersion);

      long i = 1;
      while (i)
      {
         io._SetCollectionIndex(i);

         if (i == 1)
         {
            if (!io._SetCurNodeToFirstChildElement())
               break;
         }
         else
         {
            if (!io._SetCurNodeToNextElement())
               break;
         }

         TYPE Obj;
         io.ReadProperty(NULL, Obj);
         Add(Obj);

         i++;
      }
      io._SetCollectionIndex(-1);
      if (i > 1)
         io._SetCurNodeToParent();
   }

   // {secret}
   virtual void WriteStartObjectXML(const char* szTag, CMQXMLFormatter& io) const
   {
      CMQString strTag = (szTag[0] != 0) ? szTag : GetClassName();

      char szCount[12];
      sprintf(szCount,"%ld", GetSize());

      // Write Version if > 0
      if (m_lVersion > 0)
      {
         char szVersion[10];
         sprintf(szVersion,"%ld", m_lVersion);

         if (GEO_SUCCESS != io._WriteStartTagWithAttributes(strTag, 2, "Version", szVersion, "Count", szCount))
            throw CMQException("ClassType");
      }
      else
      {
         if (GEO_SUCCESS != io._WriteStartTagWithAttributes(strTag, 1, "Count", szCount))
            throw CMQException("ClassType");
      }
   }

   // {secret}
   virtual void WriteEndObjectXML(const char* szTag, CMQXMLFormatter& io) const
   {
      io.WriteObjectCollectionEnd(szTag, GetClassName());
   }

   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const
   {
      CMQObject::WritePropertiesXML(io);

      long lCount = (long)this->size();

      for (long i = 0; i < lCount; i++)
      {
         io.WriteProperty("Item", (*this)[i]);
      }
   }


   // {secret}
   virtual void WriteStartObjectJSON(const char* szTag, CMQJSONFormatter& io) const
   {
      io.WriteObjectCollectionStart(szTag, CMQClassType(GetClassId(), GetClassName(), m_lVersion));
   }

   // {secret}
   virtual void WriteEndObjectJSON(const char* szTag, CMQJSONFormatter& io) const
   {
      io.WriteObjectCollectionEnd(szTag, GetClassName());
   }

   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const
   {
      CMQObject::WritePropertiesJSON(io);

      long lCount = (long)this->size();

      for (long i = 0; i < lCount; i++)
      {
         io.WriteProperty("", (*this)[i]);
      }
   }

};

#endif   // _MQOBJECTCOLLECTION_H_



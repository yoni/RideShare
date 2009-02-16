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
#ifndef _MQSESSION_H_
// {secret}
#define _MQSESSION_H_

#include "mqobject.h"
#include "objectcollection.h"

/**
 * Session Object.
 * This collection holds only specific objects that are used by the
 * Mapquest server to represent a Mapquest Session.
 * @ingroup Mapquest
 * @see CMQMapState
 * @see CMQPrimitiveCollection
 * @see CMQCoverageStyle
 * @see CMQDBLayerQueryCollection
 * @see CMQMapCommand
 * @see CMQFeatureCollection
 */
class CMQSession : public CMQObjectCollection<CMQObject *>
{
public:
   /**
    * Constructor
    */
   CMQSession();

   /** Operation that supersedes the Add() from CMQObjectCollection.
    * Ensures that only one of a select number of CMQObjects is added;
    * if newElement replaces an existing CMQObject, replacedElement will
    * point to it, hence the need to pass the address of a pointer to
    * a CMQObject (i.e., a pointer to a pointer).
    * @param newElement  Object to add
    * @param replacedElement Item replaced -- might need deleted
    */
   void      AddOne(CMQObject* newElement, CMQObject** replacedElement = NULL);


   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1270};
#else
   static const int   CLASS_ID = 1270;
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

   /**
    * Return the unique element from the collection.
    * This function returns the unique element of the type specified by
    * szClassName. Class name is obtained from any Class by the following
    * convention CMQXXXXXX::CLASS_NAME
    * ex: sessVar.GetObject(CMQMapState::CLASS_NAME);
    *
    * @param szClassName Name of the object to extract
    * @return CMQObject* or a NULL pointer
    *
    * @see CMQMapState
    * @see CMQPrimitiveCollection
    * @see CMQCoverageStyle
    * @see CMQDBLayerQueryCollection
    * @see CMQMapCommand
    * @see CMQFeatureCollection
    */
   CMQObject* GetObject(const char* szClassName);

protected:
   // {secret}
   virtual void Add(CMQObject *newElement);
};

#endif   // _MQSESSION_H_



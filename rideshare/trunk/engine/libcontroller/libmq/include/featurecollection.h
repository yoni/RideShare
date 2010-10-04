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
#ifndef _MQFEATURECOLLECTION_H_
// {secret}
#define _MQFEATURECOLLECTION_H_

#include "mqobject.h"
#include "objectcollection.h"
#include "feature.h"

#include "dtcollection.h"

/**
 * Collection to hold feature objects.
 * @see CMQFeature
 * @see CMQPointFeature
 * @see CMQLineFeature
 * @see CMQPolygonFeature
 * @see CMQObjectCollection
 * @ingroup Mapquest
 */
class CMQFeatureCollection : public CMQObjectCollection<CMQFeature *>
{
public:
   /**
    * Constructor
    */
   CMQFeatureCollection();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1180};
#else
   static const int   CLASS_ID = 1180;
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

   // {secret}
   bool GetBoundingRect(CMQLatLng& UL, CMQLatLng& LR, CMQDTCollection* pDTColl  = NULL);
   // {secret}
   bool ExpandBoundingRect(CMQLatLng& UL, CMQLatLng& LR, CMQDTCollection* pDTColl  = NULL);
};

#endif   // _MQFEATURECOLLECTION_H_



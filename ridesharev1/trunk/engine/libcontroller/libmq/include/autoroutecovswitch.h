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
#ifndef _MQAUTOROUTECOVSWITCH_H_
// {secret}
#define _MQAUTOROUTECOVSWITCH_H_

#include "mqobject.h"
#include "intcollection.h"

/**
 * Stores route coverage switching parameters.
 * @see CMQDataVendorCode
 * @ingroup Mapquest
 */
class CMQAutoRouteCovSwitch : public CMQObject
{
public:
#ifdef _MQ_DEPRECATED_
   static const long nDataVendorCodeUsage_Include; /**< @deprecated use CMQDataVendorCode::USAGE_INCLUDE */
   static const long nDataVendorCodeUsage_Exclude; /**< @deprecated use CMQDataVendorCode::USAGE_EXCLUDE */

   static const long nDataVendorCode_UNKNOWN;      /**< @deprecated use CMQDataVendorCode::UNKNOWN   */
   static const long nDataVendorCode_NT;           /**< @deprecated use CMQDataVendorCode::NT        */
   static const long nDataVendorCode_GDT;          /**< @deprecated use CMQDataVendorCode::GDT       */
   static const long nDataVendorCode_DMTI;         /**< @deprecated use CMQDataVendorCode::DMTI      */
   static const long nDataVendorCode_MQ;           /**< @deprecated use CMQDataVendorCode::MQ        */
   static const long nDataVendorCode_CA;           /**< @deprecated use CMQDataVendorCode::CA        */
   static const long nDataVendorCode_TIGER;        /**< @deprecated use CMQDataVendorCode::TIGER     */
   static const long nDataVendorCode_ETAK;         /**< @deprecated use CMQDataVendorCode::ETAK      */
   static const long nDataVendorCode_TA;           /**< @deprecated use CMQDataVendorCode::TA        */
   static const long nDataVendorCode_AND;          /**< @deprecated use CMQDataVendorCode::AND       */
   static const long nDataVendorCode_VOYAGER;      /**< @deprecated use CMQDataVendorCode::VOYAGER   */
   static const long nDataVendorCode_CRITCHLOW;    /**< @deprecated use CMQDataVendorCode::CRITCHLOW */
   static const long nDataVendorCode_LEADDOG;      /**< @deprecated use CMQDataVendorCode::LEADDOG   */
#endif
   /**
    * Constructor
    */
   CMQAutoRouteCovSwitch();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQAutoRouteCovSwitch& operator=(const CMQAutoRouteCovSwitch& Object);

   /**
    * Destructor
    */
   virtual ~CMQAutoRouteCovSwitch();

   /**
    * Sets the name of the coverage switching rules to use.  Names of
    * coverage switching rules are defined in the mqserver.ini file.
    * @param szName Name of coverage switching rules to use.
    */
   void              SetName(const char* szName);
   /**
    * Gets the name of the coverage switching rules being used.
    * @return Name
    */
   const CMQString&  GetName() const;

   /**
    * Returns a reference to a collection of map data vendor codes.
    * @see CMQDataVendorCode
    */
   CMQIntCollection& DataVendorCodes();

   /**
    * Sets the data vendor code usage, which specifies how the vendor codes
    * listed in DataVendorCodes() are to be used.  If set to nDataVendorCodeUsage_Include,
    * the coverage switching algorithm will only consider coverages with vendor codes
    * listed in DataVendorCodes. If set to CMQDataVendorCode::USAGE_EXCLUDE, all coverages
    * will be considered EXCEPT those with vendor codes listed in DataVendorCodes.
    * @param nDataVendorCodeUsage - DataVendorCodeUsage flag
    * @see CMQDataVendorCode
    */
   void SetDataVendorCodeUsage(long nDataVendorCodeUsage);
   /**
    * Gets the vendor name usage.
    * @return DataVendorCodeUsage flag
    * @see CMQDataVendorCode
    */
   long GetDataVendorCodeUsage() const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1642};
#else
   static const int   CLASS_ID = 1642;
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
   CMQString         m_strName;
   // {secret}
   CMQIntCollection* m_DataVendorCodes;
   // {secret}
   long              m_nDataVendorCodeUsage;
};

#endif   // _MQAUTOROUTECOVSWITCH_H_



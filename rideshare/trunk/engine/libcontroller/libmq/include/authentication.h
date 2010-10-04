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
#ifndef _MQAUTHENTICATION_H_
// {secret}
#define _MQAUTHENTICATION_H_

#include "mqobject.h"

/*
 * Authentication object for Mapquest
 * @ingroup Mapquest
 */
class CMQAuthentication : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQAuthentication();

   /**
    * Destructor
    */
   virtual ~CMQAuthentication();

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1400};
#else
   static const int   CLASS_ID = 1400;
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
    * Set the Password String
    * @param szPassword const char* the new Password string
    */
   void        SetPassword(const char* szPassword);
   /**
    * Get the Password String
    */
   const CMQString& GetPassword() const;

   /**
    * Set the ClientId for this request
    * @param szClientId  the ClientId
    */
   void        SetClientId(const char* szClientId);
   /**
    * Get the ClientId for this request
    */
   const CMQString& GetClientId() const;

   /**
   * Sets string data to be passed to the server to be logged with any subsequent requests
   * in the transaction log.
   *
   * @param  szXInfo  Transaction Info
   */
   void             SetTransactionInfo(const char* szXInfo);

   /**
   * Gets string data to be passed to the server to be logged with any subsequent requests
   * in the transaction log.
   *
   * @return   Transaction Info
   */
   const CMQString& GetTransactionInfo() const;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQString   m_strPassword;
   // {secret}
   CMQString   m_strClientId;
   // {secret}
   CMQString   m_strXInfo;
};

#endif   // _MQAUTHENTICATION_H_



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
#ifndef _MQLOCATION_H_
// {secret}
#define _MQLOCATION_H_

#include "mqobject.h"
#include "objectcollection.h"
#include "latlng.h"

// {secret}
#define MQ_MAX_ADMINAREAS      7

/**
 * Base class for all location objects
 * @see CMQLocationCollection
 * @ingroup Mapquest
 */
class CMQLocation : public CMQObject
{
protected:
   /**
    * Constructor
    */
   CMQLocation();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQLocation(const CMQLocation& Object);

public:
   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQLocation& operator=(const CMQLocation& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQLocation& Object);
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQLocation& Object);

   /**
    * Destructor
    */
   virtual ~CMQLocation();

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

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
   virtual void CopyMemberData(const CMQObject* pObj);
};


/**
 * This object holds an input address to send to the geocoder.
 * @ingroup Mapquest
 */
class CMQSingleLineAddress : public CMQLocation
{
public:
   /**
    * Constructor
    */
   CMQSingleLineAddress();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQSingleLineAddress(const CMQSingleLineAddress& Object);

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQSingleLineAddress& operator=(const CMQSingleLineAddress& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQSingleLineAddress& Object);
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQSingleLineAddress& Object);

   /**
    * Destructor
    */
   virtual ~CMQSingleLineAddress();


   /**
    * Set the single line address
    * @param szAddress   the single line address
    */
   void              SetAddress(const char* szAddress);
   /**
    * Get the single line address
    * @return    the single line address
    */
   const CMQString&  GetAddress() const;

   /**
    * Set the country name
    * @param szCountry   the country name
    */
   void              SetCountry(const char* szCountry);
   /**
    * Get the country name
    * @return    the country name
    */
   const CMQString&  GetCountry() const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1091};
#else
   static const int   CLASS_ID = 1091;
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
   virtual void CopyMemberData(const CMQObject* pObj);

   // {secret}
   CMQString         m_strAddress;
   // {secret}
   CMQString         m_strCountry;
};


/**
 * This object holds an input address to send to the geocoder.
 * @ingroup Mapquest
 */
class CMQAddress : public CMQLocation
{
public:
   /**
    * Constructor
    */
   CMQAddress();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQAddress(const CMQAddress& Object);

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQAddress& operator=(const CMQAddress& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQAddress& Object);
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQAddress& Object);

   /**
    * Destructor
    */
   virtual ~CMQAddress();


   /**
    * Set the street address, use an '@' to separate streets in an intersection
    * @param szStreet   the street address
    */
   void              SetStreet(const char* szStreet);
   /**
    * Get the street address line
    * @return    the street address
    */
   const CMQString&  GetStreet() const;

   /**
    * Set the city name
    * @param szCity   the city name
    */
   void              SetCity(const char* szCity);
   /**
    * Get the city name
    * @return    the city name
    */
   const CMQString&  GetCity() const;

   /**
    * Set the county name
    * @param szCounty   the county name
    */
   void              SetCounty(const char* szCounty);
   /**
    * Get the county name
    * @return    the county name
    */
   const CMQString&  GetCounty() const;

   /**
    * Set the state name
    * @param szState   the state name
    */
   void              SetState(const char* szState);
   /**
    * Get the state name
    * @return    the state name
    */
   const CMQString&  GetState() const;

   /**
    * Set the postal code
    * @param szPostalCode   the postal code
    */
   void              SetPostalCode(const char* szPostalCode);
   /**
    * Get the postal code
    * @return    the postal code
    */
   const CMQString&  GetPostalCode() const;

   /**
    * Set the country name
    * @param szCountry   the country name
    */
   void              SetCountry(const char* szCountry);
   /**
    * Get the country name
    * @return    the country name
    */
   const CMQString&  GetCountry() const;

   /**
    * Set the desired administrative area string
    * @param nIndex        the index of the administrative area to set
    * @param szAdminArea   the administrative area string
    */
   void              SetAdminArea(int nIndex, const char* szAdminArea);
   /**
    * Get the desired administrative area string
    * @param nIndex        the index of the administrative area to return
    * @return    the administrative area string
    */
   const CMQString&  GetAdminArea(int nIndex) const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1090};
#else
   static const int   CLASS_ID = 1090;
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
   virtual void CopyMemberData(const CMQObject* pObj);

   // {secret}
   CMQString         m_strStreet;
   // {secret}
   CMQString         m_strPostalCode;
   // {secret}
   CMQString         m_strAdminAreas[MQ_MAX_ADMINAREAS];
};


/**
 * object that holds a geocoded address
 * NOTE: geocode may have failed and user should check the geocode status
 * @ingroup Mapquest
 */
class CMQGeoAddress : public CMQAddress
{
public:
   /**
    * Constructor
    */
   CMQGeoAddress();
   /**
    * Constructor
    * @param Object Object to copy
    */
   CMQGeoAddress(const CMQGeoAddress& Object);

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQGeoAddress& operator=(const CMQGeoAddress& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQGeoAddress& Object);
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQGeoAddress& Object);

   /**
    * Destructor
    */
   virtual ~CMQGeoAddress();


   /**
    * Set the locations position
    * @param llLatLng   the locations position
    */
   void              SetLatLng(const CMQLatLng& llLatLng);
   /**
    * Get the locations position
    * @return    the locations position
    */
   const CMQLatLng&  GetLatLng() const;

   /**
    * Set the geocode result code
    * @param szResultCode   the geocode status code
    */
   void              SetResultCode(const char* szResultCode);
   /**
    * Get the geocode result code
    * Remarks:
    * Refer to Users guide for more information.
    *
    * @return    the geocode result code
    */
   const CMQString&  GetResultCode() const;

   /**
    * Set the GEFID of Geocoded Address - for use with routing
    * @param lGEFID   the GEFID of Geocoded Address
    */
   void              SetGEFID(long lGEFID);
   /**
    * Get the GEFID of Geocoded Address  - for use with routing
    * @return    the GEFID of Geocoded Address
    */
   long              GetGEFID() const;

   /**
    * Set the Distance along the link where geocoded, or the distance from a link when returned from routing
    * @param dDistAlong   the Distance
    */
   void              SetDistAlong(double dDistAlong);
   /**
    * Get the Distance along the link where geocoded, or the distance from a link when returned from routing
    * @return    the Distance
    */
   double            GetDistAlong() const;

   /**
    * Set the source id
    * @param szSourceId    the source coverage id that the geocode was acquired from
    */
   void SetSourceId(const char* szSourceId);
   /**
    * Get the source id
    * @return    the source coverage id that the geocode was acquired from
    */
   const CMQString& GetSourceId() const;

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1110};
#else
   static const int   CLASS_ID = 1110;
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
   virtual void CopyMemberData(const CMQObject* pObj);

   // {secret}
   CMQLatLng*        m_clLL;
   // {secret}
   CMQString         m_strResultCode;
   // {secret}
   double            m_dDistAlong;
   // {secret}
   long              m_lGEFID;
   // {secret}
   CMQString         m_strSourceId;

};


/**
 * Collection that holds Location objects
 * @see CMQLocation
 * @see CMQAddress
 * @see CMQGeoAddress
 * @see CMQObjectCollection
 * @ingroup Mapquest
 */
class CMQLocationCollection : public CMQObjectCollection<CMQLocation *>
{
public:
   /**
    * Constructor
    */
   CMQLocationCollection();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1150};
#else
   static const int   CLASS_ID = 1150;
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

/**
 * A Collection that holds a collection of LocationCollection objects.
 * This object holds the results form a BatchGeocode call.
 * @see CMQLocationCollection
 * @see CMQObjectCollection
 * @ingroup Mapquest
 */
class CMQLocationCollectionCollection : public CMQObjectCollection<CMQLocationCollection *>
{
public:
   /**
    * Constructor
    */
   CMQLocationCollectionCollection();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1155};
#else
   static const int   CLASS_ID = 1155;
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

#endif   // _MQLOCATION_H_



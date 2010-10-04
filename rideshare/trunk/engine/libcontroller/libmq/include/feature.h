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
#ifndef _MQFEATURE_H_
// {secret}
#define _MQFEATURE_H_

#include "mqobject.h"
#include "latlngcollection.h"
#include "pointcollection.h"

/**
 * base class for all MapQuest map features.  Not createable.
 * @see CMQFeatureCollection
 * @ingroup Mapquest
 */
class CMQFeature : public CMQObject
{
protected:
   /**
    * Constructor
    */
   CMQFeature();

public:
   /**
    * Destructor
    */
   virtual ~CMQFeature();
   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQFeature& operator=(const CMQFeature& Object);

   /**
    * Set the feature name.
    * @param szName   the feature name
    */
   void              SetName(const char* szName);
   /**
    * Get the feature name.
    * @return    the feature name
    */
   const CMQString&  GetName() const;
   /**
    * Set the display type value.
    * @param nDT   the display type value
    */
   void              SetDT(const long nDT);
   /**
    * Get the display type value.
    * @return    the display type value
    */
   const long&       GetDT() const;
   /**
    * Set the GEFID of this feature.
    * @param ulKey   the GEFID of this feature
    */
   void              SetGEFID(const long ulKey);
   /**
    * Get the GEFID of this feature.
    * @return    the GEFID of this feature
    */
   const long&       GetGEFID() const;
   /**
    * Set the source layer name.
    * @param szSourceLayerName   the source layer name
    */
   void              SetSourceLayerName(const char* szSourceLayerName);
   /**
    * Get the source layer name.
    * @return    the source layer name
    */
   const CMQString&  GetSourceLayerName() const;

   /**
    * Set the user defined key value.
    * @param szKey   the user defined key value
    */
   void              SetKey(const char* szKey);
   /**
    * Get the user defined key value.
    * @return    the user defined key
    */
   const CMQString&  GetKey() const;

   /**
    * Set the Distance from center of a radius search.
    * @param dDistance the distance from the center of a radius search
    * @param lUnits    the units type to return
    * @see CMQDistanceUnits
    */
   void              SetDistance(const double dDistance, long lUnits = CMQDistanceUnits::MILES);
   /**
    * Get the Distance from center of a radius search.
    * @param lUnits    the units type to return
    * @return          the distance from the center of a radius search
    * @see CMQDistanceUnits
    */
   double            GetDistance(long lUnits = CMQDistanceUnits::MILES) const;

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
   long              m_nDT;
   // {secret}
   long              m_ulGEFID;
   // {secret}
   CMQString         m_strSourceLayerName;
   // {secret}
   CMQString         m_strKey;
   // {secret}
   double            m_dDistance;
};


/**
 * describes a point feature
 * @ingroup Mapquest
 */
class CMQPointFeature : public CMQFeature
{
protected:
   // {secret}
   CMQLatLng*        m_LL;
   // {secret}
   CMQPoint*         m_XY;

public:
   /**
    * Constructors
    */
   CMQPointFeature();
   /**
    * Constructors
    * @param Object Object to copy
    */
   CMQPointFeature(CMQPointFeature& Object);

   /**
    * Destructor
    */
   virtual ~CMQPointFeature();
   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQPointFeature& operator=(const CMQPointFeature& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQPointFeature& Object) const;

   /**
    * Set the location of this feature.
    * @param ll   the location of this feature
    */
   void        SetCenterLatLng(const CMQLatLng& ll);
   /**
    * Get the location of this feature.
    * @return    the location of this feature
    */
   CMQLatLng&  GetCenterLatLng();


   /**
    * Set the pixel location of this feature.
    * @param xy   the pixel location of this feature
    */
   void        SetCenterPoint(const CMQPoint& xy);
   /**
    * Get the pixel location of this feature.
    * @return    the pixel location of this feature
    */
   CMQPoint&   GetCenterPoint();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1000};
#else
   static const int   CLASS_ID = 1000;
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
};


/**
 * describes a line feature
 * @ingroup Mapquest
 */
class CMQLineFeature : public CMQFeature
{
public:
   /**
    * Constructors
    */
   CMQLineFeature();
   /**
    * Constructors
    * @param Object Object to copy
    */
   CMQLineFeature(CMQLineFeature& Object);

   /**
    * Destructor
    */
   virtual ~CMQLineFeature();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQLineFeature& operator=(const CMQLineFeature& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQLineFeature& Object) const;

   /**
    * Get the closest Lat/Lng location of this feature.
    * @return    the closest Lat/Lng location of this feature
    */
   CMQLatLng&  GetClosestLatLng()     {return (*m_LL);}
   /**
    * Set the closest Lat/Lng location of this feature.
    * @param ll   the closest Lat/Lng location of this feature
    */
   void        SetClosestLatLng(const CMQLatLng& ll)    {(*m_LL) = ll;}

   /**
    * Get the closest point pixel value of this feature.
    * @return    the closest point pixel value of this feature
    */
   CMQPoint&   GetClosestPoint() { return (*m_XY); };
   /**
    * Set the closest point pixel location of this feature.
    * @param xy   the closest point pixel location of this feature
    */
   void        SetClosestPoint(const CMQPoint& xy)      {(*m_XY) = xy;}
   /**
    * Get the line feature shape points.
    * @return a reference to a CMQLatLngCollection
    */
   CMQLatLngCollection& GetLatLngs() { return (*m_LLCollection); };

   /**
    * return the line feature shape points in display coordinates.
    * @return a reference to a CMQPointCollection
    */
   CMQPointCollection&  GetPoints()  { return (*m_XYCollection); };

   /**
    * Set the postal code for the right side of the link.
    * @param szPostalCode   the postal code
    */
   void              SetRightPostalCode(const char* szPostalCode) { m_strRPostalCode = szPostalCode; };
   /**
    * Get the postal code for the right side of the link.
    * @return    the postal code
    */
   const CMQString&  GetRightPostalCode() const { return m_strRPostalCode; };
   /**
    * Set the postal code for the left side of the link.
    * @param szPostalCode   the postal code
    */
   void              SetLeftPostalCode(const char* szPostalCode) { m_strLPostalCode = szPostalCode; };
   /**
    * Get the postal code for the left side of the link.
    * @return    the postal code
    */
   const CMQString&  GetLeftPostalCode() const { return m_strLPostalCode; };

   /**
    * Set the high address range for the right side of the link.
    * @param szAddressHi   the high address range
    */
   void              SetRightAddressHi(const char* szAddressHi) { m_strRAddressHi = szAddressHi; };
   /**
    * Get the high address range for the right side of the link.
    * @return    the high address range
    */
   const CMQString&  GetRightAddressHi() const { return m_strRAddressHi; };
   /**
    * Set the high address range for the left side of the link.
    * @param szAddressHi   the high address range
    */
   void              SetLeftAddressHi(const char* szAddressHi) { m_strLAddressHi = szAddressHi; };
   /**
    * Get the high address range for the left side of the link.
    * @return    the high address range
    */
   const CMQString&  GetLeftAddressHi() const { return m_strLAddressHi; };

   /**
    * Set the low address range for the right side of the link.
    * @param szAddressLo   the low address range
    */
   void              SetRightAddressLo(const char* szAddressLo) { m_strRAddressLo = szAddressLo; };
   /**
    * Get the low address range for the right side of the link.
    * @return    the low address range
    */
   const CMQString&  GetRightAddressLo() const { return m_strRAddressLo; };
   /**
    * Set the low address range for the left side of the link.
    * @param szAddressLo   the low address range
    */
   void              SetLeftAddressLo(const char* szAddressLo) { m_strLAddressLo = szAddressLo; };
   /**
    * Get the low address range for the left side of the link.
    * @return    the low address range
    */
   const CMQString&  GetLeftAddressLo() const { return m_strLAddressLo; };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1520};
#else
   static const int   CLASS_ID = 1520;
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
   CMQLatLngCollection* m_LLCollection;
   // {secret}
   CMQPointCollection*  m_XYCollection;
   // {secret}
   CMQLatLng*      m_LL;
   // {secret}
   CMQPoint*       m_XY;

   // {secret}
   CMQString      m_strLPostalCode;
   // {secret}
   CMQString      m_strRPostalCode;
   // {secret}
   CMQString      m_strLAddressHi;
   // {secret}
   CMQString      m_strRAddressHi;
   // {secret}
   CMQString      m_strLAddressLo;
   // {secret}
   CMQString      m_strRAddressLo;
};


/**
 * describes a polygon feature
 * @ingroup Mapquest
 */
class CMQPolygonFeature : public CMQFeature
{
public:
   /**
    * Constructors
    */
   CMQPolygonFeature();
   /**
    * Constructors
    * @param Object Object to copy
    */
   CMQPolygonFeature(CMQPolygonFeature& Object);

   /**
    * Destructor
    */
   virtual ~CMQPolygonFeature();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQPolygonFeature& operator=(const CMQPolygonFeature& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQPolygonFeature& Object) const;

   /**
    * Get the closest Lat/Lng location of this feature
    * @return    the closest Lat/Lng location of this feature
    */
   CMQLatLng&  GetClosestLatLng()   {return (*m_LL);}
   /**
    * Set the closest Lat/Lng location of this feature
    * @param ll   the closet Lat/Lng location of this feature
    */
   void        SetClosestLatLng(const CMQLatLng& ll)   {(*m_LL) = ll;}

   /**
    * Get the closest point pixel value of this feature
    * @return    the closest point pixel value of this feature
    */
   CMQPoint&   GetClosestPoint() { return (*m_XY); };
   /**
    * Set the closest point pixel location of this feature
    * @param xy   the closest point pixel location of this feature
    */
   void        SetClosestPoint(const CMQPoint& xy)      {(*m_XY) = xy;}
   /**
    * return the polygon feature shape points.
    * @return a reference to a CMQLatLngCollection
    */
   CMQLatLngCollection& GetLatLngs() { return (*m_LLCollection); };

   /**
    * return the polygon feature shape points in display coordinates
    * @return a reference to a CMQPointCollection
    */
   CMQPointCollection&  GetPoints()  { return (*m_XYCollection); };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1530};
#else
   static const int   CLASS_ID = 1530;
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
   CMQLatLngCollection* m_LLCollection;
   // {secret}
   CMQPointCollection*  m_XYCollection;
   // {secret}
   CMQLatLng*      m_LL;
   // {secret}
   CMQPoint*       m_XY;
};

#endif   // _MQFEATURE_H_



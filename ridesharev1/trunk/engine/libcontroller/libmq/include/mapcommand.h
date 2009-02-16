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
#ifndef _MQMAPCOMMAND_H_
// {secret}
#define _MQMAPCOMMAND_H_

#include "mqobject.h"
#include "point.h"
#include "dtcollection.h"
#include "latlngcollection.h"

/**
 * Abstract base class for Map Commands.  Not createable.
 * @ingroup Mapquest
 */
class CMQMapCommand : public CMQObject
{
protected:
   /**
    * Constructor
    */
   CMQMapCommand();
   CMQMapCommand(const CMQMapCommand& aMapCommand);

public:
   /**
    * Destructor
    */
   virtual ~CMQMapCommand() { };

   CMQMapCommand& operator=(const CMQMapCommand& aMapCommand);
   bool operator==(const CMQMapCommand& aMapCommand);
   bool operator!=(const CMQMapCommand& aMapCommand);

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
};


/**
 * MapCommand:Center on display point
 * @ingroup Mapquest
 */
class CMQCenter : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQCenter();
   CMQCenter(const CMQCenter& aCenter);

   /**
    * Destructor
    */
   virtual ~CMQCenter()
   {
      if(m_ptCenter)
         m_ptCenter->Release();
   }

   CMQCenter& operator=(const CMQCenter& aCenter);
   bool operator==(const CMQCenter& aCenter);
   bool operator!=(const CMQCenter& aCenter);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1320};
#else
   static const int   CLASS_ID = 1320;
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
    * Set display point to center map on.
    * @param ptCenter  point to center map on.
    */
   void              SetCenter(const CMQPoint& ptCenter)  { (*m_ptCenter) = ptCenter; }
   /**
    * Get display point to center map on.
    * @return point to center map on.
    */
   const CMQPoint&   GetCenter() const { return (*m_ptCenter); }

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQPoint *m_ptCenter;
};


/**
 * MapCommand:Center on Lat/Lng
 * @ingroup Mapquest
 */
class CMQCenterLL : public CMQMapCommand
{
public:

   /**
    * Constructor
    */
   CMQCenterLL();
   CMQCenterLL(const CMQCenterLL& aCenterLL);

   /**
    * Destructor
    */
   virtual ~CMQCenterLL()
   {
      if(m_llCenter)
         m_llCenter->Release();
   }

   CMQCenterLL& operator=(const CMQCenterLL& aCenterLL);
   bool operator==(const CMQCenterLL& aCenterLL);
   bool operator!=(const CMQCenterLL& aCenterLL);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1330};
#else
   static const int   CLASS_ID = 1330;
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
    * Set Lat/Lng to center map on.
    * @param llCenter  Lat/Lng to center map on.
    */
   void               SetCenter(const CMQLatLng& llCenter)   { (*m_llCenter) = llCenter; }
   /**
    * Get Lat/Lng to center map on.
    * @return Lat/Lng to center map on.
    */
   const CMQLatLng&   GetCenter() const { return (*m_llCenter); }

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQLatLng *m_llCenter;
};


/**
 * MapCommand:ZoomIn on Display point
 * @ingroup Mapquest
 */
class CMQZoomIn : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQZoomIn();
   CMQZoomIn(const CMQZoomIn& aZoomIn);

   /**
    * Destructor
    */
   virtual ~CMQZoomIn()
   {
      if(m_ptCenter)
         m_ptCenter->Release();
   }

   CMQZoomIn& operator=(const CMQZoomIn& aZoomIn);
   bool operator==(const CMQZoomIn& aZoomIn);
   bool operator!=(const CMQZoomIn& aZoomIn);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1340};
#else
   static const int   CLASS_ID = 1340;
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
    * Set display point to zoom in on.
    * @param ptCenter  point to zoom in on.
    */
   void              SetCenter(const CMQPoint& ptCenter)  { (*m_ptCenter) = ptCenter; }
   /**
    * Get display point to zoom in on.
    * @return point to zoom in on.
    */
   const CMQPoint&   GetCenter() const { return (*m_ptCenter); }

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQPoint *m_ptCenter;
};


/**
 * MapCommand:ZoomOut on Display point
 * @ingroup Mapquest
 */
class CMQZoomOut : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQZoomOut();
   CMQZoomOut(const CMQZoomOut& aZoomOut);

   /**
    * Destructor
    */
   virtual ~CMQZoomOut()
   {
      if(m_ptCenter)
         m_ptCenter->Release();
   }

   CMQZoomOut& operator=(const CMQZoomOut& aZoomOut);
   bool operator==(const CMQZoomOut& aZoomOut);
   bool operator!=(const CMQZoomOut& aZoomOut);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1350};
#else
   static const int   CLASS_ID = 1350;
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
    * Set display point to zoom out on.
    * @param ptCenter  point to zoom out on.
    */
   void              SetCenter(const CMQPoint& ptCenter)                  { (*m_ptCenter) = ptCenter; }
   /**
    * Get display point to zoom out on.
    * @return point to zoom out on.
    */
   const CMQPoint&   GetCenter() const { return (*m_ptCenter); }

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQPoint *m_ptCenter;
};


/**
 * MapCommand:ZoomTo on Display point
 * @ingroup Mapquest
 */
class CMQZoomTo : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQZoomTo();
   CMQZoomTo(const CMQZoomTo& aZoomTo);

   /**
    * Destructor
    */
   virtual ~CMQZoomTo()
   {
      if(m_ptCenter)
         m_ptCenter->Release();
   }

   CMQZoomTo& operator=(const CMQZoomTo& aZoomTo);
   bool operator==(const CMQZoomTo& aZoomTo);
   bool operator!=(const CMQZoomTo& aZoomTo);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1342};
#else
   static const int   CLASS_ID = 1342;
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
    * Set display point to zoom in on.
    * @param ptCenter  point to zoom in on.
    */
   void              SetCenter(const CMQPoint& ptCenter)  { (*m_ptCenter) = ptCenter; }
   /**
    * Get display point to zoom in on.
    * @return point to zoom in on.
    */
   const CMQPoint&   GetCenter() const { return (*m_ptCenter); }

   /**
    * Set zoom level index from the AutoMapCovswitch object ZoomLevels property.
    * Has no affect when not using map data selector.
    * @param lZoomLevel  zoom level index
    */
   void              SetZoomLevel(long lZoomLevel)  { m_lZoomLevel = lZoomLevel; }
   /**
    * Get zoom level index from the AutoMapCovswitch object ZoomLevels property.
    * Has no affect when not using map data selector.
    * @return the zoom level index
    */
   long              GetZoomLevel() const { return m_lZoomLevel; }

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQPoint *m_ptCenter;
   long      m_lZoomLevel;
};

/**
 * MapCommand:ZoomToRect - Zoom to a Display point rectangle
 * @ingroup Mapquest
 */
class CMQZoomToRect : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQZoomToRect();
   CMQZoomToRect(const CMQZoomToRect& aZoomToRect);

   /**
    * Destructor
    */
   virtual ~CMQZoomToRect()
   {
      if(m_ULpix)
         m_ULpix->Release();
      if(m_LRpix)
         m_LRpix->Release();
   }

   CMQZoomToRect& operator=(const CMQZoomToRect& aZoomToRect);
   bool operator==(const CMQZoomToRect& aZoomToRect);
   bool operator!=(const CMQZoomToRect& aZoomToRect);


   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1360};
#else
   static const int   CLASS_ID = 1360;
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
    * Set upper left corner of rectangle
    * @param UpperLeft Upper left corner of rectangle
    */
   void              SetUpperLeft(const CMQPoint& UpperLeft)      { (*m_ULpix) = UpperLeft; }
   /**
    * Get upper left corner of rectangle
    * @return Upper left corner of rectangle
    */
   const CMQPoint&   GetUpperLeft() const { return (*m_ULpix); }

   /**
    * Set lower right corner of rectangle
    * @param LowerRight lower right corner of rectangle
    */
   void              SetLowerRight(const CMQPoint& LowerRight)    { (*m_LRpix) = LowerRight; }
   /**
    * Get lower right corner of rectangle
    * @return lower right corner of rectangle
    */
   const CMQPoint&   GetLowerRight() const { return (*m_LRpix); }
   /**
    * Set the rectangle
    * @param UpperLeft Upper left corner of rectangle
    * @param LowerRight lower right corner of rectangle
    */
   void              SetRect(const CMQPoint& UpperLeft,
                             const CMQPoint& LowerRight);
   /**
    * Get the rectangle
    * @param UpperLeft Upper left corner of rectangle
    * @param LowerRight lower right corner of rectangle
    */
   void              GetRect(CMQPoint& UpperLeft,
                             CMQPoint& LowerRight) const;

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQPoint *m_ULpix;
   CMQPoint *m_LRpix;
};


/**
 * MapCommand:ZoomToRectLL - Zoom to a Lat/Lng rectangle
 * @ingroup Mapquest
 */
class CMQZoomToRectLL : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQZoomToRectLL();
   CMQZoomToRectLL(const CMQZoomToRectLL& aZoomToRectLL);

   /**
    * Destructor
    */
   virtual ~CMQZoomToRectLL()
   {
      if(m_UL)
         m_UL->Release();
      if(m_LR)
         m_LR->Release();
   }

   CMQZoomToRectLL& operator=(const CMQZoomToRectLL& aZoomToRectLL);
   bool operator==(const CMQZoomToRectLL& aZoomToRectLL);
   bool operator!=(const CMQZoomToRectLL& aZoomToRectLL);


   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1370};
#else
   static const int   CLASS_ID = 1370;
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
    * Set upper left corner of rectangle
    * @param UpperLeft Upper left corner of rectangle
    */
   void              SetUpperLeft(const CMQLatLng& UpperLeft)      { (*m_UL) = UpperLeft; }
   /**
    * Get upper left corner of rectangle
    * @return Upper left corner of rectangle
    */
   const CMQLatLng&  GetUpperLeft() const { return (*m_UL); }
   /**
    * Set lower right corner of rectangle
    * @param LowerRight lower right corner of rectangle
    */
   void              SetLowerRight(const CMQLatLng& LowerRight)    { (*m_LR) = LowerRight; }
   /**
    * Get lower right corner of rectangle
    * @return lower right corner of rectangle
    */
   const CMQLatLng&  GetLowerRight() const { return (*m_LR); }
   /**
    * Set the rectangle
    * @param UpperLeft Upper left corner of rectangle
    * @param LowerRight lower right corner of rectangle
    */
   void              SetRect(const CMQLatLng& UpperLeft,
                             const CMQLatLng& LowerRight);
   /**
    * Get the rectangle
    * @param UpperLeft Upper left corner of rectangle
    * @param LowerRight lower right corner of rectangle
    */
   void              GetRect(CMQLatLng& UpperLeft,
                             CMQLatLng& LowerRight) const;
protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQLatLng *m_UL;
   CMQLatLng *m_LR;
};


/**
 * MapCommand:Pan - Pan the map but the display point delta.
 * @ingroup Mapquest
 */
class CMQPan : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQPan();
   CMQPan(const CMQPan& aPan);

   /**
    * Destructor
    */
   virtual ~CMQPan()
   {
      if(m_ptDeltaXY)
         m_ptDeltaXY->Release();
   }

   CMQPan& operator=(const CMQPan& aPan);
   bool operator==(const CMQPan& aPan);
   bool operator!=(const CMQPan& aPan);


   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1380};
#else
   static const int   CLASS_ID = 1380;
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
    * Set display point delta.
    * Sets the Delta X and Delta Y variables, which are the number of
    * pixels that the map viewport is to be moved in the horizontal and
    * vertical direction respectively.
    *
    * Delta X:  The number of pixels that the map viewport is to be moved in
    *           the horizontal direction.  Negative indicates movement to the
    *           left, positive to the right.
    *
    * Delta Y:  The number of pixels that the map viewport is to be moved in
    *           the vertical direction.  Negative indicates movement upward,
    *           positive downward.
    * @param ptDeltaXY  display point delta.
    */
   void              SetDeltaXY(const CMQPoint& ptDeltaXY)                  { (*m_ptDeltaXY) = ptDeltaXY; }
   /**
    * Get display point delta
    * @return display point delta.
    */
   const CMQPoint&   GetDeltaXY() const { return (*m_ptDeltaXY); }

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   CMQPoint *m_ptDeltaXY;
};


/**
 * MapCommand:BestFit - Change Scale and center to best fit a group of Features or Primitives.
 * @ingroup Mapquest
 */
class CMQBestFit : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQBestFit();
   CMQBestFit(const CMQBestFit& aBestFit);

   /**
    * Destructor
    */
   virtual ~CMQBestFit()
   {
      if(m_DisplayTypes)
         m_DisplayTypes->Release();
   }

   CMQBestFit& operator=(const CMQBestFit& aBestFit);
   bool operator==(const CMQBestFit& aBestFit);
   bool operator!=(const CMQBestFit& aBestFit);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1390};
#else
   static const int   CLASS_ID = 1390;
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
    * Set the collection of Display type features to perform the best fit on.
    * @param DTs  the collection of Display type features to perform the best fit on
    */
   void                    SetDTs(const CMQDTCollection& DTs)    { (*m_DisplayTypes).Copy(DTs) ; }
   /**
    * Get the collection of Display type features to perform the best fit on.
    * @return the collection of Display type features to perform the best fit on
    */
   const CMQDTCollection&  GetDTs() const { return (*m_DisplayTypes); }

   /**
    * Set the scale adjustment factor.  Adjust the calculated scale by this factor.  1.0 is no adjustment.
    * @param dScaleAdjFactor  the scale adjustment factor
    */
   void SetScaleAdjustmentFactor(double dScaleAdjFactor) { m_dScaleAdjFactor = dScaleAdjFactor; };
   /**
    * Get the scale adjustment factor.
    * @return the scale adjustment factor
    */
   double GetScaleAdjustmentFactor() const { return m_dScaleAdjFactor; };

   /**
    * Set the flag to include primitives in best fit calculation.
    * @param bIncludePrimitives  flag to include primitives in best fit calculation
    */
   void SetIncludePrimitives(bool bIncludePrimitives) { m_bIncludePrimitives = bIncludePrimitives; };
   /**
    * Get the flag to include primitives in best fit calculation
    * @return flag to include primitives in best fit calculation
    */
   bool GetIncludePrimitives() const { return m_bIncludePrimitives; };

   /**
    * Returns the KeepCenter property.  If KeepCenter is true BestFit will
    * use the map center pt. specified by the mapstate object and only adjust the scale.
    * If KeepCenter is false(default) the BestFit will adjust the map center point as well as the scale.
    * @return KeepCenter flag
    */
   bool GetKeepCenter() { return m_bKeepCenter; };

   /**
    * Set the KeepCenter property.  If KeepCenter is true BestFit will
    * use the map center pt. specified by the mapstate object and only adjust the scale.
    * If KeepCenter is false(default) the BestFit will adjust the map center point as well as the scale.
    * @param bKeepCenter  The KeepCenter flag
    */
   void SetKeepCenter(bool bKeepCenter) { m_bKeepCenter = bKeepCenter; };

   /**
    * Get the SnapToZoomLevel property.
    * If SnapToZoomLevel is true BestFit will use a scale from the ZoomLevels property
    * in the AutoMapCovSwitch object.  If AutoMapCovSwitch is not in use this property has no affect.
    * If SnapToZoomLevel is false(default) the BestFit will adjust scale to the best scale that
    * encompasses the area/features selected.
    * @return the SnapToZoomLevel flag
    */
   bool GetSnapToZoomLevel() { return m_bSnapToZoomLevel; };

   /**
    * Set the SnapToZoomLevel property.
    * If SnapToZoomLevel is true BestFit will use a scale from the ZoomLevels property
    * in the AutoMapCovSwitch object.  If AutoMapCovSwitch is not in use this property has no affect.
    * If SnapToZoomLevel is false(default) the BestFit will adjust scale to the best scale that
    * encompasses the area/features selected.
    * @param bSnapToZoomLevel  The SnapToZoomLevel flag
    */
   void SetSnapToZoomLevel(bool bSnapToZoomLevel) { m_bSnapToZoomLevel = bSnapToZoomLevel; };

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQDTCollection *m_DisplayTypes;
   // {secret}
   double m_dScaleAdjFactor;
   // {secret}
   bool m_bIncludePrimitives;
   // {secret}
   bool m_bKeepCenter;
   // {secret}
   bool m_bSnapToZoomLevel;
};


/**
 * MapCommand:BestFitLL - Change Scale and center to best fit a collection of Lat/Lngs.
 * @ingroup Mapquest
 */
class CMQBestFitLL : public CMQMapCommand
{
public:
   /**
    * Constructor
    */
   CMQBestFitLL();
   CMQBestFitLL(const CMQBestFitLL& aBestFitLL);

   /**
    * Destructor
    */
   virtual ~CMQBestFitLL()
   {
      if(m_LatLngs)
         m_LatLngs->Release();
   }

   CMQBestFitLL& operator=(const CMQBestFitLL& aBestFitLL);
   bool operator==(const CMQBestFitLL& aBestFitLL);
   bool operator!=(const CMQBestFitLL& aBestFitLL);

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1391};
#else
   static const int   CLASS_ID = 1391;
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
    * Set the collection of Lat/Lngs to perform the best fit on.
    * @param LatLngs  the collection of Lat/Lngs to perform the best fit on
    */
   void                    SetLatLngs(const CMQLatLngCollection& LatLngs)   { (*m_LatLngs).DeepCopy(LatLngs) ; }

   /**
    * Get the collection of Lat/Lngs to perform the best fit on.
    * @return the collection of Lat/Lngs to perform the best fit on
    */
   const CMQLatLngCollection&  GetLatLngs() const { return (*m_LatLngs); }

   /**
    * Set the scale adjustment factor.  Adjust the calculated scale by this factor.  1.0 is no adjustment.
    * @param dScaleAdjFactor  the scale adjustment factor
    */
   void SetScaleAdjustmentFactor(double dScaleAdjFactor) { m_dScaleAdjFactor = dScaleAdjFactor; };
   /**
    * Get the scale adjustment factor.
    * @return the scale adjustment factor
    */
   double GetScaleAdjustmentFactor() const { return m_dScaleAdjFactor; };

   /**
    * Returns the KeepCenter property.  If KeepCenter is true BestFit will
    * use the map center pt. specified by the mapstate object and only adjust the scale.
    * If KeepCenter is false(default) the BestFit will adjust the map center point as well as the scale.
    * @return KeepCenter flag
    */
   bool GetKeepCenter() { return m_bKeepCenter; };

   /**
    * Set the KeepCenter property.  If KeepCenter is true BestFit will
    * use the map center pt. specified by the mapstate object and only adjust the scale.
    * If KeepCenter is false(default) the BestFit will adjust the map center point as well as the scale.
    * @param bKeepCenter  The KeepCenter flag
    */
   void SetKeepCenter(bool bKeepCenter) { m_bKeepCenter = bKeepCenter; };

   /**
    * Get the SnapToZoomLevel property.
    * If SnapToZoomLevel is true BestFit will use a scale from the ZoomLevels property
    * in the AutoMapCovSwitch object.  If AutoMapCovSwitch is not in use this property has no affect.
    * If SnapToZoomLevel is false(default) the BestFit will adjust scale to the best scale that
    * encompasses the area/features selected.
    * @return the SnapToZoomLevel flag
    */
   bool GetSnapToZoomLevel() { return m_bSnapToZoomLevel; };

   /**
    * Set the SnapToZoomLevel property.
    * If SnapToZoomLevel is true BestFit will use a scale from the ZoomLevels property
    * in the AutoMapCovSwitch object.  If AutoMapCovSwitch is not in use this property has no affect.
    * If SnapToZoomLevel is false(default) the BestFit will adjust scale to the best scale that
    * encompasses the area/features selected.
    * @param bSnapToZoomLevel  The SnapToZoomLevel flag
    */
   void SetSnapToZoomLevel(bool bSnapToZoomLevel) { m_bSnapToZoomLevel = bSnapToZoomLevel; };

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   CMQLatLngCollection *m_LatLngs;
   // {secret}
   double m_dScaleAdjFactor;
   // {secret}
   bool m_bKeepCenter;
   // {secret}
   bool m_bSnapToZoomLevel;
};

#endif   // _MQMAPCOMMAND_H_



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
#ifndef _MQMAPSTATE_H_
// {secret}
#define _MQMAPSTATE_H_

#include "mqobject.h"
#include "point.h"
#include "latlng.h"

/**
 * the current map state to be set or returned from the server
 * @ingroup Mapquest
 */
class CMQMapState : public CMQObject
{
public:
   /**
    * Constructors
    */
   CMQMapState();
   /**
    * Constructors
    * @param Object Object to copy
    */
   CMQMapState(const CMQMapState& Object);

   /**
    * Destructor
    */
   virtual ~CMQMapState();


   static const double mqDblInvalid;

   /**
    * assignment operator
    * @param Object Object to copy
    */
   CMQMapState& operator=(const CMQMapState& Object);
   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQMapState& Object) const;
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQMapState& Object) const;


   /**
    * Set the map center location
    * @param ll   the map center location
    */
   void              SetCenter(const CMQLatLng& ll);
   /**
    * Get the map center location
    * @return    the map center location
    */
   const CMQLatLng&  GetCenter() const;

   /**
    * Set the map image width in Pixels.
    * @param iWidth new width in Pixels
    * @param nDPI DPI to set with respect to. (default = 72)
    */
   void            SetWidthPixels(long iWidth, int nDPI=72);
   /**
    * Set the map image height in Pixels.
    * @param iHeight new height in Pixels
    * @param nDPI DPI to set with respect to. (default = 72)
    */
   void            SetHeightPixels(long iHeight, int nDPI=72);
   /**
    * Get the map image width in pixels.
    * Note Assumes 72DPI, uses inches otherwise
    * @param nDPI Get pixel size with resect to DPI (default = 72)
    * @return map image width in pixels
    */
   long            GetWidthPixels(int nDPI=72) const;
   /**
    * Get the map image height in Pixels.
    * Note Assumes 72DPI, uses inches otherwise
    * @param nDPI Get pixel size with resect to DPI (default = 72)
    * @return map image height in pixels
    */
   long            GetHeightPixels(int nDPI=72) const;



   /**
    * Set the map image width in inches.
    * @param   iWidth new width in inches
    */
   void            SetWidthInches(double iWidth);
   /**
    * Set the map image height in inches.
    * @param   iHeight new height in inches
    */
   void            SetHeightInches(double iHeight);
   /**
    * Get the map image width in inches.
    * @return map image width in inches
    */
   double          GetWidthInches() const;
   /**
    * Get the map image height in inches.
    * @return map image height in inches
    */
   double          GetHeightInches() const;
   /**
    * Set the map scale
    * @param nNewScale   the map scale
    */
   void            SetMapScale(const int nNewScale);
   /**
    * Get the map scale
    * @return    the map scale
    */
   int             GetMapScale() const;
   /**
    * Set the map name
    * @param szName   the map name
    */
   void            SetMapName(const char* szName);
   /**
    * Get the map name
    * @return    the map name
    */
   const CMQString&  GetMapName() const;
   /**
    * Set the coverage name
    * @param szCovId   the coverage name
    */
   void              SetCoverageName(const char* szCovId);
   /**
    * Get the coverage name
    * @return    the coverage name
    */
   const CMQString&  GetCoverageName() const;


   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1190};
#else
   static const int   CLASS_ID = 1190;
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


   // {secret} Internal server methods
   void        SetImageSize(const CMQPoint& imagesize);
   // {secret}
   void        SetImageSize(long cX, long cY);
   // {secret}
   CMQPoint    GetImageSize();

   // {secret}
   void        SetImageSize(const CMQPoint& imagesize, long DPI);
   // {secret}
   void        SetImageSize(long cX, long xY, long DPI);
   // {secret}
   CMQPoint    GetImageSize(long DPI);

protected:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   long              m_nScale;
   // {secret}
   CMQLatLng*        m_llCenter;
   // {secret}
   double            m_dImageWidth;
   // {secret}
   double            m_dImageHeight;
   // {secret}
   CMQString         m_strMapName;
   // {secret}
   CMQString         m_strCoverageName;
   // {secret}
   CMQPoint          m_tmpConvertedtoPixels;
};

#endif   // _MQMAPSTATE_H_



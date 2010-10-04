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
#ifndef _MQPRIMITIVES_H_
// {secret}
#define _MQPRIMITIVES_H_

#include "mqobject.h"
#include "latlngcollection.h"
#include "pointcollection.h"

/**
 * Base class for all primitives.  Not createable.
 * @see CMQPrimitiveCollection
 * @ingroup Mapquest
 */
class CMQPrimitive : public CMQObject
{
protected:
   /**
    * Constructor
    */
   CMQPrimitive();

public:
   /**
    * Destructor
    */
   virtual ~CMQPrimitive();
   /**
    * Initialize all properties to default values
    */
   virtual void Init();

#ifdef _MQ_DEPRECATED_
   /**
    * @deprecated use SetDrawTrigger
    * @param lDrawTrigger  The draw order trigger
    * @see SetDrawTrigger
    */
   void     SetTriggerDT(long lDrawTrigger)
               { SetDrawTrigger(lDrawTrigger); };
   /**
    * @deprecated use GetDrawTrigger
    * @see GetDrawTrigger
    */
   long     GetTriggerDT()
               { return GetDrawTrigger(); };
#endif
   /**
    * Position in draw to order to place primitive.
    * @param lDrawTrigger  The draw order trigger
    * @see CMQDrawTrigger
    */
   void     SetDrawTrigger(long lDrawTrigger)
               { m_lDrawTrigger = lDrawTrigger; };
   /**
    * Position in draw to order to place primitive.
    * @return        The draw order trigger
    * @see CMQDrawTrigger
    */
   long     GetDrawTrigger()
               { return m_lDrawTrigger; };
   /**
    * User key value used for identifying particular primitive in a collection.
    * @param szKey  The user defined key
    */
   void     SetKey(const char* szKey)
               { m_strKey = szKey; };
   /**
    * User key value used for identifying particular primitive in a collection.
    * @return        The user defined key
    */
   const CMQString& GetKey() const
               { return m_strKey; }
   /**
    * Set the coordinate type of the primitive.
    * @param sCoordType   a CMQCoordinateType Value.
    * @see CMQCoordinateType
    */
   void     SetCoordinateType(long sCoordType)
               { m_lCoordinateType = sCoordType; };
   /**
    * Get the coordinate type of the primitive.
    * @return    a CMQCoordinateType Value.
    * @see CMQCoordinateType
    */
   long     GetCoordinateType()
         { return m_lCoordinateType; };

   /**
    * Opacity of the primitve 0-255, 0 being invisible, 255 being opaque
    * 255 or opaque is default.
    * @param lOpacity  The opacity value
    */
   void     SetOpacity(long lOpacity)
               { m_lOpacity = lOpacity; };
   /**
    * Opacity of the primitve 0-255, 0 being invisible, 255 being opaque
    * 255 or opaque is default.
    * @return The opacity value
    */
   long     GetOpacity()
               { return m_lOpacity; };

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
   long  m_lDrawTrigger;
   // {secret}
   CMQString m_strKey;
   // {secret}
   long m_lCoordinateType;
   // {secret}
   long m_lOpacity;
};


/**
 * describes a user added text primitive to the map at the specified draw order
 * @ingroup Mapquest
 */
class CMQTextPrimitive : public CMQPrimitive
{
public:
   /**
    * Constructor.
    */
   CMQTextPrimitive();
   /**
    * Destructor.
    */
   virtual ~CMQTextPrimitive();
   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

// Attributes
protected:
   // {secret}
   long m_lColor;
   // {secret}
   long m_lStyle;
   // {secret}
   long m_lWidth;
   // {secret}
   CMQPoint    *m_ptCenter;
   // {secret}
   CMQLatLng   *m_llCenter;
   // {secret}
   long        m_bgdColor;
   // {secret}
   CMQString   m_strText;
   // {secret}
   long        m_lBoxOutlineColor;
   // {secret}
   long        m_lOutlineColor;
   // {secret}
   CMQString   m_strFontName;
   // {secret}
   long        m_sFontSize;
   // {secret}
   long        m_lMargin;
   // {secret}
   long        m_lTextAlignment;

// Methods
public:
   /**
    * Set the RGB color of the primitive.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void     SetColor(long lColor)
               { m_lColor = lColor; };
   /**
    * Get the RGB color of the primitive.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long     GetColor()
         { return m_lColor; };
   /**
    * Set font style to draw primitive with.
    * @param nStyle   The font style
    * @see CMQFontStyle
    */
   void     SetStyle(long nStyle)
               { m_lStyle = nStyle; };
   /**
    * Get font style to draw primitive with.
    * @return     The font style
    * @see CMQFontStyle
    */
   long     GetStyle()
               { return m_lStyle; };
   /**
    * Line width to draw primitive with (in 1000ths of an inch).
    * @param nWidth  The Line Width
    */
   void     SetWidth(long nWidth)
               { m_lWidth = nWidth; };
   /**
    * Line width to draw primitive with (in 1000ths of an inch).
    * @return        The Line Width
    */
   long     GetWidth()
               { return m_lWidth; };
   /**
    * Set Upper Left pixel value.
    * @param pt  Upper Left pixel value
    */
   void        SetUpperLeftPoint(const CMQPoint& pt)
                  { (*m_ptCenter) = pt; };
   /**
    * Get Upper Left pixel value.
    * @return        Upper Left pixel value
    */
   CMQPoint&   GetUpperLeftPoint()
                  { return (*m_ptCenter); };
   /**
    * Set Upper Left Latitude.
    * @param ll  Upper Left Latitude
    */
   void        SetUpperLeftLatLng(const CMQLatLng& ll)
                  { (*m_llCenter) = ll; };
   /**
    * Get Upper Left Latitude.
    * @return        Upper Left Latitude
    */
   CMQLatLng&  GetUpperLeftLatLng()
                  { return (*m_llCenter); };
   /**
    * Set RGB Background Box Color.
    * @param lVal  RGB Background Box Color
    * @see CMQColorStyle
    */
   void     SetBkgdColor(long lVal)
               { m_bgdColor = lVal; };
   /**
    * Get RGB Background Box Color.
    * @return        RGB Background Box Color
    * @see CMQColorStyle
    */
   long     GetBkgdColor()
               { return m_bgdColor; };
   /**
    * Set Text to be displayed.
    * @param szVal  Text to be displayed
    */
   void     SetText(const char* szVal)
               { m_strText = szVal; };

   /**
    * Set RGB Outline Box Color.
    * @param lVal  RGB Outline Box Color
    * @see CMQColorStyle
    */
   void     SetBoxOutlineColor(long lVal)
               { m_lBoxOutlineColor = lVal; };
   /**
    * Get RGB Outline Box Color.
    * @return        RGB Outline Box Color
    * @see CMQColorStyle
    */
   long     GetBoxOutlineColor()
               { return m_lBoxOutlineColor; };

   /**
    * Set RGB Outline Color.
    * @param lVal  RGB Outline Color
    * @see CMQColorStyle
    */
   void     SetOutlineColor(long lVal)
               { m_lOutlineColor = lVal; };
   /**
    * Get RGB Outline Color.
    * @return        RGB Outline Color
    * @see CMQColorStyle
    */
   long     GetOutlineColor()
               { return m_lOutlineColor; };

   /**
    * Get Text to be displayed.
    * @return        Text to be displayed
    */
   const CMQString& GetText() const
               { return m_strText; };

   /**
    * Set Font Name.
    * @param szVal  Font Name
    */
   void     SetFontName(const char* szVal)
               { m_strFontName = szVal; };
   /**
    * Get Font Name.
    * @return        Font Name
    */
   const CMQString&   GetFontName() const
               { return m_strFontName; };
   /**
    * Set font Size.
    * @param nVal    new font size
    */
   void     SetFontSize(long nVal)
               { m_sFontSize = nVal; };
   /**
    * Get the font size.
    * @returns       the Font size.
    */
   long     GetFontSize()
               { return m_sFontSize; };

   /**
    * Set the margin of the Box surrounding the text.
    * @param lVal    new margin
    */
   void     SetMargin(long lVal)
               { m_lMargin = lVal; };
   /**
    * Get the margin of the Box surrounding the text.
    * @returns       the margin.
    */
   long     GetMargin()
               { return m_lMargin; };
   /**
    * Set the Text Alignment, How text emanates from the center point.
    * @param lVal    new Text Alignment
    * @see CMQTextAlignment
    */
   void     SetTextAlignment(long lVal)
               { m_lTextAlignment = lVal; };
   /**
    * Get the Text Alignment, How text emanates from the center point.
    * @returns       the Text Alignment
    * @see CMQTextAlignment
    */
   long     GetTextAlignment()
               { return m_lTextAlignment; };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1573};
#else
   static const int   CLASS_ID = 1573;
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
 * describes a user added rectangle primitive to the map at the specified draw order
 * @ingroup Mapquest
 */
class CMQRectanglePrimitive  : public CMQPrimitive
{
public:
   /**
    * Constructor
    */
   CMQRectanglePrimitive();
   /**
    * Destructor
    */
   virtual ~CMQRectanglePrimitive();
   /**
    * Initialize all properties to default values
    */
   virtual void Init();

// Attributes
protected:
   // {secret}
   long m_lColor;
   // {secret}
   long m_lStyle;
   // {secret}
   long m_lWidth;
   // {secret}
   CMQPoint    *m_UL;
   // {secret}
   CMQPoint    *m_LR;
   // {secret}
   CMQLatLng   *m_ULLL;
   // {secret}
   CMQLatLng   *m_LRLL;
   // {secret}
   long m_lFillColor;
   // {secret}
   long m_nFillStyle;

// Methods
public:
   /**
    * Set the RGB color of the primitive.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void     SetColor(long lColor)
               { m_lColor = lColor; };
   /**
    * Get the RGB color of the primitive.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long     GetColor()
         { return m_lColor; };
   /**
    * Set pen style to draw primitive outline with.
    * @param nStyle   The Line Style
    * @see CMQPenStyle
    */
   void     SetStyle(long nStyle)
               { m_lStyle = nStyle; };
   /**
    * Get pen style to draw primitive outline with.
    * @return     The Line Style
    * @see CMQPenStyle
    */
   long     GetStyle()
               { return m_lStyle; };
   /**
    * Line width to draw primitive with (in 1000ths of an inch).
    * @param nWidth  The Line Width
    */
   void     SetWidth(long nWidth)
               { m_lWidth = nWidth; };
   /**
    * Line width to draw primitive with (in 1000ths of an inch).
    * @return        The Line Width
    */
   long     GetWidth()
               { return m_lWidth; };

   /**
    * Set Upper Left corner pixel value.
    * @param pt  Upper Left corner pixel value
    */
   void        SetUpperLeftPoint(const CMQPoint& pt)
                  { (*m_UL) = pt; };
   /**
    * Get Upper Left corner pixel value.
    * @return        Upper Left corner pixel value
    */
   CMQPoint&   GetUpperLeftPoint()
                  { return (*m_UL); };

   /**
    * Set Lower Right corner pixel value.
    * @param pt  Lower Right corner X pixel value
    */
   void        SetLowerRightPoint(const CMQPoint& pt)
                  { (*m_LR) = pt; };
   /**
    * Get Lower Right corner pixel value.
    * @return        Lower Right corner pixel value
    */
   CMQPoint&   GetLowerRightPoint()
                  { return (*m_LR); };

   /**
    * Set Upper Left corner Lat/Lng.
    * @param ll  Upper Left corner Lat/Lng
    */
   void        SetUpperLeftLatLng(const CMQLatLng& ll)
                  { (*m_ULLL) = ll; };
   /**
    * Get Upper Left corner Lat/Lng.
    * @return        Upper Left corner Lat/Lng
    */
   CMQLatLng&  GetUpperLeftLatLng()
                  { return (*m_ULLL); };

   /**
    * Set Lower Right corner Lat/Lng.
    * @param ll  Lower Right corner Lat/Lng
    */
   void        SetLowerRightLatLng(const CMQLatLng& ll)
                  { (*m_LRLL) = ll; };
   /**
    * Get Lower Right corner Lat/Lng.
    * @return        Lower Right corner Lat/Lng
    */
   CMQLatLng&  GetLowerRightLatLng()
                  { return (*m_LRLL); };

   /**
    * Set the RGB color to fill this polygon with.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void     SetFillColor(long lColor)
               { m_lFillColor = lColor; };
   /**
    * Get RGB color to fill this polygon with.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long     GetFillColor()
               { return m_lFillColor; };
   /**
    * Set fill style of the primitive
    * @param nStyle   The fill style
    * @see CMQFillStyle
    */
   void     SetFillStyle(long nStyle)
               { m_nFillStyle = nStyle; };
   /**
    * Get fill style of the primitive
    * @return    The fill style
    * @see CMQFillStyle
    */
   long     GetFillStyle()
               { return m_nFillStyle; };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1572};
#else
   static const int   CLASS_ID = 1572;
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
 * describes a user added ellipse primitive to the map at the specified draw order
 * @ingroup Mapquest
 */
class CMQEllipsePrimitive : public CMQRectanglePrimitive
{
public:
   /**
    * Constructor.
    */
   CMQEllipsePrimitive();
   /**
    * Destructor.
    */
   virtual ~CMQEllipsePrimitive();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1571};
#else
   static const int   CLASS_ID = 1571;
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
};


/**
 * describes a user added line primitive to the map at the specified draw order
 * @ingroup Mapquest
 */
class CMQLinePrimitive : public CMQPrimitive
{
public:
   /**
    * Constructor.
    */
   CMQLinePrimitive();
   /**
    * Destructor.
    */
   virtual ~CMQLinePrimitive();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

// Attributes
protected:
   // {secret}
   long m_lColor;
   // {secret}
   long m_lStyle;
   // {secret}
   long m_lWidth;
   // {secret}
   CMQLatLngCollection *m_LLCollection;
   // {secret}
   CMQPointCollection  *m_XYCollection;

// Methods
public:
   /**
    * Set the RGB color of the primitive.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void     SetColor(long lColor)
               { m_lColor = lColor; };
   /**
    * Get the RGB color of the primitive.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long     GetColor()
         { return m_lColor; };
   /**
    * Set pen style to draw primitive with.
    * @param nStyle   The Line Style
    * @see CMQPenStyle
    */
   void     SetStyle(long nStyle)
               { m_lStyle = nStyle; };
   /**
    * Get pen style to draw primitive with.
    * @return     The Line Style
    * @see CMQPenStyle
    */
   long     GetStyle()
               { return m_lStyle; };
   /**
    * Line width to draw primitive with (in 1000ths of an inch).
    * @param nWidth  The Line Width
    */
   void     SetWidth(long nWidth)
               { m_lWidth = nWidth; };
   /**
    * Line width to draw primitive with (in 1000ths of an inch).
    * @return        The Line Width
    */
   long     GetWidth()
               { return m_lWidth; };
   /**
    * Lat/Lng collection of points that make up the line primitive.
    */
   CMQLatLngCollection&    GetLatLngs()
                              {return (*m_LLCollection);}
   /**
    * pixel values collection of points that make up the line primitive.
    */
   CMQPointCollection&     GetPoints()
                              {return (*m_XYCollection);}

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1570};
#else
   static const int   CLASS_ID = 1570;
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
 * describes a user added polygon primitive to the map at the specified draw order
 * @ingroup Mapquest
 */
class CMQPolygonPrimitive : public CMQLinePrimitive
{
public:
   /**
    * Constructor.
    */
   CMQPolygonPrimitive();
   /**
    * Destructor.
    */
   virtual ~CMQPolygonPrimitive();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

// Attributes
protected:
   // {secret}
   long m_lFillColor;
   // {secret}
   long m_nFillStyle;

// Methods
public:
   /**
    * Set the RGB color to fill this polygon with.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void     SetFillColor(long lColor)
               { m_lFillColor = lColor; };
   /**
    * Get RGB color to fill this polygon with.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long     GetFillColor()
               { return m_lFillColor; };
   /**
    * Set fill style of the primitive
    * @param nStyle   The fill style
    * @see CMQFillStyle
    */
   void     SetFillStyle(long nStyle)
               { m_nFillStyle = nStyle; };
   /**
    * Get fill style of the primitive
    * @return    The fill style.
    * @see CMQFillStyle
    */
   long     GetFillStyle()
               { return m_nFillStyle; };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1575};
#else
   static const int   CLASS_ID = 1575;
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
 * describes a user added symbol primitive to the map at the specified draw order
 * @ingroup Mapquest
 */
class CMQSymbolPrimitive : public CMQPrimitive
{
public:
   /**
    * Constructor.
    */
   CMQSymbolPrimitive();
   /**
    * Destructor.
    */
   virtual ~CMQSymbolPrimitive();

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

// Attributes
protected:
   // {secret}
   CMQPoint    *m_ptCenter;
   // {secret}
   CMQLatLng   *m_llCenter;
   // {secret}
   CMQString    m_strSymbolName;
   // {secret}
   long         m_SymbolType;

public:

// Methods
public:
   /**
    * Set center point pixel value.
    * @param pt   center point pixel value
    */
   void        SetCenterPoint(const CMQPoint& pt)
                  { (*m_ptCenter) = pt; };
   /**
    * Get center point pixel value.
    * @return  center point pixel value
    */
   CMQPoint&   GetCenterPoint()
                  { return (*m_ptCenter); };
   /**
    * Set center Lat/Lng.
    * @param ll   center Lat/Lng
    */
   void        SetCenterLatLng(const CMQLatLng& ll)
                  { (*m_llCenter) = ll; };
   /**
    * Get center Lat/Lng.
    * @return  center Lat/Lng
    */
   CMQLatLng&  GetCenterLatLng()
                  { return (*m_llCenter); };
   /**
    * Set Symbol Filename.
    *
    * The Filename should only be specified no extension or path should be included.  The symbol should be
    * placed in the style directory.  Alternately a full path maybe stored here, but is not recommended.
    * @param szVal  Symbol Filename
    */
   void     SetName(const char* szVal)
               { m_strSymbolName = szVal; };
   /**
    * Get symbol Filename.
    * @return        Symbol Filename
    */
   const CMQString& GetName() const
               { return m_strSymbolName; };
   /**
    * Set symbol type.
    * @param nVal   symbol type
    * @see CMQSymbolType
    */
   void     SetSymbolType(long nVal)
               { m_SymbolType=nVal; };
   /**
    * Get symbol type.
    * @return  symbol type
    * @see CMQSymbolType
    */
   long     GetSymbolType()
               { return m_SymbolType; };

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1652};
#else
   static const int   CLASS_ID = 1652;
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

#endif   // _MQPRIMITIVES_H_



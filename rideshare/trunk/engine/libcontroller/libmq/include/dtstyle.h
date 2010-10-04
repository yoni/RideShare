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
#ifndef _MQDTSTYLE_H_
// {secret}
#define _MQDTSTYLE_H_

#include "mqobject.h"
#include "featurespecifiercollection.h"

/**
 * Base Class all DTStyles are derived from.  Not createable.
 * @ingroup Mapquest
 * @see CMQCoverageStyle
 */
class CMQBaseDTStyle : public CMQObject
{
protected:
   /**
    * Constructor
    */
   CMQBaseDTStyle();

public:
   /**
    * Destructor
    */
   virtual ~CMQBaseDTStyle();

   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQBaseDTStyle& Object);
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQBaseDTStyle& Object);

   /**
    * Set the Minimum Scale for this Display Type.
    * The minimum scale to which display type style applies
    * @param lLowScale   The minimum scale for this Display Type
    */
   void              SetLowScale(long lLowScale);
   /**
    * Get the Minimum Scale for this Display Type.
    * The minimum scale to which display type style applies
    * @return    The minimum scale for this Display Type
    */
   long              GetLowScale() const;

   /**
    * Set the Maximum Scale for this Display Type.
    * The maximum scale to which display type style applies
    * @param lHighScale   The maximum scale for this Display Type
    */
   void              SetHighScale(long lHighScale);
   /**
    * Get the Maximum Scale for this Display Type.
    * The maximum scale to which display type style applies
    * @return    The maximum scale for this Display Type
    */
   long              GetHighScale() const;

   /**
    * Set the Display Type.
    * @param nDT   The Display Type
    */
   void              SetDT(int nDT);
   /**
    * Get the Display Type.
    * @return    The Display Type
    */
   int               GetDT() const;

   /**
    * Returns a GeoLocate style string.
    * Returns a GeoLocate style string for a DT, similar to what would appear
    * in a "DT xxx" section of a style file.  (The string begins with the first
    * attribute after "DT xxx".)
    * @param str   The string object in which to place the string
    */
   virtual void GetStyleString(CMQString& str) const = 0;

   /**
    * Initialize all properties to default values.
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
   int       m_nDT;
   // {secret}
   int       m_lLowScale;
   // {secret}
   int       m_lHighScale;
};



/**
 * describes style properties to draw user added or existing features on the map
 * @see CMQCoverageStyle
 * @ingroup Mapquest
 */
class CMQDTStyle : public CMQBaseDTStyle
{
public:
   /**
    * Constructor
    */
   CMQDTStyle();
   /**
    * Destructor
    */
   virtual ~CMQDTStyle();

   /**
    * equality operator
    * @param Object Object to compare
    */
   bool operator==(const CMQDTStyle& Object);
   /**
    * inequality operator
    * @param Object Object to compare
    */
   bool operator!=(const CMQDTStyle& Object);


   /**
    * Set the Name of the Icon for this Display Type.
    * @param szIcon   The Name of the Icon for this Display Type
    */
   void              SetSymbolName(const char* szIcon);
   /**
    * Get Name of the Icon for this Display Type.
    * @return    The Name of the Icon for this Display Type
    */
   const             CMQString& GetSymbolName() const;

   /**
    * Set the Type of Icon for this Display Type.
    * @param sType   The Type of Icon for this Display Type
    * @see CMQSymbolType
    */
   void              SetSymbolType(long sType);
   /**
    * Get the Name of the Icon for this Display Type.
    * @return    The Type of Icon for this Display Type
    * @see CMQSymbolType
    */
   long             GetSymbolType() const;

   /**
    * Set label visible.
    * True = Show the label(if any), False = do not display the label
    * @param bVisible    label visible flag
    */
   void              SetLabelVisible(bool bVisible);
   /**
    * Get label visible.
    * True = Show the label(if any), False = do not display the label
    * @return   label visible flag
    */
   bool          GetLabelVisible() const;

   /**
    * Set visible.
    * True = display DTStyle, False =Hide the objects using this DTStyle
    * @param bVisible    visible flag
    */
   void              SetVisible(bool bVisible);
   /**
    * Get visible.
    * Remarks:
    * True = display DTStyle, False =Hide the objects using this DTStyle
    * @return   visible flag
    */
   bool          GetVisible() const;

   /**
    * Set the font size.
    * @param sSize   The Font Size
    */
   void              SetFontSize(long sSize)
                        { m_sFontSize = sSize; };
   /**
    * Get the font size.
    * @return    The Font Size
    */
   long             GetFontSize() const
                        { return m_sFontSize; };
   /**
    * Set the name of the font to be used.
    * @param szFontName   The name of the font to be used
    */
   void              SetFontName(const char* szFontName)
                        { m_szFontName = szFontName; };
   /**
    * Get the name of the font used.
    * @return    The name of the font used
    */
   CMQString         GetFontName() const
                        { return m_szFontName; };
   /**
    * Set the RGB color of the font.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void              SetFontColor(long lColor)
                        { m_lFontColor = lColor; };
   /**
    * Get the RGB color of the font.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long              GetFontColor() const
                        { return m_lFontColor; };
   /**
    * Set the RGB color of the font outline.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void              SetFontOutlineColor(long lColor)
                        { m_lFontOutlineColor = lColor; };
   /**
    * Get the RGB color of the font outline.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long              GetFontOutlineColor() const
                        { return m_lFontOutlineColor; };
   /**
    * Set the RGB color of the font background box.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void              SetFontBoxBkgdColor(long lColor)
                        { m_lFontBoxBkgdColor = lColor; };
   /**
    * Get the RGB color of the font background box.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long              GetFontBoxBkgdColor() const
                        { return m_lFontBoxBkgdColor; };
   /**
    * Set the RGB color of the font background box outline.
    * @param lColor   a COLORREF formatted color
    * @see CMQColorStyle
    */
   void              SetFontBoxOutlineColor(long lColor)
                        { m_lFontBoxOutlineColor = lColor; };
   /**
    * Get the RGB color of the font background box outline.
    * @return    The color value.
    * @see CMQColorStyle
    */
   long              GetFontBoxOutlineColor() const
                        { return m_lFontBoxOutlineColor; };
   /**
    * Set Box Margin when Boxed Font style is selected.
    * @param lMargin   Box Margin in 1000's of an inch
    */
   void              SetFontBoxMargin(long lMargin);
   /**
    * Get Box Margin when Boxed Font style is selected.
    * @return    Box Margin in 1000's of an inch
    */
   long              GetFontBoxMargin() const;

   /**
    * Set the font style.
    * @param lStyle   The font style
    * @see CMQFontStyle
    */
   void              SetFontStyle(long lStyle)
                        { m_lFontStyle = lStyle; };
   /**
    * Get the font style.
    * @return    The font style
    * @see CMQFontStyle
    */
   long              GetFontStyle() const
                        { return m_lFontStyle; };

   /**
    * Returns a GeoLocate style string.
    * Returns a GeoLocate style string for a DT, similar to what would appear
    * in a "DT xxx" section of a style file.  (The string begins with the first
    * attribute after "DT xxx".)
    * @param str   The string object in which to place the string
    */
   virtual void GetStyleString(CMQString& str) const;

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1060};
#else
   static const int   CLASS_ID = 1060;
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
   CMQString m_strIcon;
   // {secret}
   long      m_sIconType;
   // {secret}
   bool  m_bLabelVisible;
   // {secret}
   bool  m_bVisible;
   // {secret}
   long      m_sFontSize;
   // {secret}
   CMQString m_szFontName;
   // {secret}
   long      m_lFontColor;
   // {secret}
   long      m_lFontOutlineColor;
   // {secret}
   long      m_lFontBoxBkgdColor;
   // {secret}
   long      m_lFontBoxOutlineColor;
   // {secret}
   long      m_lFontStyle;
   // {secret}
   long      m_lFontBoxMargin;
};


/**
 * Describes style properties for a particular Display Type group of features
 * This support Points, Lines and Polygons.
 * @see CMQCoverageStyle
 * @ingroup Mapquest
 */
class CMQDTStyleEx : public CMQBaseDTStyle
{
public:
   /**
    * Constructor
    */
   CMQDTStyleEx();
   /**
    * Destructor
    */
   virtual ~CMQDTStyleEx();

   /**
    * Set the Style String for this Display Type.
    * The Style String to which display type style applies
    * @param szGLString   The Style String for this Display Type
    */
   void SetStyleString(const char* szGLString);
   /**
    * Get the Style String for this Display Type.
    * The Style String to which display type style applies
    * @param str The Style String for this Display Type
    */
   virtual void GetStyleString(CMQString& str) const;

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1062};
#else
   static const int   CLASS_ID = 1062;
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
   CMQString m_szGLStyle;
};


/**
 * describes style properties for a specific feature(s)
 * @see CMQCoverageStyle
 * @ingroup Mapquest
 */
class CMQDTFeatureStyleEx : public CMQBaseDTStyle
{
public:
   /**
    * Constructor
    */
   CMQDTFeatureStyleEx();
   /**
    * Destructor
    */
   virtual ~CMQDTFeatureStyleEx();

   /**
    * Set the Style String for this Display Type.
    * The Style String to which display type style applies
    * @param szGLString   The Style String for this Display Type
    */
   void SetStyleString(const char* szGLString);
   /**
    * Get the Style String for this Display Type.
    * The Style String to which display type style applies
    * @param str  The Style String for this Display Type
    */
   virtual void GetStyleString(CMQString& str) const;

   /**
    * Get the FeatureSpecifierList.
    * The Feature specifier list contains a list of attribute/value pairs describing
    * a specific feature.
    * @return    FeatureSpecifier Collection
    */
   CMQFeatureSpecifierCollection& GetFeatureSpecifiers();

   /**
    * Initialize all properties to default values
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1063};
#else
   static const int   CLASS_ID = 1063;
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
   CMQString m_szGLStyle;
   // {secret}
   CMQFeatureSpecifierCollection* m_FeatureSpecifierList;
};

#endif   // _MQDTSTYLE_H_



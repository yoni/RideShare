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
#ifndef _MQCONSTANTS_H_
// {secret}
#define _MQCONSTANTS_H_

#include "mqobject.h"

/**
 * Map image data Formats. These constants are used to set the image type returned.
 * @see CMQDisplayState
 * @ingroup Constants
 */
class CMQContentType
{
public:
   static const long GIF;    /**< GIF Output */
   static const long EPS;    /**< Standard EPS Output */
   static const long AIEPS;  /**< Adobe Illustrator EPS Output */
   static const long PNG;    /**< PNG Output */
   static const long WBMP;   /**< Wireless Bitmap Output */
};


#ifdef _MQ_DEPRECATED_
/**
 * @deprecated use CMQCoordinateType
 */
class CMQCoordType
{
public:
   static const long sGeographic;   /**< Use the lat/lng values, Primitive should follow geographic coordinates and move when map is repositioned. */
   static const long sDisplay;      /**< Use the X/Y values, Primitive should stay at pixel coordinates and not move when map is repositioned. */
};
#endif

/**
 * Constants to specify the type of coordinate the primitives should use.
 * @see CMQPrimitive
 * @ingroup Constants
 */
class CMQCoordinateType
{
public:
   static const long GEOGRAPHIC;   /**< Use the lat/lng values, Primitive should follow geographic coordinates and move when map is repositioned. */
   static const long DISPLAY;      /**< Use the X/Y values, Primitive should stay at pixel coordinates and not move when map is repositioned. */
};


/**
 * Constants to specify data vencode codes that may be used to alter auto data selection
 * @see CMQAutoMapCovSwitch
 * @see CMQAutoRouteCovSwitch
 * @ingroup Constants
 */
class CMQDataVendorCode
{
public:
   static const long UNKNOWN;       /**< Unknown */
   static const long NT;            /**< NAVTEQ */
   static const long GDT;           /**< GDT */
   static const long DMTI;          /**< DMTI */
   static const long MQ;            /**< MapQuest */
   static const long CA;            /**< MapQuest */
   static const long TIGER;         /**< TIGER */
   static const long ETAK;          /**< ETAK */
   static const long TA;            /**< TeleAtlas */
   static const long AND;           /**< AND */
   static const long VOYAGER;       /**< Voyager */
   static const long CRITCHLOW;     /**< Critchlow */
   static const long LEADDOG;       /**< LeadDog */
   static const long MDS;           /**< MDS */

   static const long USAGE_INCLUDE; /**< Include - Only consider coverages with the given vendors */
   static const long USAGE_EXCLUDE; /**< Exclude - Only consider coverages without the given vendor names */
};


/**
 * Constants to specify the type of geocode results wanted.
 * @see CMQGeocodeOptions
 * @ingroup Constants
 */
class CMQMatchType
{
public:
#ifdef _MQ_DEPRECATED_
   static const int MT_LOC;      /**< @deprecated use LOC    */
   static const int MT_INTR;     /**< @deprecated use INTR   */
   static const int MT_NEARBLK;  /**< @deprecated use NEARBLK*/
   static const int MT_REPBLK;   /**< @deprecated use REPBLK */
   static const int MT_BLOCK;    /**< @deprecated use BLOCK  */
   static const int MT_AA1;      /**< @deprecated use AA1    */
   static const int MT_AA2;      /**< @deprecated use AA2    */
   static const int MT_AA3;      /**< @deprecated use AA3    */
   static const int MT_AA4;      /**< @deprecated use AA4    */
   static const int MT_AA5;      /**< @deprecated use AA5    */
   static const int MT_AA6;      /**< @deprecated use AA6    */
   static const int MT_AA7;      /**< @deprecated use AA7    */
   static const int MT_PC1;      /**< @deprecated use PC1    */
   static const int MT_PC2;      /**< @deprecated use PC2    */
   static const int MT_PC3;      /**< @deprecated use PC3    */
   static const int MT_PC4;      /**< @deprecated use PC4    */
   static const int MT_POI;      /**< @deprecated use POI    */
#endif
   static const int LOC;         /**< Location */
   static const int INTR;        /**< Intersection */
   static const int NEARBLK;     /**< Block - Nearest numbered */
   static const int REPBLK;      /**< Block - Representative (Centroid) */
   static const int BLOCK;       /**< Block */
   static const int AA1;         /**< Admin - Country */
   static const int AA2;         /**< Admin - Division */
   static const int AA3;         /**< Admin - State */
   static const int AA4;         /**< Admin - County */
   static const int AA5;         /**< Admin - City */
   static const int AA6;         /**< Admin - Division (rarely used) */
   static const int AA7;         /**< Admin - smallest division (rarely used) */
   static const int PC1;         /**< Postal - Zip */
   static const int PC2;         /**< Postal - */
   static const int PC3;         /**< Postal - */
   static const int PC4;         /**< Postal - */
   static const int POI;         /**< POI */
};


/**
 * Constants to specify the type of geocode results wanted.
 * @see CMQGeocodeOptions
 * @ingroup Constants
 */
class CMQQualityType
{
public:
#ifdef _MQ_DEPRECATED_
   static const int QT_EXACT;    /**< @deprecated use EXACT   */
   static const int QT_GOOD;     /**< @deprecated use GOOD    */
   static const int QT_APPROX;   /**< @deprecated use APPROX  */
#endif
   static const int EXACT;       /**< Exact */
   static const int GOOD;        /**< Good */
   static const int APPROX;      /**< Approximate */
};


#ifdef _MQ_DEPRECATED_
/**
 * @deprecated use CMQDistanceUnits
 */
class CMQUnits
{
public:
   static const long lMiles;            /**< Distance represented in miles.*/
   static const long lKilometers;       /**< Distance represented in kilometers.*/
};
#endif

/**
 * Constants to specify the type of units returned when calculating distance.
 * @ingroup Constants
 */
class CMQDistanceUnits
{
public:
   static const long MILES;            /**< Distance represented in miles.*/
   static const long KILOMETERS;       /**< Distance represented in kilometers.*/
};

#ifdef _MQ_DEPRECATED_
/**
 * @deprecated use CMQDrawTrigger
 */
class CMQTriggerDT
{
public:
   static const long lBeforePolygons;        /**< Draw Position: Before Polygons*/
   static const long lAfterPolygons;         /**< Draw Position: After Polygons*/
   static const long lBeforeText;            /**< Draw Position: Before Text*/
   static const long lAfterText;             /**< Draw Position: After Text*/
   static const long lBeforeRouteHighlight;  /**< Draw Position: Before Route Highlight*/
   static const long lAfterRouteHighlight;   /**< Draw Position: After Route Highlight*/
};
#endif

/**
 * Constants for draw trigger
 * @see CMQPrimitive
 * @ingroup Constants
 */
class CMQDrawTrigger
{
public:
   static const long BEFORE_POLYGONS;        /**< Draw Position: Before Polygons*/
   static const long AFTER_POLYGONS;         /**< Draw Position: After Polygons*/
   static const long BEFORE_TEXT;            /**< Draw Position: Before Text*/
   static const long AFTER_TEXT;             /**< Draw Position: After Text*/
   static const long BEFORE_ROUTE_HIGHLIGHT; /**< Draw Position: Before Route Highlight*/
   static const long AFTER_ROUTE_HIGHTLIGHT; /**< Draw Position: After Route Highlight*/
};

/**
 * Pen Styles
 * @ingroup Constants
 */
class CMQPenStyle
{
public:
#ifdef _MQ_DEPRECATED_
   static const long sSolid;        /**< @deprecated use SOLID*/
   static const long sDash;         /**< @deprecated use DASH*/
   static const long sDot;          /**< @deprecated use DOT*/
   static const long sDashDot;      /**< @deprecated use DASH_DOT*/
   static const long sDashDotDot;   /**< @deprecated use DASH_DOT_DOT*/
   static const long sNull;         /**< @deprecated use NONE*/
#endif
   static const long SOLID;        /**< Pen Style: Solid*/
   static const long DASH;         /**< Pen Style: Dash*/
   static const long DOT;          /**< Pen Style: Dot*/
   static const long DASH_DOT;     /**< Pen Style: DashDot*/
   static const long DASH_DOT_DOT; /**< Pen Style: DashDotDot*/
   static const long NONE;         /**< Pen Style: None*/
};

#ifdef _MQ_DEPRECATED_
/**
 * @deprecated use CMQFillStyle
 */
class CMQBrushStyle
{
public:
   static const long sSolidFill;    /**< Brush Style: SolidFill*/
   static const long sBDiagonal;    /**< Brush Style: BDiagonal*/
   static const long sCross;        /**< Brush Style: Cross*/
   static const long sDiagCross;    /**< Brush Style: DiagCross*/
   static const long sFDiagonal;    /**< Brush Style: FDiagonal*/
   static const long sHorizontal;   /**< Brush Style: Horizontal*/
   static const long sVertical;     /**< Brush Style: Vertical*/
   static const long sHollow;       /**< Brush Style: Hollow*/
};
#endif


/**
 * Fill Styles
 * @see CMQPolygonPrimitive
 * @see CMQRectanglePrimitive
 * @see CMQEllipsePrimitive
 * @ingroup Constants
 */
class CMQFillStyle
{
public:
   static const long SOLID;        /**< Solid Fill */
   static const long BDIAGONAL;    /**< Backward Diagonal */
   static const long CROSS;        /**< Cross */
   static const long DIAG_CROSS;   /**< Diagonal Cross */
   static const long FDIAGONAL;    /**< Forward Diagonal */
   static const long HORIZONTAL;   /**< Horizontal */
   static const long VERTICAL;     /**< Vertical */
   static const long NONE;         /**< None */
};


/**
 * Constants for the symbol type in a DTStyle and SymbolPrimitives.
 * @ingroup Constants
 * @see CMQDTStyle
 * @see CMQSymbolPrimitive
 */
class CMQSymbolType
{
public:
#ifdef _MQ_DEPRECATED_
   static const long sRaster;      /**< @deprecated use RASTER*/
   static const long sVector;      /**< @deprecated use VECTOR*/
#endif
   static const long RASTER;       /**< Symbol Type: Raster (GRF File).*/
   static const long VECTOR;       /**< Symbol Type: Vector (GMF File).*/
};


/**
 * Constants for the font style in a DTStyle and TextPrimitives.
 * When using DTStyles you may reset the font style back to the its default style from the style
 * file state by specifying CMQFontStyle::INVALID.
 * @ingroup Constants
 */
class CMQFontStyle
{
public:
#ifdef _MQ_DEPRECATED_
   static const long lNormal;       /**< @deprecated use NORMAL*/
   static const long lBold;         /**< @deprecated use BOLD*/
   static const long lBoxed;        /**< @deprecated use BOXED*/
   static const long lOutlined;     /**< @deprecated use OUTLINED*/
   static const long lItalics;      /**< @deprecated use ITALICS*/
   static const long lUnderline;    /**< @deprecated use UNDERLINE*/
   static const long lStrikeout;    /**< @deprecated use STRIKEOUT*/
   static const long lThin;         /**< @deprecated use THIN*/
   static const long lSemiBold;     /**< @deprecated use SEMIBOLD*/
   static const long lInvalid;      /**< @deprecated use INVALID*/
#endif
   static const long NORMAL;       /**< Font Style: Normal*/
   static const long BOLD;         /**< Font Style: Bold*/
   static const long BOXED;        /**< Font Style: Boxed*/
   static const long OUTLINED;     /**< Font Style: Outline*/
   static const long ITALICS;      /**< Font Style: Italics*/
   static const long UNDERLINE;    /**< Font Style: Underline*/
   static const long STRIKEOUT;    /**< Font Style: Strikeout*/
   static const long THIN;         /**< Font Style: Thin*/
   static const long SEMIBOLD;     /**< Font Style: SemiBold*/
   static const long INVALID;      /**< Font Style: Invalid*/
};


#ifdef _MQ_DEPRECATED_
/**
 * @deprecated use CMQColorStyle
 */
class CMQColor
{
public:
   static const long lBlack;        /**< Color: lBlack*/
   static const long lBlue;         /**< Color: lBlue*/
   static const long lCyan;         /**< Color: lCyan*/
   static const long lDarkGray;     /**< Color: lDarkGray*/
   static const long lGray;         /**< Color: lGray*/
   static const long lGreen;        /**< Color: lGreen*/
   static const long lLightGray;    /**< Color: lLightGray*/
   static const long lMagenta;      /**< Color: lMagenta*/
   static const long lOrange;       /**< Color: lOrange*/
   static const long lPink;         /**< Color: lPink*/
   static const long lRed;          /**< Color: lRed*/
   static const long lWhite;        /**< Color: lWhite*/
   static const long lYellow;       /**< Color: lYellow*/
   static const long lInvalid;      /**< Color: lInvalid*/
};
#endif


/**
 * Constants used for specifying color values.
 * Parameters may also specify this value using standard RGB(x,y,z) in the Windows API.
 * When using DTStyles you may reset the color back to the its default color from the style
 * file state by specifying CMQColorStyle::lInvalid.
 * @ingroup Constants
 */
class CMQColorStyle
{
public:
   static const long BLACK;        /**< Color: Black*/
   static const long BLUE;         /**< Color: Blue*/
   static const long CYAN;         /**< Color: Cyan*/
   static const long DARK_GRAY;    /**< Color: DarkGray*/
   static const long GRAY;         /**< Color: Gray*/
   static const long GREEN;        /**< Color: Green*/
   static const long LIGHT_GRAY;   /**< Color: LightGray*/
   static const long MAGENTA;      /**< Color: Magenta*/
   static const long ORANGE;       /**< Color: Orange*/
   static const long PINK;         /**< Color: Pink*/
   static const long RED;          /**< Color: Red*/
   static const long WHITE;        /**< Color: White*/
   static const long YELLOW;       /**< Color: Yellow*/
   static const long INVALID;      /**< Color: Invalid*/
};


/**
 * Constants for the attribute type of a FeatureSpecifier object.
 * use to select the attribute of a feature you want to match
 * @ingroup Constants
 */
class CMQFeatureSpeciferAttributeType
{
public:
#ifdef _MQ_DEPRECATED_
   static const long lGEFID;        /**< @deprecated use GEFID*/
   static const long lName;         /**< @deprecated use NAME*/
#endif
   static const long GEFID;         /**< FeatureSpeciferAttributeType: GEFID.*/
   static const long NAME;          /**< FeatureSpeciferAttributeType: Name.*/
};


/**
 * Constants for the data types for fields in the database.
 * @ingroup Constants
 */
class CMQDBFieldType
{
public:
#ifdef _MQ_DEPRECATED_
   static const long lVarChar;     /**< @deprecated use VARCHAR*/
   static const long lNumeric;     /**< @deprecated use NUMERIC*/
#endif
   static const long VARCHAR;      /**< DBFieldType: VarChar.*/
   static const long NUMERIC;      /**< DBFieldType: Numeric.*/
};

/**
 * Constants for the types for encryption.
 * @ingroup Constants
 */
class CMQEncryptionType
{
public:
#ifdef _MQ_DEPRECATED_
   static const long lNone;            /**< @deprecated use NONE*/
   static const long lRandomShuffle;   /**< @deprecated use RANDOM_SHUFFLE*/
#endif
   static const long NONE;             /**< EncryptionType: None*/
   static const long RANDOM_SHUFFLE;   /**< EncryptionType: RandomShuffle*/
};


/**
 * Constants for the types for Text Alignment
 * @ingroup Constants
 * @see CMQTextPrimitive
 */
class CMQTextAlignment
{
public:
#ifdef _MQ_DEPRECATED_
   static const long lCenter;    /**< @deprecated use CENTER*/
   static const long lLeft;      /**< @deprecated use LEFT*/
   static const long lRight;     /**< @deprecated use RIGHT*/
   static const long lBaseline;  /**< @deprecated use BASELINE*/
   static const long lBottom;    /**< @deprecated use BOTTOM*/
   static const long lTop;       /**< @deprecated use TOP*/
#endif
   static const long CENTER;    /**< TextAlignment: Center*/
   static const long LEFT;      /**< TextAlignment: Left*/
   static const long RIGHT;     /**< TextAlignment: Right*/
   static const long BASELINE;  /**< TextAlignment: Baseline*/
   static const long BOTTOM;    /**< TextAlignment: Bottom*/
   static const long TOP;       /**< TextAlignment: Top*/
};

#endif   // _MQCONSTANTS_H_



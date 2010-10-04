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
#ifndef _MQSIGN_H_
// {secret}
#define _MQSIGN_H_

#include "mqobject.h"

/**
 * A class that contains all of the attributes and behaviors of a sign.
 * @ingroup Mapquest
 */
class CMQSign : public CMQObject
{
public:
   /**
    * Constructor
    */
   CMQSign();
   /**
    * Constructor
    * @param src Object to copy
    */
   CMQSign(const CMQSign &src);

   /**
    * Destructor
    */
   virtual ~CMQSign();

   /**
    * assignment operator
    * @param src Object to copy
    */
   CMQSign& operator=(const CMQSign& src);

   /**
    * Get the type.
    *
    * LIST OF VALUES:
    *    0    No sign
    *    32   No sign
    *
    *    United States Road Shield Tokens
    *    1    Interstate
    *    2    US Highway
    *    3    State Route
    *    4    County Route / Parish Route
    *    5    Interstate Business
    *    10   Farm to Market (FM)
    *    11   Bureau of Indian Affairs (BIA)
    *
    *    Puerto Rico Road Shield Tokens
    *    15   Carr
    *    16   Carretera
    *
    *    US Virgin Islands Road Shield Tokens
    *    19   National Roads
    *
    *    Canada Road Shield Tokens
    *    20   Trans Canada Highway
    *    21   Autoroute
    *    22   Primary Provincial Route
    *    23   Provincial Secondary Route
    *    24   District Route / Regional Route
    *    25   Yellowhead Highway
    *
    *    United Kingdom Road Shield Tokens
    *    30   Motorway / M Road
    *    31   National / A Road
    *    32   * DO NOT USE (ASCII space) *
    *    33   Regional / B Road
    *    34   C Road
    *
    *    Brazil Road Shield Tokens
    *    35  National
    *    36  State
    *
    *    Mexico Road Shield Tokens
    *    40   Federal Route
    *    41   Route Type 2
    *    42   State Route
    *
    *    Argentina Road Shield Tokens
    *    45  National
    *    46  Provincial
    *
    *    European Road Shield Tokens
    *    50   European / E Road
    *
    *    Andorra Road Shield Tokens
    *    52   Carretera General
    *    53   Carretera Secundaria
    *
    *    Austria Road Shield Tokens
    *    55   Autobahnen
    *    56   Schnellstrassen
    *    57   Bundersstrassen
    *    58   Landestrassen / Bezirkstrassen / Privatstrassen des Bundes
    *
    *    Belgium Road Shield Tokens
    *    60   Autosnelwegen
    *    61   Gewestwegen
    *    62   Bretelles / Ring / Regionaalwegen
    *
    *    Denmark Road Shield Tokens
    *    65   Primaerrute
    *    66   Sekendaerrute
    *
    *    Finland Road Shield Tokens
    *    70   Valtatie
    *    71   Kantatie
    *    72   Seututie
    *    73   Muun Yleisen Tie
    *
    *    France / Monaco Road Shield Tokens
    *    75   Autoroutes
    *    76   Routes Nationales
    *    77   Departmentale Strategique / Routes Departmentales
    *    78   Voie Communale, Chemin Rural / Vicinal / Communal
    *    79   Local
    *
    *    Germany Road Shield Tokens
    *    80   Autobahnen
    *    81   Bundesstrassen
    *
    *    Italy / San Marino / Vatican City State Road Shield Tokens
    *    90   Autostrada
    *    91   Strada Statale
    *    92   Strada Provinciale / Strada Regionale
    *
    *    Luxembourg Road Shield Tokens
    *    95   Autoroute A
    *    96   Routes Nationales
    *    97   Chemins Repris
    *    98   Autoroute B
    *
    *    The Netherlands (Holland) Road Shield Tokens
    *    100  Autosnelwegen
    *    101  Nationale wegen
    *    102  Stadsroutenummmers
    *
    *    Norway Road Shield Tokens
    *    105  Riksveg
    *    106  Fylkeveg
    *
    *    Portugal Road Shield Tokens
    *    110  Autostrada
    *    111  Itinerario Principal
    *    112  Itinerario Complementar
    *    113  Estrada Nacional
    *    114  Estrada Municipal
    *
    *    Spain Road Shield Tokens
    *    115  Autopista
    *    116  Nacional
    *    117  Autonomica 1st order
    *    118  Autonomica 2nd order / Autonomica Local
    *    119  Autonomica Local
    *
    *    Sweden Road Shield Tokens
    *    120  Riksvag
    *    121  Lansvag
    *
    *    Switzerland / Liechtenstein Road Shield Tokens
    *    125  Autostrassen
    *    126  Haupstrassen
    *
    *    Czech Republic Road Shield Tokens
    *    130  Dalnice
    *    131  Silnice
    *
    *    Greece Road Shield Tokens
    *    140  National Roads
    *
    *    Russia Road Shield Tokens
    *    145 Motorways
    *    146 National
    *
    *    Ukraine Road Shield Tokens
    *    147 M (Level 2) Roads
    *    148 P (Level 3) Roads
    *    149 Level 4 Roads
    *
    *    Hungary Road Shield Tokens
    *    150  Autopalya (Motorways)
    *    151  Orszagut (Country Roads)
    *
    *    Bosnia and Herzegovina Road Shield Tokens
    *    152  Autoput
    *    153  Magistralni Put
    *    154  Regionalni Put
    *
    *    Estonia Road Shield Tokens
    *    155  Pohimaantee  (Motorway)
    *    156  Tugimaantee  (National)
    *    157  Korvalmaantee (Regional)
    *
    *    Poland Road Shield Tokens
    *    160  Autostrada (Motorways
    *    161  Drogo Ekspresowa (Expressway)
    *    162  Drogo Krajowa (National Road)
    *    163  Drogo Wojewodzka (Regional Road)
    *
    *    Latvia Road Shield Tokens
    *    165  Galvenie Autoceii (Motorway)
    *    166  Skiras Autoceii  (1st class road)
    *    167  Skiras Autoceii  (2nd class road)
    *
    *    Bulgaria Road Shield Tokens
    *    168 Magistrala (Motorway)
    *    169 Put (National Road)
    *
    *    Slovak Republic Road Shield Tokens
    *    170  Dialnice
    *    171  Cesty
    *
    *    Albania Road Shield Tokens
    *    172  Route Type 2
    *    173  Route Type 3
    *
    *    Lithuania Road Shield Tokens
    *    175  Magistraliniai Keliai
    *    176  Krasto Keliai
    *    177  Rajoniniai Keliai
    *
    *    Moldova Road Shield Tokens
    *    178  M (Level 2) Roads
    *    179  R (Level 3) Roads
    *
    *    Slovenia Road Shield Tokens
    *    180  Avtocesta
    *    181  Hitra Cesta
    *    182  Glavna Cesta
    *    183  Regionalna Cesta
    *
    *    Croatia Road Shield Tokens
    *    185  Autocesta
    *    186  Drzavna
    *    187  Zupanijska Cesta
    *
    *    Romania Road Shield Tokens
    *    190  Class 2 (A1, A2)
    *    191  Class 3
    *    192  Class 4
    *
    *    United Arab Emirates Road Shield Tokens
    *    200  Federal
    *    201  Emirate
    *
    *    Oman Road Shield Tokens
    *    205  Class 1
    *    206  Class 2
    *
    *    Bahrain Road Shield Tokens
    *    208  Highway Class 2
    *
    *    Kuwait Road Shield Tokens
    *    210  Ring Road
    *    211  2 Digit State Route
    *
    *    Saudi Arabia Road Shield Tokens
    *    212  Class 1
    *    213  Class 2
    *    214  Class 3
    *
    *    Hong Kong Road Shield Tokens
    *    215  Highway
    *
    *    Taiwan Road Shield Tokens
    *    220  National Freeway
    *    221  Provincial Highway
    *    222  County Highway
    *
    *    Singapore Road Shield Tokens
    *    225  Level 1 Roads
    *    226  Level 3 Roads
    *
    *    Malaysia Road Shield Tokens
    *    230  Level 1 Roads
    *    231  Level 3 Roads
    *
    *    Australia Road Shield Tokens
    *    235  Freeway
    *    236  Highway/ National
    *    237  State
    *    238  Metropolitan
    *    239  Tourist
    *
    *    New Zealand Road Shield Tokens
    *    240  State
    *
    *    South Africa Road Shield Tokens
    *    245  National
    *    246  Regional
    *    247  Metro
    *
    *    Exit sign information
    *    1001 Exit number
    *
    * @return  long value representing type.
    */
   long GetType() const;

   /**
    * Set the type.
    * @param type  long value representing type.
    * @see   CMQSign::GetType() for list of values.
    */
   void SetType(long type);

   /**
    * Get the text.
    * @return the text.
    */
   const CMQString& GetText() const;
   /**
    * Set the text.
    * @param text const char* string for the text.
    */
   void SetText(const char* text);

   /**
    * Get the extra text.
    * @return the extra text.
    */
   const CMQString& GetExtraText() const;
   /**
    * Set the extra text.
    * @param extraText const char* string for the extra text.
    */
   void SetExtraText(const char* extraText);

   /**
    * Get the direction value.
    * @return  direction value.
    */
   long GetDirection() const;
   /**
    * Set the direction value.
    * @param direction  direction value.
    */
   void SetDirection(long direction);

   /**
    * Initialize all properties to default values.
    */
   virtual void Init();

   /**
    * Numeric id of this class
    */
#if (defined(_MSC_VER) && (_MSC_VER <= 1200))
   enum              {CLASS_ID = 1670};
#else
   static const int   CLASS_ID = 1670;
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

private:
   // {secret}
   virtual void ReadPropertiesXML(CMQXMLFormatter& io, long lVersion = -1);
   // {secret}
   virtual void WritePropertiesXML(CMQXMLFormatter& io) const;
   // {secret}
   virtual void WritePropertiesJSON(CMQJSONFormatter& io) const;

   // {secret}
   long m_lType;
   // {secret}
   CMQString m_strText;
   // {secret}
   CMQString m_strExtraText;
   // {secret}
   long m_lDirection;
};

#endif   // _MQSIGN_H_



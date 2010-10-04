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

// mqif - lib

#include <authentication.h>
#include <automapcovswitch.h>
#include <autoroutecovswitch.h>
#include <autogeocodecovswitch.h>
#include <classfactory.h>
#include <coveragestyle.h>
#include <dblayerquery.h>
#include <dblayerquerycollection.h>
#include <dbtodtmap.h>
#include <displaystate.h>
#include <dtcollection.h>
#include <dtstyle.h>
#include <feature.h>
#include <featurecollection.h>
#include <featurespecifier.h>
#include <featurespecifiercollection.h>
#include <geocodeoptions.h>
#include <geocodeoptionscollection.h>
#include <idencrit.h>
#include <intcollection.h>
#include <latlng.h>
#include <latlngcollection.h>
#include <location.h>
#include <maneuver.h>
#include <maneuvercollection.h>
#include <mapcommand.h>
#include <mapstate.h>
#include <mqconstants.h>
#include <mqobject.h>
#include <objectcollection.h>
#include <point.h>
#include <pointcollection.h>
#include <primitivecollection.h>
#include <primitives.h>
#include <recordset.h>
#include <routematrixresults.h>
#include <routeoptions.h>
#include <routeresults.h>
#include <session.h>
#include <sessionif.h>
#include <srchcrit.h>
#include <stringcollection.h>
#include <trekroute.h>
#include <trekroutecollection.h>

// -- Depricated Constants  use CMQXXXXX::CLASS_NAME or CLASS_ID
#ifdef _MQ_DEPRECATED_
#include <mqdefs.h>
#endif

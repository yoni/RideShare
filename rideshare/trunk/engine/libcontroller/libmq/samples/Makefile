############################################################################## 
#  Copyright (C) 1996-2003 MapQuest.com Inc. All Rights Reserved.
#
#  This software is the confidential and proprietary information of 
#  MapQuest.com Inc. ("Confidential Information"). You shall not disclose such
#  Confidential Information and shall use it only in accordance with the terms
#  of the license agreement you entered into with MapQuest.com Inc.
#
#  MAPQUEST.COM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY
#  OF THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
#  PURPOSE, OR NON-INFRINGEMENT. MAPQUEST.COM SHALL NOT BE LIABLE FOR ANY
#  DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR
#  DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
#
#  Makefile for MapQuest Enterprise Unix C++ Simple Samples
# 
##############################################################################
PLATFORM=linux

ifeq ($(PLATFORM),linux)
	LIBDIRS=-L../lib #  RHEL AS 4.0 gnu 3.4.5 support  	
	LIBS= -lnsl -lpthread
	COMPILE=g++
	STATIC_FLAG = -Xlinker -Bstatic
	DYNAMIC_FLAG = -Xlinker -Bdynamic
endif

INCLUDEDIRS=-I. -I../include
INCFLAGS=-c

LIBFLAGS=-o

LIBS +=  -mt $(STATIC_FLAG) -lmqexec -lmqif -lmqosutil -lxml2 $(DYNAMIC_FLAG)
#LIBS +=  -mt $(STATIC_FLAG) -lcontroller $(DYNAMIC_FLAG)

ALL : mapIt\
	geocodeIt\
	routeItWithServerSession\
	routeItNoServerSession\
	SearchIt\
	SearchAndDisplayIt\
	SearchAndDisplayItWithRouteDistance\
	mapWithPOI\
	mapItWithPrimitives

mapIt: mapIt.o
	$(COMPILE) $(LIBFLAGS) mapIt mapIt.o $(LIBS) $(LIBDIRS)
  
geocodeIt: geocodeIt.o
	$(COMPILE) $(LIBFLAGS) geocodeIt geocodeIt.o $(LIBS) $(LIBDIRS)

routeItWithServerSession: routeItWithServerSession.o
	$(COMPILE) $(LIBFLAGS) routeItWithServerSession routeItWithServerSession.o $(LIBS) $(LIBDIRS)

routeItNoServerSession: routeItNoServerSession.o
	$(COMPILE) $(LIBFLAGS) routeItNoServerSession routeItNoServerSession.o $(LIBS) $(LIBDIRS)

SearchIt: SearchIt.o
	$(COMPILE) $(LIBFLAGS) SearchIt SearchIt.o $(LIBS) $(LIBDIRS)

SearchAndDisplayIt: SearchAndDisplayIt.o
	$(COMPILE) $(LIBFLAGS) SearchAndDisplayIt SearchAndDisplayIt.o $(LIBS) $(LIBDIRS)

SearchAndDisplayItWithRouteDistance: SearchAndDisplayItWithRouteDistance.o
	$(COMPILE) $(LIBFLAGS) SearchAndDisplayItWithRouteDistance SearchAndDisplayItWithRouteDistance.o $(LIBS) $(LIBDIRS)

mapWithPOI: mapWithPOI.o
	$(COMPILE) $(LIBFLAGS) mapWithPOI mapWithPOI.o $(LIBS) $(LIBDIRS)

mapItWithPrimitives: mapItWithPrimitives.o
	$(COMPILE) $(LIBFLAGS) mapItWithPrimitives mapItWithPrimitives.o $(LIBS) $(LIBDIRS)
   

mapIt.o: mapIt.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) mapIt.cpp
   
geocodeIt.o: geocodeIt.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) geocodeIt.cpp

mapWithPOI.o: mapWithPOI.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) mapWithPOI.cpp

mapItWithPrimitives.o: mapItWithPrimitives.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) mapItWithPrimitives.cpp

routeItWithServerSession.o: routeItWithServerSession.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) routeItWithServerSession.cpp

routeItNoServerSession.o: routeItNoServerSession.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) routeItNoServerSession.cpp

SearchIt.o: SearchIt.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) SearchIt.cpp

SearchAndDisplayIt.o: SearchAndDisplayIt.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) SearchAndDisplayIt.cpp

SearchAndDisplayItWithRouteDistance.o: SearchAndDisplayItWithRouteDistance.cpp
	$(COMPILE) -DMQUNIX -g $(INCFLAGS) $(INCLUDEDIRS) SearchAndDisplayItWithRouteDistance.cpp

nuke:
	rm -f mapIt
	rm -f geocodeIt
	rm -f routeItWithServerSession
	rm -f routeItNoServerSession
	rm -f SearchIt
	rm -f SearchAndDisplayIt
	rm -f SearchAndDisplayItWithRouteDistance
	rm -f mapWithPOI
	rm -f mapItWithPrimitives


clean:
	rm -f mapIt.o
	rm -f geocodeIt.o
	rm -f routeItWithServerSession.o
	rm -f routeItNoServerSession.o
	rm -f SearchIt.o
	rm -f SearchAndDisplayIt.o
	rm -f SearchAndDisplayItWithRouteDistance.o
	rm -f mapWithPOI.o
	rm -f mapItWithPrimitives.o



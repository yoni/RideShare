
PWD=.
#library rules
L_OTARGET=DBAccess.o Utils.o RouteClient.o Solution.o SolutionUtils.o Match.o 
L_OTARGET+=Optimizer.o BruteForceOptimizer.o BipartiteMatchingOptimizer.o GeneticOptimizer.o RouteOptimizer.o

I_TARGET=DBAccess.hpp Utils.hpp Route.hpp TesterUtil.hpp
I_TARGET+=Preference.hpp RoutePreference.hpp DriverRouteSubmission.hpp Location.hpp
I_TARGET+=RiderRouteSubmission.hpp Rideshare.hpp RoutePreference.hpp RouteSubmission.hpp
I_TARGET+=TimeWindow.hpp UserPreference.hpp RouteClient.hpp RouteInfo.hpp PointInfo.hpp
I_TARGET+=mqservers.hpp RouteMatrix.hpp Address.hpp UserInfo.hpp Solution.hpp
I_TARGET+=SolutionUtils.hpp Match.hpp RouteMatrixLocal.hpp Optimizer.hpp BruteForceOptimizer.hpp
I_TARGET+=RouteOptimizer.hpp BipartiteMatchingOptimizer.hpp GeneticOptimizer.hpp

L_TARGET=libcontroller.a

# library unit test rule
# since we build the lib here, using RLIB would create 
# a recursive build that would recurse till the earth crashed into the sun
# instead, use LIBS and include -lcontroller
LIBS+=-lcontroller -lboost_date_time -lm
UTARGET=libcontroller_tester
OUNITTEST=tester.o

# mapquest library rules
MQLIBSDIR=$(PWD)/libmq/lib
MQINCDIR=$(PWD)/libmq/include
INCLUDESDIR+=-I$(MQINCDIR) 
LIBSDIR+=-L$(MQLIBSDIR) 
#
include $(PWD)/../Makefiles/std.mk
#
# copy mq files to release dir
all:
	cp $(MQLIBSDIR)/* $(L_RELEASE)
	cp $(MQINCDIR)/* $(I_RELEASE)


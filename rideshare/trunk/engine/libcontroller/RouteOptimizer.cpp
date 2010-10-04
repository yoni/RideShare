#include "RouteOptimizer.hpp"
//#include <boost/shared_ptr.hpp>

namespace optimizer 
{
	
	//typedef boost::shared_ptr< RouteMatrix<double> > RouteMatrixPtr;

	RouteInfo<>           bestRoute;
	RouteMatrixPtr        distanceMatrix;
	map<uint32_t, Rider>  ridersMap;
	Driver::ptr           driver;


	/**
	 * Rider's Starting locs 
	 * ____________
	 * |
	 * | start, r1
	 * | start, r2
	 * | start, r3
	 * |____________
	 *
	 * Ex run
	 * step1:
	 *   Driver -> austin
	 *   	r3's end loc pushed on ending locs array
	 *       Rider's Ending locs 
	 * ____________
	 * | end, r3
	 * |____________
	 * Rider's Starting locs 
	 * ____________
	 * | start, r1
	 * | start, r2
	 * |____________
	 *
	 *  step2:
	 *   Driver -> 3:start -> 2:start -> 1:start -> 1:end -> 2:end -> 3:end
	 *   																									-> 3:end -> 2:end
	 *   																				 -> 2:end -> 1:end -> 3:end
	 *   																				 					-> 3:end -> 1:end
	 *   																				 -> 3:end -> 1:end -> 2:end
	 *   																				          -> 2:end -> 1:end
	 *   															-> 2:end
	 *   															-> 3:end
	 *										    1:start -> 2:start
	 *										    				-> 1:end
	 *										    				-> 3:end
	 *										    3:end   -> 
	 * *
	 *   Driver -> 3:start -> 1:start -> 2:start -> 2:end -> 1:end -> 3:end -> driver:end
	 *
	 *
	 **/
	RouteInfo<> optimizeRouteOrder(const Match& match, RouteMatrixPtr matrix)
	{
		distanceMatrix = matrix;
		RouteInfo<> startRoute;
		driver.reset(new Driver(match.myDriver));
		startRoute.addPointInfo(PointInfo<>(driver->routeId, START, driver->startLoc(), 999999.99, 99999999.99));
		bestRoute = startRoute;

		RouteElements startElementVector;
		Riders riders(match.myRiders.begin(), match.myRiders.end());
		for (size_t ii=0; ii < riders.size(); ii++)
		{
			ridersMap[riders[ii].routeId] = riders[ii];
			RouteElement start;
			start.routeId = riders[ii].routeId;
			start.locType = START;
			start.loc     = riders[ii].startLoc();
			startElementVector.push_back(start);
		}

		optimizeRecursive(startElementVector, startRoute);
		return bestRoute;
	}

	void optimizeRecursive(RouteElements elems, RouteInfo<> rInfo)
	{
		//std::cout<<"Route elements size: : " << elems.size()
			//<< " \t RouteInfo size: " << rInfo.size() << std::endl;
		if (elems.size() == 0)
		{
			PointInfo<> driverEndPoint(driver->routeId, END, driver->endLoc(), 0, 0);
			PointInfo<> & lastPoint = rInfo.getLastPointInfo();
			if(lastPoint.locType == START){
				//case: only driver is in match
				lastPoint.distanceMiles = distanceMatrix->getDistance
					(lastPoint.routeId, START, driverEndPoint.routeId, END);
				lastPoint.timeMinutes   = distanceMatrix->getTime
					(lastPoint.routeId, START, driverEndPoint.routeId, END);
				rInfo.addPointInfo(driverEndPoint);
			}else{
				//case: at least one rider in the match
				lastPoint.distanceMiles = distanceMatrix->getDistance
					(lastPoint.routeId, END, driverEndPoint.routeId, END);
				lastPoint.timeMinutes   = distanceMatrix->getTime
					(lastPoint.routeId, END, driverEndPoint.routeId, END);
				rInfo.addPointInfo(driverEndPoint);
			}

			//std::cout<<"Old distance: " << bestRoute.getRouteDistance() << "\tthis distance: " 
			//	<< rInfo.getRouteDistance() << std::endl;

			if (rInfo.getRouteDistance() < bestRoute.getRouteDistance() )
			{
				bestRoute = rInfo;
				//std::cout<<"New Best route:" << std::endl;
				//bestRoute.printAllPoints();
			}
			return;
		}

		RouteElements::iterator firstElem = elems.begin();
		for(size_t ii=0; ii < elems.size(); ii++)
		{
			RouteElement elem = elems[ii];
			PointInfo<> & lastPoint = rInfo.getLastPointInfo();

			//std::cout<<"Getting distance for routeId" << elem.routeId << " type: " << elem.locType
			//	<< "\t to routeId: " << lastPoint.routeId<< " type: "<< lastPoint.locType<<std::endl;

			lastPoint.distanceMiles = distanceMatrix->getDistance
				(elem.routeId, elem.locType, lastPoint.routeId, lastPoint.locType);

			lastPoint.timeMinutes   = distanceMatrix->getTime
				(elem.routeId, elem.locType, lastPoint.routeId, lastPoint.locType);
			//cout <<"Distance to next point is: "<< lastPoint.distanceMiles << endl;
			//cout <<"Time to next point is: "<< lastPoint.timeMinutes << endl;
	
			PointInfo<> newPoint(elem.routeId, elem.locType, elem.loc, 0, 0);
			rInfo.addPointInfo(newPoint);

			elems.erase(firstElem + ii);
			if (elem.locType == START)
			{
				RouteElement endElem;
				endElem.routeId = elem.routeId;
				endElem.loc     = ridersMap[elem.routeId].endLoc();
				endElem.locType = END;
				elems.push_back(endElem);
			}
			optimizeRecursive(elems, rInfo);
			rInfo.popPointInfo();

			if (elem.locType == START)
			{
				elems.pop_back();
			}
			elems.insert(firstElem + ii, elem);
		}
	}
}


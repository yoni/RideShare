#ifndef _ROUTEMATRIXLOCAL_HPP
#define _ROUTEMATRIXLOCAL_HPP
#include "RouteMatrix.hpp"
#include "RouteMatrix.hpp"
#include "Location.hpp"
#include "math.h"

namespace controller {
	namespace routes {
static const double  pi = 3.14159265358979323846;
static const double  DISTANCE_TIME_CONVERSION = 60 / 45;
class RouteMatrixLocal : public RouteMatrix<>
{
public:
	RouteMatrixLocal()
		: RouteMatrix<>()
	{}

	RouteMatrixLocal(Drivers drivers, Riders riders, Matches matches)
		: RouteMatrix<>()
	{
		initMatrix(drivers, riders, matches);
	}

	~RouteMatrixLocal()
	{
		if (myInternalMatrix)
		{
			size_t numLocs = RouteMatrix<>::myLocations.size();
			for(size_t ii = 0; ii < numLocs; ii++)
			{
				 delete [] myInternalMatrix[ii];
			}
			delete [] myInternalMatrix;
		}
	}
	/**
	 * getDistance()
	 * 	@params
	 * 		start - routeId of starting point
	 * 		end   - routeId of ending point
	 *
	 * 	@returns the distance in miles
	 **/
	double getDistance(uint32_t start, LocationType startType,
			uint32_t end, LocationType endType)
	{
		//std::cout<< "startId: " << start << "\tendId "
		//	<< end << std::endl;
		size_t startIndex = RouteMatrix<>::indexMap[start];
		size_t endIndex   = RouteMatrix<>::indexMap[end];
		if (startType == END)
			startIndex++;

		if (endType == END)
			endIndex++;

		//std::cout<<"Location count: " << myMatrix->GetLocationCount()
		//	<< "starti: " << startIndex << "\tendi " << endIndex << "\n";

		return myInternalMatrix[startIndex][endIndex];
	}

	long getTime(uint32_t start, LocationType startType,
			uint32_t end, LocationType endType)
	{
		size_t startIndex = RouteMatrix<>::indexMap[start];
		size_t endIndex   = RouteMatrix<>::indexMap[end];
		if (startType == END)
			startIndex++;

		if (endType == END)
			endIndex++;

		return static_cast<long>(myInternalMatrix[startIndex][endIndex] * DISTANCE_TIME_CONVERSION);
	}

	static double getDistance(const Location<> &a, const Location<> &b)
	{
		double lat1 = a.lat;
		double lon1 = a.lng;
		double lat2 = b.lat;
		double lon2 = b.lng;
		double theta, dist;
		theta = lon1 - lon2;
		dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
		dist = acos(dist);
		dist = rad2deg(dist);
		dist = dist * 60 * 1.1515;
		return dist;
	}

protected:
	virtual void initMatrix(Drivers drivers, Riders riders, Matches matches)
	{
		size_t curIndex = 0;
		Locations allLocs;
		// add matches to matrix
		for(size_t ii=0; ii < matches.size(); ii++)
		{
			allLocs.push_back(matches[ii].myDriver.startLoc());
			allLocs.push_back(matches[ii].myDriver.endLoc());
			updateIndexMap(matches[ii].myDriver.routeId, curIndex);


			for (size_t rr=0; rr < matches[ii].myRiders.size(); rr++)
			{
				allLocs.push_back(matches[ii].myRiders[rr].startLoc());
				allLocs.push_back(matches[ii].myRiders[rr].endLoc());
				updateIndexMap(matches[ii].myRiders[rr].routeId, curIndex);
			}
		}

		// add drivers to matrix
		for(size_t ii=0; ii < drivers.size(); ii++)
		{
			allLocs.push_back(drivers[ii].startLoc());
			allLocs.push_back(drivers[ii].endLoc());
			updateIndexMap(drivers[ii].routeId, curIndex);
		}
		
		// add riders to matrix
		for(size_t ii=0; ii < riders.size(); ii++)
		{
			allLocs.push_back(riders[ii].startLoc());
			allLocs.push_back(riders[ii].endLoc());
			updateIndexMap(riders[ii].routeId, curIndex);
		}

		// update matrix with values
		RouteMatrix<>::myLocations = allLocs;
		
		initInternalMatrix();
	}

	void initInternalMatrix()
	{
		size_t numLocs = RouteMatrix<>::myLocations.size();
		myInternalMatrix = new double*[numLocs];
		for(size_t ii = 0; ii < numLocs; ii++)
		{
			myInternalMatrix[ii] = new double[numLocs];
		}

		for (size_t xx = 0; xx < numLocs; xx++ )
		{
			for (size_t yy = 0; yy < numLocs; yy++ )
			{
				Location<> * loc1 = &RouteMatrix<>::myLocations[xx];
				Location<> * loc2 = &RouteMatrix<>::myLocations[yy];
				myInternalMatrix[xx][yy] = getDistance(*loc1, *loc2);
			}
		}
	}

private:
	double **myInternalMatrix;
	static double deg2rad(double deg) 
	{ return (deg * pi / 180); }

	static double rad2deg(double rad) 
	{ return (rad * 180 / pi); }

};


}
}
#endif // #ifndef _ROUTEMATRIXLOCAL_HPP

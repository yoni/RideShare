#ifndef _ROUTEMATRIX_HPP
#define _ROUTEMATRIX_HPP

#include <map>
#include <iostream>
#include "RouteClient.hpp"
#include "Location.hpp"
#include "DriverRouteSubmission.hpp"
#include "RiderRouteSubmission.hpp"
#include "Match.hpp"
#include "Utils.hpp"
using std::vector;
using std::map;

using optimizer::Match;

namespace controller {
	namespace routes {


template <class T=double>
class RouteMatrix
{
public:
	typedef vector< Location<T> > Locations;
	typedef RiderRouteSubmission Rider;
	typedef DriverRouteSubmission Driver;
	typedef vector<Rider> Riders;
	typedef vector<Driver> Drivers;
	typedef vector<Match> Matches;
	typedef RouteClient::MQMatrixPtr MQMatrixPtr;

	RouteMatrix()
	{}

	RouteMatrix(CMQRouteMatrixResults &matrix, Locations &locs)
		: myLocations ( locs )
		, myMatrix( new CMQRouteMatrixResults(matrix) )
	{
	
		cout<<"RouteMatrix(CMQRouteMatrixResults,Locations). number of locations: "<<locs.size()<<endl;
	}

	RouteMatrix(Drivers drivers, Riders riders, Matches matches)
	{
		//cout<<"RouteMatrix constructor: #Drivers: "<<drivers.size()<<" #Riders: "<<riders.size()<<" #Matches: " << matches.size()<<endl;
		initMatrix(drivers, riders, matches);
	}

	virtual ~RouteMatrix()
	{}

	RouteMatrix(const Match& match)
	{
		Matches matches;
		Drivers drivers; Riders riders;
		matches.push_back(match);
		initMatrix(drivers, riders, matches);
	}

	uint32_t getLocationCount() const
	{
		return myLocations.size();
	}

	/**
	 * getDistance()
	 * 	@params
	 * 		start - routeId of starting point
	 * 		end   - routeId of ending point
	 *
	 * 	@returns the distance in miles
	 **/
	virtual double getDistance(uint32_t start, LocationType startType,
			uint32_t end, LocationType endType)
	{
		//std::cout<< "startId: " << start << "\tendId "
		//	<< end << std::endl;
		size_t startIndex = indexMap[start];
		size_t endIndex   = indexMap[end];
		if (startType == END)
			startIndex++;

		if (endType == END)
			endIndex++;

		//std::cout<<"Location count: " << myMatrix->GetLocationCount()
			//<< "starti: " << startIndex << "\tendi " << endIndex << "\n";

		return myMatrix->GetDistance(startIndex, endIndex);
	}

	virtual long getTime(uint32_t start, LocationType startType,
			uint32_t end, LocationType endType) 
	{
		size_t startIndex = indexMap[start];
		size_t endIndex   = indexMap[end];
		if (startType == END)
			startIndex++;

		if (endType == END)
			endIndex++;

		return myMatrix->GetTime(startIndex, endIndex);
	}

	void setAttr(CMQRouteMatrixResults &matrix, Locations &locs)
	{
		myLocations = locs;
		myMatrix.reset(new CMQRouteMatrixResults(matrix));
	}
private:
	MQMatrixPtr myMatrix;
protected:

	map<uint32_t,size_t> indexMap;
	Locations myLocations;
	
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
		myLocations = allLocs;
		//cout<<"InitMatrix: number of locations = "<<allLocs.size()<<endl;
		//cout<<"Locations: "<<allLocs[0].lat<<" "<<allLocs[0].lng <<endl;
		//cout<<"Locations: "<<allLocs[1].lat<<" "<<allLocs[1].lng <<endl;
		RouteClient rc;
		rc.setLocations(allLocs);
		myMatrix = rc.getMQRouteMatrixResults();
		//cout<<"Reached the end of initMatrix"<<endl;
	}

	void updateIndexMap(uint32_t routeId, size_t &curIndex)
	{
		indexMap[routeId] = curIndex;
		curIndex += 2;

	}

};



	}
}

#endif // #ifndef _ROUTEMATRIX_HPP

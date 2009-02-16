#ifndef _COMPATIBILITYMATRIX_HPP
#define _COMPATIBILITYMATRIX_HPP
#include "Location.hpp"

namespace controller {
	namespace routes {

enum CompatibilityType { INCOMPATIBLE = 1, MATCHED, NOT_MATCHED };
class optimizer::Match;
class CompatibilityMatrix 
{
public:
	typedef vector< Location<> > Locations;
	typedef RiderRouteSubmission Rider;
	typedef DriverRouteSubmission Driver;
	typedef vector<Rider> Riders;
	typedef vector<Driver> Drivers;
	typedef vector<optimizer::Match> Matches;
	size_t NUM_MATCHES;
	size_t NUM_RIDERS;
protected:
	map<uint32_t,size_t> indexMapMatches;
	map<uint32_t,size_t> indexMapRiders;
	CompatibilityType **myInternalMatrix;
	const Riders  * myRiders;
	const Matches * myMatches;

public:
	CompatibilityMatrix()
		: NUM_MATCHES(0)
		, NUM_RIDERS(0)
		, myInternalMatrix(NULL)
	{}

	/*
	 *
	 * Internal Matrix is M [ NUM_MATCHES ][ NUM_RIDERS ]
	 *
	 */
	CompatibilityMatrix(const Riders *riders, const Matches *matches)
		: NUM_MATCHES( matches->size() )
		, NUM_RIDERS( riders->size() )
		, myRiders( riders )
		, myMatches( matches )
	{
		initIndexMap();
		initInternalMatrix();
	}

	~CompatibilityMatrix()
	{
		if (myInternalMatrix)
		{
			for(size_t ii = 0; ii < NUM_MATCHES; ii++)
			{
				 delete [] myInternalMatrix[ii];
			}
			delete [] myInternalMatrix;
		}
	}

	/**
	 * getCompatibility()
	 * 	@params
	 * 		matchRouteId - routeId of match
	 * 		riderRouteId - routeId of rider
	 *
	 * 	@returns the CompatibilityType between a match and a rider
	 **/
	CompatibilityType getCompatibility(uint32_t matchRouteId, uint32_t riderRouteId)
	{
		size_t matchIndex   = indexMapMatches[matchRouteId];
		size_t riderIndex   = indexMapRiders[riderRouteId];

		std::cout<<"\nMatch Index: " << matchIndex << "\tMatchId: " << matchRouteId;
		std::cout<<"\nRider Index: " << riderIndex << "\tRiderId: " << riderRouteId;
		return myInternalMatrix[matchIndex][riderIndex];
	}

	/**
	 * setCompatibility()
	 * 	@params
	 * 		matchRouteId - routeId of match
	 * 		riderRouteId - routeId of rider
	 * 		type - INCOMPATIBLE, MATCHED, NOT_MATCHED
	 *
	 **/
	void setCompatibilityType(uint32_t matchRouteId, uint32_t riderRouteId, CompatibilityType type)
	{
		size_t matchIndex   = indexMapMatches[matchRouteId];
		size_t riderIndex   = indexMapRiders[riderRouteId];

		std::cout<<"\nMatch Index: " << matchIndex << "\tMatchId: " << matchRouteId;
		std::cout<<"\nRider Index: " << riderIndex << "\tRiderId: " << riderRouteId;
		myInternalMatrix[matchIndex][riderIndex] = type;
	}

protected:
	void initInternalMatrix()
	{
		myInternalMatrix = new CompatibilityType*[NUM_MATCHES];
		for(size_t ii = 0; ii < NUM_MATCHES; ii++)
		{
			myInternalMatrix[ii] = new CompatibilityType[NUM_RIDERS];
		}
		cout<<"Initializing compatibility matrix:"<<endl;
		for (size_t xx = 0; xx < NUM_MATCHES; xx++ )
		{
			for (size_t yy = 0; yy < NUM_RIDERS; yy++ )
			{
				RouteInfo<> dummyRInfo;
				myInternalMatrix[xx][yy] = (*myMatches)[xx].canAddRider( (*myRiders)[yy]) 
																		? NOT_MATCHED : INCOMPATIBLE;
				cout<<"pair (" << (*myMatches)[xx].myDriver.routeId <<","<< 
					(*myRiders)[yy].routeId << ") "<< "value set to: " << myInternalMatrix[xx][yy] << endl;
			}
		}
	}

	void initIndexMap()
	{
		for(size_t mm=0; mm < NUM_MATCHES; mm++)
		{
			uint32_t routeId  = (*myMatches)[mm].myDriver.routeId;
			std::cout<<"I: " << mm << "\t " << "Adding match route Id " << routeId << std::endl;
			indexMapMatches[routeId] = mm;
		}
		for(size_t rr=0; rr < NUM_RIDERS; rr++)
		{
			uint32_t routeId  = (*myRiders)[rr].routeId;
			std::cout<<"I: " << rr << "\t " << "Adding rider route Id " << routeId << std::endl;
			indexMapRiders[routeId] = rr;
		}
		//debug statements
		cout<<"Initializing index map:"<<endl;
		for(map<uint32_t,size_t>::iterator m = indexMapMatches.begin();
				m != indexMapMatches.end();
				m++)
		{
			cout<<"Match id: " << m->first << "Index: " << m->second << endl;
		}
		for(map<uint32_t,size_t>::iterator r = indexMapRiders.begin();
				r != indexMapRiders.end();
				r++)
		{
			cout<<"Rider id: " << r->first << "Index: " << r->second << endl;
		}
	}
};


}
}
#endif // #ifndef _COMPATIBILITYMATRIX_HPP

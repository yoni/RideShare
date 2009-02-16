#ifndef _ROUTEINFO_HPP
#define _ROUTEINFO_HPP
#include <vector>
#include <iostream>
#include "Location.hpp"
#include "PointInfo.hpp"
#include "ifexec.h"
#include "TimeWindow.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace controller
{
namespace routes
{

template <class T=double>
class RouteInfo
{
	public:
		RouteInfo()
		{}

		RouteInfo(const CMQRouteResults &routeResults)
			: mqResults( routeResults )
		{}

		RouteInfo(const RouteInfo &lhs)
		{
			points = lhs.points;
			timeWindows = lhs.timeWindows;
		}

		CMQRouteResults mqResults;

		const  PointInfo<T> & at(size_t index) const { return points[index]; }
		const  PointInfo<T> & operator[](size_t index) const { return points[index]; }
		void   addPointInfo(PointInfo<T> point) { points.push_back(point); }
		void   popPointInfo() { points.pop_back(); }
		void   clear() { points.clear(); }
		size_t size() const { return points.size(); }
		size_t numPoints() const { return points.size(); }

		PointInfo<T> & getLastPointInfo() 
		{ 
			return points[points.size() -1 ];
		}

		/**
		 * getRouteDistance()
		 * 	@desc gets total route distance in miles
		 **/
		double getRouteDistance() const
		{
			double totalDistance = 0.0;
			for(size_t ii = 0; ii < points.size(); ii++)
			{
				totalDistance += points[ii].distanceMiles;
			}
			//std::cout<< "Route distance is: "<<totalDistance<<std::endl;
			return totalDistance;
		}

		/**
		 * getRouteTime()
		 * 	@desc gets total route time in seconds
		 **/
		double getRouteTime() const
		{
			double totalTime = 0.0;
			for(size_t ii = 0; ii < points.size(); ii++)
			{
				totalTime += points[ii].timeMinutes;
			}
			return totalTime;
		}

		void printAllPoints() const
		{
			for (size_t ii = 0 ; ii < points.size(); ii++)
			{
				printPointInfo(ii);
			}
			std::cout<<"\nTotal Distance(mi): " << getRouteDistance() << std::endl;
			std::cout<<"Total Time(mins): " << getRouteTime() << std::endl;
		}

		void printPointInfo(size_t index) const
		{
			PointInfo<T> point = points[index];
			std::cout<<std::endl<<"Point " << index << std::endl;
			std::cout<<"Lat: " << point.loc.lat 
				<< "\tLong: " << point.loc.lng 
				<< "\tStreet: " << point.loc.addr.street 
				<< std::endl;
			//TODO: print time window for this point
			std::cout<<"Distance(mi): " << point.distanceMiles << std::endl;
			std::cout<<"Time(mins): " << point.timeMinutes << std::endl;
			if(timeWindows.size())
			{
				TimeWindow<ptime> tw = timeWindows[index];
				std::cout<<"TimeWindow: ( " << tw.startTime <<" , " << tw.endTime << " )" << std::endl;
			}
		}

		std::vector< TimeWindow<ptime> > timeWindows;
		std::vector< PointInfo<T> > points;
};

} // end routes namespace
} // end controller namepsace
#endif // #ifndef _ROUTEINFO_HPP

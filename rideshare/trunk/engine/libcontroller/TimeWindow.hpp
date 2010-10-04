#ifndef _TIMEWINDOW_HPP
#define _TIMEWINDOW_HPP
#include "mysql++/datetime.h"
#include <boost/date_time/posix_time/posix_time.hpp>


namespace controller 
{
	typedef mysqlpp::DateTime DateTime;
	using namespace boost::posix_time;
	
	/*
	 * TimeWindow has a startTime and endTime
	 */
	template <class S=DateTime>
	class TimeWindow
	{
		public:
			S startTime;
			S endTime;

			TimeWindow()
			{}

			TimeWindow(S _startTime, S _endTime)
				:startTime(_startTime)
				,endTime(_endTime)
			{}
	};
	

}
#endif // #ifndef _TIMEWINDOW_HPP

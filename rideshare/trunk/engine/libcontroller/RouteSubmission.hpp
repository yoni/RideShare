#ifndef _ROUTESUBMISSION_HPP
#define _ROUTESUBMISSION_HPP
#include <string>
#include <boost/shared_ptr.hpp>
#include "Route.hpp"

#include "Location.hpp"
#include "UserPreference.hpp"
#include "RoutePreference.hpp"
#include "UserInfo.hpp"

namespace controller
{

using std::string;


class RouteSubmission : public Route
{
	/**
	 * RouteSubmission
	 *   @desc: holds the fields associated with the Route table
	 **/
	public:
		typedef boost::shared_ptr< RouteSubmission > ptr;

		RouteSubmission(uint32_t _routeId, uint32_t _userId
				, Location<double> _startLoc, Location<double> _endLoc
				, UserPreference _userPref, RoutePreference _routePref
				, double _optimalDistance, string _comment = "")
			: Route(_startLoc, _endLoc, _userPref, _routePref)
			, routeId(_routeId)
			, userId(_userId)
			, optimalDistance(_optimalDistance)
			, comment(_comment)
		{}

		RouteSubmission(uint32_t _routeId, uint32_t _userId
				, Location<double> _startLoc, Location<double> _endLoc
				, UserPreference _userPref, RoutePreference _routePref
				, UserInfo _uInfo, double _optimalDistance
				, string _comment="")
			: Route(_startLoc, _endLoc, _userPref, _routePref)
			, routeId(_routeId)
			, userId(_userId)
			, optimalDistance(_optimalDistance)
			, uInfo( _uInfo )
			, comment(_comment)
		{}

		RouteSubmission(const RouteSubmission& rhs)
			: Route(rhs.startLoc(), rhs.endLoc(), rhs.userPref, rhs.routePref)
			, routeId(rhs.routeId)
			, userId(rhs.userId)
			, optimalDistance(rhs.optimalDistance)
			, uInfo(rhs.uInfo)
			, comment(rhs.comment)
		{}

		virtual ~RouteSubmission()
		{}

		bool operator==(RouteSubmission rhs){
			if(this->routeId==rhs.routeId){ return true;}
			return false;
		}
		bool operator!=(RouteSubmission rhs){
			return !(this->routeId == rhs.routeId);
		}
		bool operator<(RouteSubmission rhs){
			if(this->routeId < rhs.routeId){ return true;}
			return false;
		}
		bool operator>(RouteSubmission rhs){
			if(this->routeId > rhs.routeId){ return true;}
			return false;
		}

		void setComment(string comment_) { comment = comment_; }
		void setUserInfo(const UserInfo& uInfo_) { uInfo = uInfo_; }

		string virtual get_type() const { return "SUBMISSION" ; }
		uint32_t routeId, userId;
		double   optimalDistance;
		UserInfo uInfo;
		string   comment;

};

} // end namespace

#endif // #ifndef _ROUTESUBMISSION_HPP

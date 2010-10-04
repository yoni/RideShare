#ifndef _USER_PREFERENCE_HPP
#define _USER_PREFERENCE_HPP

#include "Preference.hpp"
#include <vector>
#include "boost/shared_ptr.hpp"
#include "Utils.hpp"

namespace controller
{
using namespace std;
using std::vector;
class UserPreference : public Preference
{

	public:
		typedef vector< UserPreference > UserPreferences;
		typedef boost::shared_ptr< UserPreference > ptr;

	UserPreference()
			: Preference()
			, ageMin(0), ageMax(255), genderId(0), ratingMin(0.0)
	{}

	UserPreference(size_t _ageMin, size_t _ageMax, 
								size_t _genderId, double _ratingMin)
			: Preference()
			, ageMin(_ageMin), ageMax(_ageMax)
			, genderId(_genderId), ratingMin(_ratingMin)
	{}

	UserPreference(uint32_t _userId, size_t _ageMin, size_t _ageMax, 
								size_t _genderId, double _ratingMin)
			: Preference()
			, userId(_userId)
			, ageMin(_ageMin), ageMax(_ageMax)
			, genderId(_genderId), ratingMin(_ratingMin)
	{}

	UserPreference(uint32_t _routeId, uint32_t _userId, size_t _ageMin, size_t _ageMax, 
								size_t _genderId, double _ratingMin)
			: Preference()
			, routeId(_routeId)
			, userId(_userId)
			, ageMin(_ageMin), ageMax(_ageMax)
			, genderId(_genderId), ratingMin(_ratingMin)
	{}

	uint32_t routeId;
	uint32_t userId;
	size_t  ageMin, ageMax, genderId;
	double  ratingMin;

	static UserPreference getCommonUserPreference(const UserPreferences& prefs)
	{
		UserPreference uPref;
		if(prefs.size()){
			uPref = prefs[0];
			for(size_t i = 1; i < prefs.size(); i++){
				if(uPref.ageMax > prefs[i].ageMax){
					 uPref.ageMax = prefs[i].ageMax;
				}
				if(uPref.ageMin < prefs[i].ageMin){
					 uPref.ageMin = prefs[i].ageMin;
				}
				if(uPref.ratingMin < prefs[i].ratingMin){
					uPref.ratingMin = prefs[i].ratingMin;
				}
				if(prefs[i].genderId != DONT_CARE){
					uPref.genderId = prefs[i].genderId;
				}
			}
		}
		return uPref;
	}

};

} // end controller namespace
#endif // #ifndef _USER_PREFERENCE_HPP

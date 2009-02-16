#ifndef _USERINFO_HPP
#define _USERINFO_HPP

namespace controller {

#include <string>
#include <iostream>

using std::string;
using std::ostream;
class UserInfo
{
	public:
		string  firstName;
		string  lastName;
		string  emailAddr;
		size_t  genderId;
		size_t  age;

		UserInfo(string firstName_, string lastName_, 
				string emailAddr_, size_t genderId_, size_t age_)
			: firstName( firstName_ )
			, lastName( lastName_)
			, emailAddr( emailAddr_ )
			, genderId( genderId_ )
			, age( age_ )
		{}

		UserInfo()
			: age(0)
		{}

		friend ostream& operator<<(ostream& out, const UserInfo & uInfo)
		{
			out << uInfo.firstName << " " << uInfo.lastName << " " << uInfo.emailAddr << " "
				<< uInfo.genderId << " " << uInfo.age;
			return out;
		}

		bool operator==(const UserInfo& rhs)
		{
			return (firstName == rhs.firstName
					&& lastName == rhs.lastName
					&& emailAddr == rhs.emailAddr
					&& genderId == rhs.genderId
					&& age == rhs.age);
		}
};


}

#endif // #ifndef _USERINFO_HPP

#ifndef _LOCATION_HPP
#define _LOCATION_HPP
#include <string>
#include <vector>
#include "Address.hpp"

namespace controller 
{
	using std::string;
	using std::vector;
	using routes::Address;
	/*
	 * Location is lat,lng,addr
	 */
	template <class T=double>
	class Location
	{
		public:
			T  lat, lng;
			Address addr;

			Location()
			{}

			Location(T _lat, T _lon)
				:lat(_lat)
				,lng(_lon)
			{}

			explicit Location(T _lat, T _lon, string _addr)
				:lat(_lat)
				,lng(_lon)
				,addr(_addr)
			{
				//Address newAddr(_addr);
			}
			explicit Location(string _addr, T _lat, T _lon)
				:lat(_lat)
				,lng(_lon)
				,addr(_addr)
			{
			}

			explicit Location(T _lat, T _lon, const Address & _addr)
				:lat(_lat)
				,lng(_lon)
				,addr(_addr)
			{}
			

			bool operator==(const Location<T> &rhs) const
			{
				return (rhs.lat == lat && rhs.lng == lng);
			}

			Location(const Location<T> &copyMe)
				: lat(copyMe.lat)
				, lng(copyMe.lng)
				, addr(copyMe.addr)
			{}
	};

}

#endif // #ifndef _LOCATION_HPP

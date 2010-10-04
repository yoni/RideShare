#ifndef _ADDRESS_HPP
#define _ADDRESS_HPP

namespace controller
{

namespace routes
{

using std::string;
class Address
{
	public:
		Address()
			: street("")
			, city("")
			, state("")
			, zipCode("")
			, country("")
		{}

		explicit Address(const Address& copyme)
			: street(copyme.street)
			, city(copyme.city)
			, state(copyme.state)
			, zipCode(copyme.zipCode)
			, country(copyme.country)
		{}

		explicit Address(string _street)
			: street( _street )
		{}

		Address(string _street, string _city, string _state,
				string _zipCode = "", string _country= "")
			: street( _street )
			, city( _city )
			, state( _state )
			, zipCode( _zipCode )
			, country( _country )
		{}

		string street, city, state, zipCode, country;
};

}
}

#endif // #ifndef _ADDRESS_HPP

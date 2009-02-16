#ifndef _RIDESHARE_HPP
#define _RIDESHARE_HPP

#include <string>
#include <boost/shared_ptr.hpp>
#include "Utils.hpp"
namespace controller
{

using std::string;
class Rideshare
{
	/**
	 * Rideshare
	 *   @desc: holds the fields associated with the Rideshare table
	 **/
	public:
		typedef boost::shared_ptr< Rideshare > ptr;

		Rideshare(uint32_t _rideshareId, uint32_t _driverReqId, uint32_t _riderReqId
							ConfirmType _confirm, string _created)
			: rideshareId(_rideshareId), driverReqId(_driverReqId), riderReqId(_riderReqId)
			, confirm(_confirm), created(_created)
		{}

		// Members: this needs to be updated with fields in the Rideshare Table
		uint32_t       rideshareId, driverReqId, riderReqId;
		ConfirmType    confirmType;
		string         created;
};

} // end namespace

#endif // #ifndef _RIDESHARE_HPP

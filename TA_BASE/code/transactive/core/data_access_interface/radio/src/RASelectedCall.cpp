// RASelectedCall.cpp: implementation of the RASelectedCall class.
//
//////////////////////////////////////////////////////////////////////

#include "core/data_access_interface/radio/src/RASelectedCall.h"
#include "core/data_access_interface/radio/src/RASelectedCallAccessFactory.h"
#include "core/data_access_interface/src/IDatabase.h"
#include "core/data_access_interface/src/DatabaseFactory.h"

namespace TA_Base_Core
{
	const unsigned long RASelectedCall::rowLimit = 10;

	RASelectedCall::RASelectedCall(
            const unsigned long& key,
            const std::string& tetraid,
			const std::string& callID,
			const std::string& location
            )
			:m_key(key),
			m_tetraid(tetraid),
			m_id(callID),
			m_location(location)
	   {

	   }
	

	std::string RASelectedCall::getTetraid()
	{
		return m_tetraid;
	}
	

	std::string RASelectedCall::getID()
	{
		return m_id;
	}

	
	std::string RASelectedCall::getLocation()
	{
		return m_location;
	}


    RASelectedCall::~RASelectedCall() 
	{
    }  

} // closes TA_Base_Core
 
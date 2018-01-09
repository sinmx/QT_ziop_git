#ifndef INOTIFICATIONAGENTDATA_H
#define INOTIFICATIONAGENTDATA_H
/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/data_access_interface/entity_access/src/INotificationAgentData.h $
 * @author:  Jade Welton
 * @version: $Revision: #1 $
 *
 * Last modification: $DateTime: 2015/10/09 15:42:35 $
 * Last modified by:  $Author: CM $
 * 
 * Interface to configuration data accessor for the Notification Service Agent
 *
 */

#include "core/data_access_interface/entity_access/src/IEntityData.h"

namespace TA_Base_Core
{
	class INotificationAgentData : virtual public IEntityData
	{
		
	public:

		virtual ~INotificationAgentData() {}

		virtual std::string getNotifyServicePath() = 0;

		virtual std::string getAssetName() = 0;
	};
}

#endif // INOTIFICATIONAGENTDATA_H
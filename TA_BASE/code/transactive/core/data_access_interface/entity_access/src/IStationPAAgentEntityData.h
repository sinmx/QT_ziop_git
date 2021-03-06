/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/data_access_interface/entity_access/src/IStationPAAgentEntityData.h $
  * @author HoaVu
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by: $Author: CM $
  * 
  * IStationPAAgentEntityData provides read-only access to StationPAAgent entity data.
  */

#ifndef IStationPAAgent_ENTITY_DATA_H
#define IStationPAAgent_ENTITY_DATA_H

#include <vector>
#include "core/data_access_interface/entity_access/src/IEntityData.h"
#include "core/data_access_interface/entity_access/src/IPAAgentEntityData.h"

namespace TA_Base_Core
{

    class IStationPAAgentEntityData : public virtual IPAAgentEntityData
    {
    public:

        // Nothing specialised so far...
    };

} //close namespace TA_Base_Core

#endif



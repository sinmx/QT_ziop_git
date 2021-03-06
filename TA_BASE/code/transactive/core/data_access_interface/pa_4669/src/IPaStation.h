/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/core/data_access_interface/pa_4669/src/IPaStation.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by: $Author: CM $
  * 
  * IPaStation is an interface to a PaStation object.  It allows the PA DVA Message object implementation
  * to be changed (e.g. if necessary due to a database schema change) without changing code
  * that uses it.
  */

#if !defined(IPaStation_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_)
#define IPaStation_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_

#include <string>
#include <vector>
#include "core/data_access_interface/src/IItem.h"

namespace TA_Base_Core
{
    class IPaStation : public virtual TA_Base_Core::IItem
    {

    public:

        virtual unsigned long getLocationKey() =0;

        virtual ~IPaStation() {};
        
        /**
         * invalidate
         *
         * Make the data contained by this item as invalid. The next call to get...() 
         * following a call to invalidate() will cause all the data to be reloaded from
         * the database.
         */
        virtual void invalidate() =0;
    };

    typedef std::vector<IPaStation*> IPaStations;
    typedef IPaStations::iterator    IPaStationsIt;

} //close namespace TA_Base_Core


#endif // !defined(IPaStation_34315582_B0A7_4100_BD60_2E13958D7501__INCLUDED_)

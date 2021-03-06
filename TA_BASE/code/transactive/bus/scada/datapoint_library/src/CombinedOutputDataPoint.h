/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source : $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/scada/datapoint_library/src/CombinedOutputDataPoint.h $
  * @author  HoaVu
  * @version $Revision: #1 $
  * Last modification : $DateTime: 2015/10/09 15:42:35 $
  * Last modified by : $Author: CM $
  *
  *
  *	A Safety Output Datapoint maps a single value to several target
  * datapoints.  Combined Output datapoint is controlled by setting a state.
  * The associated output datapoints are set according to a state table.
  *
  */

#ifndef COMBINED_OUTPUT_DATAPOINT_H
#define COMBINED_OUTPUT_DATAPOINT_H

#include "bus/scada/datapoint_library/src/SafetyOutputDataPoint.h"

namespace TA_Base_Bus
{

	class CombinedOutputDataPoint : public SafetyOutputDataPoint
	{
	public:


		CombinedOutputDataPoint ( TA_Base_Core::DataPointEntityDataPtr				dataPointEntityAccess,
								  TA_Base_Bus::EDataPointType		                dpType,
					   			  TA_Base_Bus::EDataPointDataType	                dpDataType,
                                  ScadaPersistencePtr                               persistence,
                                  TA_Base_Core::ScadaRootEntityData&                scadaRootEntityData,
                                  MmsScadaUtility&                                  mmsScadaUtility,
                                  CommandProcessor&                                 commandProcessor);


		virtual ~CombinedOutputDataPoint();
	};

}

#endif


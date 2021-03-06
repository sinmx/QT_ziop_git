/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/bus/scada/datapoint_library/src/IExpressionNodeNotification.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2015/10/09 15:42:35 $
  * Last modified by:  $Author: CM $
  *
  */
#ifndef IEXPRESSION_NODE_NOTIFICATION_H
#define IEXPRESSION_NODE_NOTIFICATION_H


namespace TA_Base_Bus
{

	class IExpressionNodeNotification
	{
	public:

		/**
		 * processExpressionChanges
		 *
		 * Call back when the expression node has changed.
		 *
		 */
		virtual void processExpressionChanges() = 0;
	};

}

#endif

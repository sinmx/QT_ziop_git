/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in
  * any form.
  *
  * Source:		$File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/scada/OpcBridgeLib/attributes/DnOnitp.h $
  * @author:	Chin Wenching
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2015/10/09 15:42:35 $
  * Last modified by:	$Author: CM $
  *
  * Description:
  * Class representing the ONITP attribute of a DataNode (TD13873)
  *
  */

#ifndef DNONITP_H
#define DNONITP_H

#include "app/scada/opcbridgelib/src/Attribute.h"

namespace TA_Base_App
{
    class DataNodeAttributes;

	class DnOnitp : public Attribute
	{
	public:

		//------------------------------------------------------------------------------------------
		// Operation: DnOnitp
		//	Constructor
		//------------------------------------------------------------------------------------------
		DnOnitp(DataNodeAttributes* dnAttribute, const std::string& tagName);

		//------------------------------------------------------------------------------------------
		// Operation: ~DnOnitp
		//	Destructor
		//------------------------------------------------------------------------------------------
		virtual ~DnOnitp();

	public:

		/**
		 * processProxyUpdate
		 *
		 * Process the update messages received from the proxy
		 *
		 *
		 */
		void processProxyUpdate();

		virtual EOPCATTRIBUTETYPE getAttributeType() {return E_OPC_DN_ONTIP;}

	private:
		DataNodeAttributes* m_dnAttribute;
	};
}

#endif

/**
  * The source code in this file is the property of Ripple Systems and is not for redistribution in
  * any form.
  *
  * Source:		$File: //depot/PRIV_GenericGUI_QT/TA_BASE/transactive/app/scada/OpcBridgeLib/attributes/DnAssetName.h $
  * @author:	Darren Sampson
  * @version:	$Revision: #1 $
  *
  * Last modification:	$DateTime: 2015/10/09 15:42:35 $
  * Last modified by:	$Author: CM $
  *
  * Description:
  * Class representing the Asset Name attribute of a DataNode
  *
  */

#ifndef DNASSETNAME_H
#define DNASSETNAME_H

#include "app/scada/opcbridgelib/src/Attribute.h"

namespace TA_Base_App
{
    class DataNodeAttributes;

	class DnAssetName : public Attribute
	{
	public:

		//------------------------------------------------------------------------------------------
		// Operation: DnAssetName
		//	Constructor
		//------------------------------------------------------------------------------------------
        DnAssetName(DataNodeAttributes* dnAttribute, const std::string& tagName, const std::string& defaultValue);

		//------------------------------------------------------------------------------------------
		// Operation: ~DnAssetName
		//	Destructor
		//------------------------------------------------------------------------------------------
		virtual ~DnAssetName();
		
		virtual EOPCATTRIBUTETYPE getAttributeType() {return E_OPC_DN_ASSETNAME;}

	private:
		DataNodeAttributes* m_dnAttribute;
	};
}

#endif

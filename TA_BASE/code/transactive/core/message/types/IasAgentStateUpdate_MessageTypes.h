// File: IasAgentStateUpdate_MessageTypes.h
// Created: 12/04/2006 4:13:31 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef IASAGENTSTATEUPDATE_MESSAGETYPES_H
#define IASAGENTSTATEUPDATE_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace IasAgentStateUpdate
	{
		// Root context
		static MessageContext Context("StateUpdate", "IasAgentStateUpdate", StateUpdateMessage);

		// Message Types for context IasAgentStateUpdate
		static const MessageType IasAgentDataPointUpdate(Context, "10026");
	};
};

#endif // IASAGENTSTATEUPDATE_MESSAGETYPES_H

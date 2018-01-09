// File: AuthenticationAgentStateUpdate_MessageTypes.h
// Created: 12/04/2006 4:13:30 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef AUTHENTICATIONAGENTSTATEUPDATE_MESSAGETYPES_H
#define AUTHENTICATIONAGENTSTATEUPDATE_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace AuthenticationAgentStateUpdate
	{
		// Root context
		static MessageContext Context("StateUpdate", "AuthenticationAgentStateUpdate", StateUpdateMessage);

		// Message Types for context AuthenticationAgentStateUpdate
		static const MessageType AuthenticationAgentBatchStateUpdate(Context, "10009");
		static const MessageType AuthenticationAgentSessionTimeStateUpdate(Context, "10010");
		static const MessageType AuthenticationAgentStateUpdate(Context, "10011");
		static const MessageType AuthenticationAgentStateUpdateRequest(Context, "10012");
		static const MessageType Deprecated_AuthenticationAgentDistributedUpdate(Context, "10013");
	};
};

#endif // AUTHENTICATIONAGENTSTATEUPDATE_MESSAGETYPES_H
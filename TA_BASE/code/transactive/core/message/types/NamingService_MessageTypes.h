// File: NamingService_MessageTypes.h
// Created: 12/04/2006 4:13:32 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef NAMINGSERVICE_MESSAGETYPES_H
#define NAMINGSERVICE_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace NamingService
	{
		// Root context
		static MessageContext Context("NameBind", "NamingService", BindingRequestMessage);

		// Message Types for context NamingService
		static const MessageType BindName(Context, "1");
		static const MessageType RebindName(Context, "2");
	};
};

#endif // NAMINGSERVICE_MESSAGETYPES_H

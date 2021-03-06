// File: ReportsAudit_MessageTypes.h
// Created: 12/04/2006 4:13:33 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef REPORTSAUDIT_MESSAGETYPES_H
#define REPORTSAUDIT_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace ReportsAudit
	{
		// Root context
		static MessageContext Context("Audit", "ReportsAudit", AuditMessage);

		// Message Types for context ReportsAudit
		static const MessageType Reports(Context, "30341");
	};
};

#endif // REPORTSAUDIT_MESSAGETYPES_H

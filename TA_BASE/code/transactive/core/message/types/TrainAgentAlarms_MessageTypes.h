// File: TrainAgentAlarms_MessageTypes.h
// Created: 12/04/2006 4:13:34 PM
// This file is automatically generated from 9999D02170001-TransActive_CORBA_Messages_Register.xls
// Reference: 9999-D02-17-0001, Version: 34.06, Status: Draft, Dated: 06 Apr 06
//
// * DO NOT MODIFY! *

#ifndef TRAINAGENTALARMS_MESSAGETYPES_H
#define TRAINAGENTALARMS_MESSAGETYPES_H

#include "MessageTypes.h"

namespace TA_Base_Core
{
	namespace TrainAgentAlarms
	{
		// Root context
		static MessageContext Context("Alarm", "TrainAgentAlarms", AlarmMessage);

		// Message Types for context TrainAgentAlarms
		static const MessageType ATSAgentCommsAlarm(Context, "50106");
		static const MessageType CctvTrainConflictAlarm(Context, "50107");
		static const MessageType CctvTrainPreConflictAlarm(Context, "50108");
		static const MessageType Oa1AtcTimerAlarm(Context, "50109");
		static const MessageType RadioModeTimerAlarm(Context, "50110");
		static const MessageType RccpModeConflictAlarm(Context, "50507");
		static const MessageType RccpDirectionConflictAlarm(Context, "50508");
		static const MessageType RccpTrnConflictAlarm(Context, "50509");
		static const MessageType RccpTrnChangedAlarm(Context, "50510");
		static const MessageType MpuChangeoverAlarm(Context, "50512");
	};
};

#endif // TRAINAGENTALARMS_MESSAGETYPES_H
#ifndef __COMMAND_HANDLER__
#define __COMMAND_HANDLER__
#pragma once

#include <vector>
#include <queue>
#include <string>
#include "Thread.h"
#include "NonReEntrantThreadLockable.h"
#include "..\ShareMemoryDLL\AlarmApi.h"
#include "IAlarmUpdate.h"
#include "Semaphore.h"

typedef std::vector<IAlarmUpdate*> AlarmUpdateObserver;
enum UPDATE_TYPE {NEW_ALARM = 0, UPDATE_ALARM, CLOSE_ALARM, REMOVE_ALL};
struct RequestMgs
{
	I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail;
	UPDATE_TYPE mgsType;
	bool bUpdateList;
	RequestMgs() : pAlarmDetail(0), mgsType(NEW_ALARM), bUpdateList(true){};
};
typedef std::queue<RequestMgs*> RequestQueue;

class CCommandHandler : public TA_Base_Core::Thread
{
public:
	~CCommandHandler(void);
	static CCommandHandler& getInstance();
	static void freeInstance();

	bool submitAlarm(I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail, bool bUpdateList = true);
	bool acknowledgeAlarm(I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail);
	bool closeAlarm(I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail);
	bool normalizeAlarm(I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail);
	bool updateMMSState(I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail);

	void notifyObserver(UPDATE_TYPE tUpdate, I_ATS_ISCS_ALARM::AlarmDetail* pAlarmDetail);
	
	void getProfileInfo(I_ATS_ISCS_ALARM::ProfileInfo& profileInfo);
	void setProfileInfo(I_ATS_ISCS_ALARM::ProfileInfo profileInfo);
	void registerObserver(IAlarmUpdate* pObserver);
	void unRegisterObserver(IAlarmUpdate* pObserver);
	void setUpdateTime();

	void setTargetWnd(HWND hWnd){m_hTargetWnd = hWnd; };
protected:
	void run();
	void terminate();
private:
	CCommandHandler(void);
	
private:
	static CCommandHandler* m_pInstance;
	static TA_Base_Bus::NonReEntrantThreadLockable m_singletonLock;
	
	bool m_bTerminate;
	CSemaphoreLock* m_semaphore;
	RequestQueue m_requestQue;
	TA_Base_Bus::NonReEntrantThreadLockable m_ThreadLock;
	I_ATS_ISCS_ALARM::ProfileInfo* m_pProfileInfo;
	AlarmUpdateObserver m_pUpdateObserver;

	HWND m_hTargetWnd;

};

#endif __COMMAND_HANDLER__
#include "SessionService.h"

NS_BEGIN_MH

SessionService::SessionService(BSPtr<BPTree> config)
:Service(config),
_sessionCapacity(0),
_sessionList()
{
	if (config == NULL)
	{
		MH_FATAL("SessionService can't create with null config");
		return;
	}

	_sessionCapacity = config->get<MHInt16>("sessionCapacity");
}

SessionService::~SessionService()
{
}

inline MHInt32 SessionService::getSessionCapacity()
{
	return _sessionCapacity;
}

inline MHInt32 SessionService::getAliveSessionCount()
{
	MHBSLock(_muSessionList);
	
	return _sessionList.size();
}

SessionService::ServiceStat SessionService::getServiceStat()
{
	if (getWorkerStat() != Worker::WorkerRunning)
	{
		return NotWork;
	}

	MHInt32 aliveCount = getAliveSessionCount();

	if (aliveCount == 0)
	{
		return Idel;
	}

	if (aliveCount >= _sessionCapacity)
	{
		return Full;
	}

	if (_sessionCapacity < aliveCount * 2)
	{
		return ServiceStat::Busy;
	}

	return ServiceStat::Normal;
}

bool SessionService::addSession(shared_ptr<Session> session)
{
	MHBSLock(_muSessionList);
	session->setSockCloseCallBack(std::bind1st(std::mem_fun(&SessionService::onSessionClose), this));
	session->onInit();
	_sessionList.push_back(session);
	session->beginReadData();

	return true;
}

void SessionService::onSessionClose(shared_ptr<Session> session)
{
	MHBSLock(_muSessionList);
	session->onDestory();
	_sessionList.remove(session);
}

void SessionService::onTick()
{
	//MH_TRACE2(getName(), getAliveSessionCount());
	MHBSLock(_muSessionList);
	std::list<shared_ptr<Session>>::iterator it;
	for (it = _sessionList.begin(); it != _sessionList.end(); it++)
	{
		(*it)->onTick();
	}
}


NS_END_MH

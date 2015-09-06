#include "SessionServiceManager.h"

NS_BEGIN_MH

SessionServiceManager* SessionServiceManager::p_instance = new SessionServiceManager();

SessionServiceManager* SessionServiceManager::getInstance()
{
	return p_instance;
}

SessionServiceManager::SessionServiceManager()
:_sessionServList()
{
	int i;
	for (i = 0; i < MAX_SESSION_SERV; i++)
	{
		_sessionServList.push_back(shared_ptr<SessionService>(new SessionService("SessionService", MAX_SESSION_SERV_CAPACITY)));
	}
}

SessionServiceManager::~SessionServiceManager()
{
}

void SessionServiceManager::startSessionServices(shared_ptr<boost::thread_group> threadGroup)
{
	std::vector<shared_ptr<SessionService>>::iterator it;
	for (it = _sessionServList.begin(); it != _sessionServList.end(); it++)
	{
		threadGroup->create_thread(boost::bind(&SessionService::run, (*it)));
	}
}

void SessionServiceManager::addSession(shared_ptr<ASIO_TCP_SOCKET> sock)
{
	shared_ptr<SessionService> serv = getSessionService();
	if (serv == NULL)
	{
		MH_TRACE("SessionServiceManager no more SessionService for new session");
		sock->close();
		return;
	}
	serv->addSession(shared_ptr<Session>(new Session(sock)));
}

shared_ptr<SessionService> SessionServiceManager::getSessionService()
{
	shared_ptr<SessionService> serv;
	SessionService::ServiceStat servStat = SessionService::NotWork;

	std::vector<shared_ptr<SessionService>>::iterator it;
	for (it = _sessionServList.begin(); it != _sessionServList.end(); it++)
	{
		servStat = (*it)->getServStat();
		if ((servStat == SessionService::Full) || (servStat == SessionService::NotWork))
		{
			continue;
		}

		if ((serv == NULL) || (servStat < (*it)->getServStat()))
		{
			serv = *it;
		}
	}

	return serv;
}

NS_END_MH

#include "SessionServiceManager.h"

NS_BEGIN_MH

//SessionServiceManager* SessionServiceManager::p_instance = new SessionServiceManager();

/*essionServiceManager* SessionServiceManager::getInstance()
{
	return p_instance;
}*/

SessionServiceManager::SessionServiceManager(BSPtr<BPTree> config)
:_sessionServList()
{
	if (config == NULL)
	{
		MH_FATAL("SessionServiceManager cnst with null config");
		return;
	}

	int threadCount = config->get<MHUInt32>("threadCount");
	int sessionCapacity = config->get<MHUInt32>("sessionCapacity");
	int i;
	for (i = 0; i < threadCount; i++)
	{
		_sessionServList.push_back(BSPtr<SessionService>(new SessionService(config)));
	}

	std::stringstream strStream;
	std::string strLogTmp;
	strStream << "SessionServiceManager init service thread count: " << threadCount << "session capacity: " << sessionCapacity;
	strStream >> strLogTmp;
	
	MH_INFO(strLogTmp);
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
		servStat = (*it)->getServiceStat();
		if ((servStat == SessionService::Full) || (servStat == SessionService::NotWork))
		{
			continue;
		}

		if ((serv == NULL) || (servStat < (*it)->getServiceStat()))
		{
			serv = *it;
		}
	}

	return serv;
}

NS_END_MH

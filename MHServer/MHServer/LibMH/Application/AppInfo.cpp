#include "AppInfo.h"

NS_BEGIN_MH

AppInfo* AppInfo::s_instance = new AppInfo();

AppInfo::AppInfo()
{
}

AppInfo::~AppInfo()
{
}

AppInfo* AppInfo::getInstance()
{
	return s_instance;
}

void AppInfo::createConfigMgr()
{
	_confMgr.reset(new MHConfigManager());
}

BSPtr<MHConfigManager> AppInfo::getConfigMgr()
{
	return _confMgr;
}

void AppInfo::createSessionServiceManager(BSPtr<BPTree> config, BSPtr<ISessionFactory> sessionFactory)
{
	_sessionServiceMgr.reset(new SessionServiceManager(config, sessionFactory));
}


BSPtr<SessionServiceManager> AppInfo::getSessionServiceMgr()
{
	return _sessionServiceMgr;
}

NS_END_MH
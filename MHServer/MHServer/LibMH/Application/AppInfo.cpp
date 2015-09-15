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

void AppInfo::createSessionServiceManager(BSPtr<BPTree> config)
{
	_sessionServiceMgr.reset(new SessionServiceManager(config));
}

BSPtr<SessionServiceManager> AppInfo::getSessionServiceMgr()
{
	return _sessionServiceMgr;
}

bool AppInfo::setAppInfo(const std::string& key, std::string value, bool forceUpdate)
{
	BSLock lock(_muStrInfo);

	bool ret;
	MAP_STR_STR_IT item;
	item = _appStrInfo.find(key);

	if (item != _appStrInfo.end())
	{
		if (forceUpdate)
		{
			item->second = value;
			ret = true;
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		ret = _appStrInfo.insert(MAP_STR_STR_VT(key, value)).second;
	}

	return ret;
}

std::string AppInfo::getAppInfo(const std::string& key)
{
	std::string ret = NullStr;
	MAP_STR_STR_IT item;
	item = _appStrInfo.find(key);
	if (item != _appStrInfo.end())
	{
		ret = item->second;
	}

	return ret;
}

NS_END_MH
#include "AppInfo.h"

NS_BEGIN_MH

AppInfo::AppInfo()
{
}

AppInfo::~AppInfo()
{
}

AppInfo* AppInfo::createInstance()
{
	_instance = new AppInfo();
	return _instance;
}

AppInfo* AppInfo::getInstance()
{
	return _instance;
}

NS_END_MH
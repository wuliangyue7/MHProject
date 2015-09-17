//  [9/14/2015 wuliangyu]

#ifndef __APPINFO_H__
#define __APPINFO_H__

#include "../Common/MHComInc.h"
#include "../NetWork/SessionServiceManager.h"
#include "../Config/MHConfigManager.h"
#include "Attribute.h"

NS_BEGIN_MH

class AppInfo
{
public:
	static AppInfo* getInstance();

	void createConfigMgr();
	BSPtr<MHConfigManager> getConfigMgr();

	void AppInfo::createSessionServiceManager(BSPtr<BPTree> config);
	BSPtr<SessionServiceManager> getSessionServiceMgr();

	DEF_MH_ATTRS

private:
	AppInfo();
	~AppInfo();

private:
	static AppInfo* s_instance;

	shared_ptr<SessionServiceManager> _sessionServiceMgr;
	BSPtr<MHConfigManager> _confMgr;
	std::map<std::string, int> _appInfo;
};

NS_END_MH

#endif // __APPINFO_H__
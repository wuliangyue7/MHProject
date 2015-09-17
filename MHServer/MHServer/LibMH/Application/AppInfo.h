//  [9/14/2015 wuliangyu]

#ifndef __APPINFO_H__
#define __APPINFO_H__

#include "../Common/MHComInc.h"
#include "../NetWork/SessionServiceManager.h"
#include "../Config/MHConfigManager.h"

NS_BEGIN_MH

class AppInfo
{
public:
	static AppInfo* getInstance();
	bool setAppInfo(const std::string& key, std::string value, bool forceUpdate);
	std::string getAppInfo(const std::string& key);

	void createConfigMgr();
	BSPtr<MHConfigManager> getConfigMgr();

	void AppInfo::createSessionServiceManager(BSPtr<BPTree> config);
	BSPtr<SessionServiceManager> getSessionServiceMgr();

private:
	AppInfo();
	~AppInfo();

private:
	static AppInfo* s_instance;
	BMutex _muStrInfo;
	std::map<std::string, std::string> _appStrInfo;

	shared_ptr<SessionServiceManager> _sessionServiceMgr;
	BSPtr<MHConfigManager> _confMgr;
	std::map<std::string, int> _appInfo;
};

NS_END_MH

#endif // __APPINFO_H__
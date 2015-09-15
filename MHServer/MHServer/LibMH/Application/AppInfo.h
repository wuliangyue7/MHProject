//  [9/14/2015 wuliangyu]

#ifndef __APPINFO_H__
#define __APPINFO_H__

#include "../Common/MHComInc.h"
#include "../NetWork/SessionServiceManager.h"

#define SetAppInfo(__key, __value) AppInfo::getInstance->setAppInfo(__x, __y);
#define GetAppInfo(__x) AppInfo::getInstance->getAppInfo(__x);

NS_BEGIN_MH

class AppInfo
{
public:
	static AppInfo* getInstance();
	bool setAppInfo(const std::string& key, std::string value, bool forceUpdate);
	std::string getAppInfo(const std::string& key);
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
	//std::map<std::string, int> _appInfo;
};

NS_END_MH

#endif // __APPINFO_H__
//  [9/14/2015 wuliangyu]

#ifndef __APPINFO_H__
#define __APPINFO_H__

#include "../Common/MHComInc.h"

NS_BEGIN_MH

class AppInfo
{
public:
	static AppInfo* createInstance();
	static AppInfo* getInstance();
	void setAppInfo(const std::string& key, std::string value);
	std::string getAppInfo(const std::string& key);

private:
	AppInfo();
	~AppInfo();

private:
	static AppInfo* _instance;
	std::map<std::string, std::string> _appInfo;
};

NS_END_MH

#endif // __APPINFO_H__
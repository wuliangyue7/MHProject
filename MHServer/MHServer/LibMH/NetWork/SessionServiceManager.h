/*!
 * \file SessionManager.h
 *
 * \author wuly
 * \date ÈýÔÂ 2015
 *
 * 
 */

#ifndef SessionManager_h__
#define SessionManager_h__

#include "../Common/MHMacro.h"
#include "./SessionService.h"

#include <boost/asio.hpp>

#define MAX_SESSION_SERV 1
#define MAX_SESSION_SERV_CAPACITY 2

US_NS_BOOST

NS_BEGIN_MH

class SessionServiceManager
{
public:
	SessionServiceManager(BSPtr<BPTree> config);
	~SessionServiceManager();

	void onClinetConnect(BSPtr<BSocket> socket);
	void startSessionServices(BSPtr<boost::thread_group> threadGroup);

protected:
	virtual BSPtr<SessionService> getSessionService();

private:
	SessionServiceManager();

protected:
	std::vector<BSPtr<SessionService>> _sessionServList;
};

NS_END_MH

#endif // SessionManager_h__

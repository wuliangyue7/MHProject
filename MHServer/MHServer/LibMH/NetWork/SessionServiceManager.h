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

#include "../Common/MHComInc.h"

#include "./SessionService.h"

#include <boost/asio.hpp>

#define MAX_SESSION_SERV 1
#define MAX_SESSION_SERV_CAPACITY 2

US_NS_BOOST

NS_BEGIN_MH

class SessionServiceManager
{
public:
	~SessionServiceManager()
		;
	static SessionServiceManager* getInstance();
	void addSession(shared_ptr<ASIO_TCP_SOCKET> socket);
	
	void startSessionServices(shared_ptr<boost::thread_group> threadGroup);

private:
	SessionServiceManager();
	static SessionServiceManager* p_instance;

	shared_ptr<SessionService> getSessionService();

	std::vector<shared_ptr<SessionService>> _sessionServList;
};

NS_END_MH

#endif // SessionManager_h__

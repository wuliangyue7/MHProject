/*!
 * \file SessionService.h
 *
 * \author wuly
 * \date ÈýÔÂ 2015
 *
 * 
 */

#ifndef SessionService_h__
#define SessionService_h__

#include "../Common/MHComInc.h"
#include "../Thread//Service.h"
#include "boost/asio.hpp"
#include "Session.h"

NS_BEGIN_MH

class SessionService:public Service
{
public:
	enum ServiceStat
	{
		NotWork = 0,
		Idel,
		Working,
		Busy,
		Full,
	};

	SessionService(std::string name, MHInt32 sessionCapacity);
	~SessionService();

	virtual void onTick();
	inline MHInt32 getSessionCapacity();
	inline MHInt32 getAliveSessionCount();
	ServiceStat getServStat();
	bool addSession(shared_ptr<Session> session);
	bool removeSession(shared_ptr<Session> session);

private:
	MHInt16 _sessionCapacity;
	boost::mutex _muSessionList;
	std::list<shared_ptr<Session>> _sessionList;
};

NS_END_MH

#endif // SessionService_h__

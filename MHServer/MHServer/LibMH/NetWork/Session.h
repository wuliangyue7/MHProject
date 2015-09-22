/*!
 * \file Session.h
 *
 * \author wuly
 * \date ÈýÔÂ 2015
 *
 * 
 */


#ifndef Session_h__
#define Session_h__

#include "../Utils/ByteUtils.hpp"
#include "../Common/MHComInc.h"
#include "NetMessageCodec.h"
#include "../Application/Attribute.h"
#include "./Connection.h"

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/type_traits.hpp>
#include <google/protobuf/message.h>

#define RecvDataCacheMaxLen 4*1024*8
#define SendDataCacheMaxLen 8*1024*8

NS_BEGIN_MH
US_NS_BOOST

using namespace boost::asio;

class Session :public enable_shared_from_this<Session>
{
public:
	Session();
	~Session();

	virtual void onInit();
	virtual void onDestory();

	std::string getSid();
	void onTick();
	void close();

private:
	std::string _sId;

	static BMutex MU_SId;
	static MHUInt32 SID;
	static std::string createSid();

	DEF_MH_ATTRS
};

class ISessionFactory
{
public:
	virtual BSPtr<Session> createSession() = 0;
};

template<class T>
class SessionFactory :public ISessionFactory
{
public:
	virtual BSPtr<Session> createSession()
	{
		//BOOST_MPL_ASSERT_MSG((boost::is_base_of<Session, T>::value), "type must be ISessionFactory", T);
		return BSPtr<T>(new T);
	}
};

NS_END_MH
#endif // Session_h__

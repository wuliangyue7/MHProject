//  [3/5/2015 wuliangyu]

#ifndef NetworkWorker_h__
#define NetworkWorker_h__

#include "../Common/MHComInc.h"
#include "../Thread//Service.h"
#include "../Thread/Message.h"
#include "boost/asio.hpp"
#include "./SessionServiceManager.h"

#define  ASIO_SERV boost::asio::io_service

NS_BEGIN_MH

class NetworkWorker:public Service
{
public:
	NetworkWorker(shared_ptr<ASIO_SERV> ioservice, shared_ptr<BPTree> config);
	virtual ~NetworkWorker();
	static NetworkWorker* getInstance();

	virtual void onStart();
	virtual void onRunning();
	virtual void onFinish();
	virtual void onTick();

private:
	void handleAccept(shared_ptr<boost::asio::ip::tcp::socket> socket, boost::system::error_code err);

private:
	NetworkWorker();
	//static NetworkWorker* p_NetInstance;
	void startAccept();

	MHUInt16 _port;
	shared_ptr<boost::asio::io_service> _ioservice;
	shared_ptr<boost::asio::ip::tcp::acceptor> _accptor;
	//shared_ptr<boost::asio::ip::tcp::socket> _sock;
};

NS_END_MH
#endif // NetworkWorker_h__
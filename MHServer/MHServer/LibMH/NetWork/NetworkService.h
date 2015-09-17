//  [3/5/2015 wuliangyu]

#ifndef NetworkWorker_h__
#define NetworkWorker_h__

#include "../Common/MHComInc.h"
#include "../Thread//Service.h"
#include "../Thread/Message.h"
#include <boost/asio.hpp>
#include "./SessionServiceManager.h"

NS_BEGIN_MH

class NetworkService:public Service
{
public:
	NetworkService(BSPtr<BIOServ> ioservice, BSPtr<BPTree> config, BFunc<void(BSPtr<BSocket>)> sockHandle);
	virtual ~NetworkService();
	static NetworkService* getInstance();

	virtual void onStart();
	virtual void onRunning();
	virtual void onFinish();
	virtual void onTick();

private:
	void handleAccept(BSPtr<BSocket> socket, boost::system::error_code err);

private:
	NetworkService();
	void startAccept();

	MHUInt16 _port;
	BSPtr<boost::asio::io_service> _ioservice;
	BSPtr<boost::asio::ip::tcp::acceptor> _accptor;
	BFunc<void(BSPtr<BSocket>)> _sockHandle;
};

NS_END_MH
#endif // NetworkWorker_h__
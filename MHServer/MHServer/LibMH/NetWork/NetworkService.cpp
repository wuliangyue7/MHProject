#include "NetworkService.h"

NS_BEGIN_MH

NetworkService::NetworkService(shared_ptr<BIOServ> ioservice, shared_ptr<BPTree> config, BFunc<void(shared_ptr<boost::asio::ip::tcp::socket>)> sockHandle)
:Service(config),
_ioservice(ioservice),
_accptor(NULL),
_sockHandle(sockHandle)
{
	_port = config->get<MHUInt16>("port");
	_accptor.reset(new boost::asio::ip::tcp::acceptor(*ioservice, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _port)));
	std::cout << " NetworkWorker NetworkWorker" << std::endl;
}

NetworkService::~NetworkService()
{

}

void NetworkService::onStart()
{
	Service::onStart();
	std::cout << getName()<<" onStart at _port:" << _port<< std::endl;
}

void NetworkService::startAccept()
{
	shared_ptr<boost::asio::ip::tcp::socket> _sock(new boost::asio::ip::tcp::socket(*_ioservice));
	_accptor->async_accept(*_sock, boost::bind(&NetworkService::handleAccept, this, _sock, _1));
}

void NetworkService::handleAccept(shared_ptr<boost::asio::ip::tcp::socket> socket, boost::system::error_code err)
{
	if (err)
	{
		MH_TRACE2("handleAccept err: ", err);
	}
	else
	{
		MH_TRACE2("handleAccept: ", socket->remote_endpoint().address());
		_sockHandle(socket);
	}
	
	startAccept();
}

void NetworkService::onRunning()
{
	startAccept();
	_ioservice->run();
}

void NetworkService::onFinish()
{
	Service::onFinish();
	std::cout << getName() <<" onFinish" << std::endl;

	_ioservice->stop();
	//_sock->close();
	_accptor->close();
}

void NetworkService::onTick()
{
	MH_TRACE("onTick")
}

NS_END_MH
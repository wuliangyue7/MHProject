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

#include <boost/asio.hpp>
#include <google/protobuf/message.h>

#define RecvDataCacheMaxLen 256*1024
#define SendDataCacheMaxLen 256*1024

NS_BEGIN_MH
US_NS_BOOST

using namespace boost::asio;

struct NetMessage
{
public:
	NetMessage();
	NetMessage(MHUInt16 msgId, shared_ptr<google::protobuf::Message> msg);
	MHUInt16 msgId;
	shared_ptr<google::protobuf::Message> message;
};

class Session
{
public:
	Session(shared_ptr<ASIO_TCP_SOCKET> sock);
	~Session();

	void sendNetMessage(shared_ptr<NetMessage> message);
	void onTick();
	void close();

protected:
	virtual bool processNetMessage(shared_ptr<NetMessage> netMsg);

private:
	void begintReadData();
	void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
	void sendData();
	void trySendData();
	void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);
	void processAllRecvNetMessage();
	void onSockClose();

	shared_ptr<ASIO_TCP_SOCKET> _sock;
	MHUInt8 _recvDataCache[RecvDataCacheMaxLen];
	MHInt16 _recvDataCachePos;		//start 0 end _recvDataCachePos
	std::queue<shared_ptr<NetMessage>> _recvMessageQueue;
	boost::mutex _muRecvMsg;

	MHUInt8 _sendDataCache[SendDataCacheMaxLen];
	MHInt16 _sendDataCachePos;		//start 0 end _sendDataCachePos valid data pos
	MHInt16 _totalSendDataPos;		//current send data pos
	MHInt16 _sendedDataPos;			//current sended data pos
	std::queue<shared_ptr<NetMessage>> _sendMessageQueue;
	boost::mutex _muSendMsg;
	bool _isSending;
};

NS_END_MH
#endif // Session_h__

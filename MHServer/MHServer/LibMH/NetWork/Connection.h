/*!
 * \file Connection.h
 *
 * \author wuly
 * \date ¾ÅÔÂ 2015
 *
 * 
 */


#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "../Utils/ByteUtils.hpp"
#include "../Common/MHComInc.h"
#include "./NetMessageCodec.h"
#include "../Application/Attribute.h"

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/type_traits.hpp>
#include <google/protobuf/message.h>

#define RecvDataCacheMaxLen 4*1024*8
#define SendDataCacheMaxLen 8*1024*8

NS_BEGIN_MH
US_NS_BOOST

using namespace boost::asio;

struct NetMessage
{
public:
	NetMessage();
	NetMessage(MHUInt16 msgId, BSPtr<google::protobuf::Message> msg);
	MHUInt16 msgId;
	BSPtr<google::protobuf::Message> message;
};

class Connection :public enable_shared_from_this<Connection>
{
public:
	Connection(BSPtr<BSocket> sock);
	~Connection();

	virtual void onInit();
	void beginReadData();
	virtual void onDestory();

	void sendNetMessage(shared_ptr<NetMessage> message);
	void onTick();
	void close();
	inline void setSockCloseCallBack(BFunc<void(BSPtr<Connection>)> func)
	{
		_funcOnSockClose = func;
	}

	inline void setMessageHandle(BSPtr<NetMessage> msgHandle)
	{
		_funcNetMessageHandle = msgHandle;
	}

protected:
	virtual bool processNetMessage(shared_ptr<NetMessage> netMsg);

private:
	void handleRead(const boost::system::error_code& error, size_t bytes_transferred);
	void sendData();
	void trySendData();
	void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);
	void processAllRecvNetMessage();
	void onSockClose();

private:
	shared_ptr<BSocket> _sock;
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

	BFunc<void(BSPtr<Connection>)> _funcOnSockClose;
	BFunc<void(BSPtr<NetMessage>)> _funcNetMessageHandle;
};

NS_END_MH

#endif // __CONNECTION_H__

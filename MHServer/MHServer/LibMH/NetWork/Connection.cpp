#include "Connection.h"

NS_BEGIN_MH

NetMessage::NetMessage()
:msgId((MHUInt16)0),
message()
{}

NetMessage::NetMessage(MHUInt16 msgId, shared_ptr<google::protobuf::Message> msg)
: msgId(msgId),
message(msg)
{}

Connection::Connection(BSPtr<BSocket> sock)
:_sock(sock),
_recvDataCachePos(0),
_recvMessageQueue(),
_sendDataCachePos(0),
_sendMessageQueue(),
_totalSendDataPos(0),
_sendedDataPos(0),
_isSending(false)
{
	memset(_recvDataCache, 0x00, sizeof(_recvDataCache));
}

Connection::~Connection()
{
	if (_sock->is_open())
	{
		_sock->close();
	}
}

void Connection::onInit()
{

}

void Connection::onDestory()
{

}

void Connection::onTick()
{
	if (_sock == NULL)
	{
		return;
	}

	processAllRecvNetMessage();
	sendData();
}

void Connection::sendData()
{
	if ((_sock == NULL) || (!_sock->is_open()))
	{
		return;
	}

	boost::mutex::scoped_lock lock(_muSendMsg);
	if (_isSending)
	{
		return;
	}
	if (_sendDataCachePos > 0)
	{
		_isSending = true;
		_sendedDataPos = 0;
		_totalSendDataPos = _sendDataCachePos;

		//MH_TRACE2("async_write_some _totalSendDataPos:", _totalSendDataPos);
		_sock->async_write_some(
			boost::asio::buffer(_sendDataCache, _totalSendDataPos),
			boost::bind(&Connection::handleWrite, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
}

void Connection::handleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		close();
		return;
	}

	boost::mutex::scoped_lock lock(_muSendMsg);
	//MH_TRACE2("handleWrite bytes_transferred:", bytes_transferred);
	//MH_TRACE2("handleWrite _sendedDataPos:", _sendedDataPos);
	_sendedDataPos += bytes_transferred;
	assert(_sendedDataPos <= _totalSendDataPos);

	if (_sendedDataPos < _totalSendDataPos)
	{
		return;
	}

	memcpy(_sendDataCache, _sendDataCache + _totalSendDataPos, SendDataCacheMaxLen - _totalSendDataPos);
	_sendDataCachePos -= _totalSendDataPos;
	_totalSendDataPos = _sendedDataPos = 0;
	_isSending = false;
	//sendData();
}

void Connection::close()
{
	if (!_sock->is_open())
	{
		MH_TRACE("client disconected!");
		_sock->close();
		return;
	}
}

void Connection::beginReadData()
{
	_sock->async_read_some(buffer(_recvDataCache + _recvDataCachePos, RecvDataCacheMaxLen - _recvDataCachePos), boost::bind(&Connection::handleRead, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void Connection::handleRead(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		MH_TRACE2("error find for handleRead error:", error);
		close();
		return;
	}

	MH_TRACE2("handleRead bytes_transferred:", bytes_transferred);

	boost::mutex::scoped_lock lock(_muRecvMsg);
	_recvDataCachePos += bytes_transferred;
	if (_recvDataCachePos > RecvDataCacheMaxLen)
	{
		MH_TRACE("recv data out of cache!");
		close();
		return;
	}


	shared_ptr<NetMessage> message;
	MHInt16 readSize;

	while (1)
	{
		message = NetMessageCodec::decodeMessage(_recvDataCache, _recvDataCachePos, readSize);
		if (message != NULL)
		{
			_recvMessageQueue.push(message);
			memcpy(_recvDataCache, _recvDataCache + readSize, RecvDataCacheMaxLen - readSize);
			_recvDataCachePos -= readSize;
			memset(_recvDataCache + _recvDataCachePos, 0x00, RecvDataCacheMaxLen - _recvDataCachePos);
		}
		else
		{
			if (readSize == -1)
			{
				close();
			}
			break;
		}
	}

	beginReadData();
}

void Connection::sendNetMessage(shared_ptr<NetMessage> message)
{
	MHInt16 dataSize = 0;
	boost::mutex::scoped_lock lock(_muSendMsg);
	if (NetMessageCodec::encodeMessage(_sendDataCache + _sendDataCachePos, message, SendDataCacheMaxLen - _sendDataCachePos, dataSize))
	{
		_sendDataCachePos += dataSize;
		MH_TRACE2("encodeMessage size: ", dataSize);
		MH_TRACE2("encodeMessage _sendDataCachePos: ", _sendDataCachePos);
	}
}

void Connection::processAllRecvNetMessage()
{
	boost::mutex::scoped_lock lock(_muRecvMsg);
	while (!_recvMessageQueue.empty())
	{
		processNetMessage(_recvMessageQueue.front());
		_recvMessageQueue.pop();
	}
}

bool Connection::processNetMessage(shared_ptr<NetMessage> netMsg)
{
	MH_TRACE2("Connection processNetMessage:", netMsg->msgId);
	netMsg->message->PrintDebugString();

	if (_funcNetMessageHandle.empty())
	{
		MH_WARING("connection net message handle not set");
		return false;
	}

	_funcNetMessageHandle(netMsg);
	return true;
}

void Connection::onSockClose()
{
	if (!_funcOnSockClose.empty())
	{
		_funcOnSockClose(shared_from_this());
	}
}

NS_END_MH
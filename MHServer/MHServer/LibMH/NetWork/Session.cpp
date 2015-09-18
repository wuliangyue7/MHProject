#include "Session.h"

NS_BEGIN_MH

NetMessage::NetMessage()
:msgId((MHUInt16)0),
message()
{}

NetMessage::NetMessage(MHUInt16 msgId, shared_ptr<google::protobuf::Message> msg)
: msgId(msgId),
message(msg)
{}

BMutex Session::MU_SId;
MHUInt32 Session::SID = 0;
std::string Session::createSid()
{
	MHBSLock(MU_SId);
	return "sid"+(++SID);
}

Session::Session(shared_ptr<BSocket> sock)
:_sock(sock),
_sId(createSid()),
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

Session::~Session()
{
	if (_sock->is_open())
	{
		_sock->close();
	}
}

std::string Session::getSid()
{
	return _sId;
}

void Session::onInit()
{

}

void Session::onDestory()
{

}

void Session::onTick()
{
	if (_sock == NULL)
	{
		return;
	}

	processAllRecvNetMessage();
	sendData();
}

void Session::sendData()
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
			boost::bind(&Session::handleWrite, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}
}

void Session::handleWrite(const boost::system::error_code& error, size_t bytes_transferred)
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

void Session::close()
{
	if (!_sock->is_open())
	{
		MH_TRACE("client disconected!");
		//_sock.reset();
		_sock->close();
		return;
	}
}

void Session::beginReadData()
{
	_sock->async_read_some(buffer(_recvDataCache + _recvDataCachePos, RecvDataCacheMaxLen - _recvDataCachePos), boost::bind(&Session::handleRead, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));;
}

void Session::handleRead(const boost::system::error_code& error, size_t bytes_transferred)
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

	
	shared_ptr<NetMessage> message(NULL);
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

void Session::sendNetMessage(shared_ptr<NetMessage> message)
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

void Session::processAllRecvNetMessage()
{
	boost::mutex::scoped_lock lock(_muRecvMsg);
	while (!_recvMessageQueue.empty())
	{
		processNetMessage(_recvMessageQueue.front());
		_recvMessageQueue.pop();
	}
}

bool Session::processNetMessage(shared_ptr<NetMessage> netMsg)
{
	MH_TRACE2("Session processNetMessage:", netMsg->msgId);
	netMsg->message->PrintDebugString();

	return true;
}

void Session::onSockClose()
{
	if (!_funcOnSockClose.empty())
	{
		_funcOnSockClose(shared_from_this());
	}
}

void Session::setSockCloseCallBack(BFunc<void(BSPtr<Session>)> func)
{
	_funcOnSockClose = func;
}

NS_END_MH
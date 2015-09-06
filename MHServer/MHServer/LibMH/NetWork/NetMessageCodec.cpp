#include "NetMessageCodec.h"

NS_BEGIN_MH

//outReadLen return -1 with unkonw msgId (len(uint id + content) + id(ushort) + content)
shared_ptr<NetMessage> NetMessageCodec::decodeMessage(MHUInt8* buff, MHUInt16 maxLen, MHInt16& outReadLen)
{
	MHInt32 msgLen = BytesUtils::readUInt32(buff);
	if (maxLen < msgLen + 4)
	{
		outReadLen = 0;
		return shared_ptr<NetMessage>(NULL);
	}

	MHUInt16 msgId = BytesUtils::readUShort(buff + 4);
	shared_ptr<google::protobuf::Message> content = NetMessageFactory::createNetMessage(msgId);
	if (content == NULL)
	{
		outReadLen = -1;
		MH_TRACE2("MessageFactory::decodeMessage unkonw netMsgId:", msgId);
		return shared_ptr<NetMessage>(NULL);
	}

	MH_TRACE2("MessageFactory::decodeMessage netMsgId:", msgId);
	outReadLen = msgLen + 4;
	shared_ptr<NetMessage> netMessage(new NetMessage(msgId, content));
	netMessage->message->ParseFromArray(buff + 6, msgLen-2);
	return netMessage;
}

bool NetMessageCodec::encodeMessage(MHUInt8* buff, shared_ptr<NetMessage> netMmesaage, MHUInt32 maxLen, MHInt16& outDataSize)
{
	if (!netMmesaage->message->IsInitialized())
	{
		MH_TRACE2("NetMessage Initialized error",netMmesaage->message->InitializationErrorString());
		return false;
	}

	MHUInt16 msgContentLen = netMmesaage->message->ByteSize();
	if (maxLen < msgContentLen + 6)
	{
		MH_TRACE("send buff overflow");
		return false;
	}

	BytesUtils::writeUint32(buff, msgContentLen + 2);
	BytesUtils::writeUShort(buff + 4, netMmesaage->msgId);
	netMmesaage->message->SerializeToArray(buff + 6, msgContentLen);
	outDataSize = msgContentLen + 6;
	return true;
}

NS_END_MH
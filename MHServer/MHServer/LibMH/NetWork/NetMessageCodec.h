//  [3/18/2015 wuliangyu]

#ifndef NetMessageCodec_h__
#define NetMessageCodec_h__

#include "../Common/MHComInc.h"
#include "NetMessageFactory.h"

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/descriptor.h>
#include "../network/Session.h"

NS_BEGIN_MH
US_NS_BOOST

#define MessageMap std::map<NetMsgId, google::protobuf::Message*>
struct NetMessage;

class NetMessageCodec
{
public:
	static shared_ptr<NetMessage> decodeMessage(MHUInt8* buff, MHUInt16 maxLen, MHInt16& outReadLen);
	static bool encodeMessage(MHUInt8* buff, shared_ptr<NetMessage> mesaage, MHUInt32 maxLen, MHInt16& outDataSize);
};

NS_END_MH
#endif // MessageFactory_h__
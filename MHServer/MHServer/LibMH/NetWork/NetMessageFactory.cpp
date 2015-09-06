#include "NetMessageFactory.h"

shared_ptr<google::protobuf::Message> NetMessageFactory::createNetMessage(MHUInt16 messageId)
{
	shared_ptr<google::protobuf::Message> netMessage(NULL);
	/*switch (messageId)
	{
		case CS_PbTest:
			netMessage = shared_ptr<PbTest>(new PbTest()); 
			break;
		case CS_UseItem:
			netMessage = shared_ptr<UseItem>(new UseItem()); 
			break;
		default:
			break;
	};*/

	return netMessage;
}

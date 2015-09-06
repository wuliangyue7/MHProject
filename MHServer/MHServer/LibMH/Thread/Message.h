//  [3/11/2015 wuliangyu]

#ifndef Message_h__
#define Message_h__

#include "../Common/MHComInc.h"

NS_BEGIN_MH
US_NS_BOOST

enum MessageId
{
	WorkerExit = 10000
};

struct Message
{
	MessageId mId;
	shared_ptr<any> mContent;
};

NS_END_MH
#endif // Message_h__
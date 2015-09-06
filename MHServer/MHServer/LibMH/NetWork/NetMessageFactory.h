/*!
 * \file NetMessageFactory.h
 *
 * \author wuly
 * \date ËÄÔÂ 2015
 *
 * 
 */


#ifndef __NETMESSAGEFACTORY_H__
#define __NETMESSAGEFACTORY_H__

#include "../Common/MHComInc.h"
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/message.h>

US_NS_BOOST

class NetMessageFactory
{
public:
	static shared_ptr<google::protobuf::Message> createNetMessage(MHUInt16 messageId);
};

#endif // __NetMessageFactory_H__

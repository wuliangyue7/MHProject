#include <LibMH.h>
#include <NetWork/NetworkService.h>
#include <boost/log/common.hpp>
#include "ConfigTest.h"
#include "NetWorkTest.h"

US_NS_MH
US_NS_STD
US_NS_BOOST

int main(int argc, char** argv)
{
	APP_INS->setAttr("test", any(string("ccxasdsd")));
	MH_TRACE(APP_INS->getAttr<string>("test", "str"));

	APP_INS->setAttr("123", any(string("val_of_123")));
	MH_TRACE(APP_INS->getAttr<string>("123", "abc"));

	APP_INS->setAttr("123", 789);
	MH_TRACE(APP_INS->getAttr<int>("123", 0));
	//MHConfigTest();
	//MHTestNetWork();
	/*
	boost::thread threadNetwork(boost::bind(&NetworkWorker::run, NetworkWorker::getInstance()));
	boost::shared_ptr<boost::thread_group> threadGroup(new boost::thread_group());
	SgInsSessionServMgr->startSessionServices(threadGroup);
	//boost::this_thread::sleep(boost::posix_time::millisec(500));

	//shared_ptr<Message> pMsg(new Message());
	//pMsg->mId = MessageId::WorkerExit;
	//NetworkWorker::getInstance()->postMessage(pMsg);

	threadNetwork.join();
	threadGroup->join_all();
	//assert(pStr == NULL);
	*/
	
	::system("pause");
	return 0;
}
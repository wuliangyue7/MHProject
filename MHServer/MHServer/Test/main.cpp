#include <LibMH.h>
#include <NetWork/NetworkWorker.h>

US_NS_MH
US_NS_STD
US_NS_BOOST

int main(int argc, char** argv)
{
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

	::system("pause");
	return 0;
	return 0;
}
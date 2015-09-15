#include <LibMH.h>
#include <NetWork/NetworkWorker.h>
#include <Config/MHConfigManager.h>

US_NS_MH

void MHTestNetWork()
{
	BSPtr<MHConfigManager> confMgr(new MHConfigManager());
	confMgr->addConfigWithFile("./config/services.json");

	BSPtr<NetworkWorker> netWork(new NetworkWorker(BSPtr<ASIO_SERV>(new ASIO_SERV()), confMgr->getConfig("services")));

	boost::thread threadNetwork(boost::bind(&NetworkWorker::run, netWork));
	BSPtr<boost::thread_group> threadGroup(new boost::thread_group());
	SgInsSessionServMgr->startSessionServices(threadGroup);
	threadGroup->join_all();
}
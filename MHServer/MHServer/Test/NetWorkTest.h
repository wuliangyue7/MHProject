#include <LibMH.h>
#include <NetWork/NetworkService.h>
#include <Config/MHConfigManager.h>

US_NS_MH

void MHTestNetWork()
{
	//BSPtr<MHConfigManager> confMgr(new MHConfigManager());
	//confMgr->addConfigWithFile("./config/services.json");

	//BSPtr<NetworkService> netWork(new NetworkService(BSPtr<BIOServ>(new BIOServ()), confMgr->getConfig("services")));

	//boost::thread threadNetwork(boost::bind(&NetworkService::run, netWork));
	//BSPtr<boost::thread_group> threadGroup(new boost::thread_group());
	////SgInsSessionServMgr->startSessionServices(threadGroup);
	//threadGroup->join_all();
}
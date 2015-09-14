//  [9/7/2015 wuliangyu]

#ifndef __CONFIGTEST_H__
#define __CONFIGTEST_H__

#include <LibMH.h>
#include <Config/MHConfigManager.h>

US_NS_BOOST
US_NS_MH

bool MHConfigTest()
{
	boost::shared_ptr<MHConfigManager> confMgr(new MHConfigManager());

	confMgr->addConfigWithFile("servers.json");

	boost::shared_ptr<BPTree> pConf = confMgr->getConfig("servers");

	if (pConf == NULL)
	{
		MH_TRACE("get conf failed!");
		return false;
	}
	
	BPTree pt2 = pConf->get_child("development");
	BPTree pt3 = pt2.get_child("connector");
	BPTree pt4;
	//BPTree::iterator it = pt3.begin();

	for (BPTree::iterator it = pt3.begin(); it != pt3.end(); ++it)
	{
		pt4 = it->second;
		try
		{
			MH_TRACE2("id :", pt4.get<std::string>("id1"));
		}
		catch (std::exception e)
		{
			MH_TRACE(e.what());
		}
	}

	return true;
}

#endif // __CONFIGTEST_H__
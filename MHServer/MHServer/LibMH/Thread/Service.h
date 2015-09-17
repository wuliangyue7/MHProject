//  [3/11/2015 wuliangyu]

#ifndef Service_h__
#define Service_h__

#include "../Common/MHMacro.h"
#include "Message.h"
#include "Worker.h"
#include "../Log/MHLog.h"

#include <boost/property_tree/ptree.hpp>

NS_BEGIN_MH

class Service:public Worker
{
public:
	Service(BSPtr<BPTree> config);

	virtual void onStart();
	virtual void onPreRunning();
	virtual void onRunning();
	virtual void onPreFinish();
	virtual void onFinish();

	inline std::string getName() const
	{
		return _name;
	}

	inline boost::uint16_t getTickTime() const
	{
		return _tickTime;
	}

	bool postMessage(shared_ptr<Message> message);
	void processAllMessage();
	virtual bool onMessage(shared_ptr<Message> message);

protected:
	virtual void onTick() = 0;

private:
	//no default cnst
	Service();


	std::queue<shared_ptr<Message>> _messageQueue;
	boost::mutex _muMsg;

protected:
	std::string _name;

private:
	bool _running;
	MHUInt32 _tickTime;
	MHUInt64 _tickCostTime;
};

NS_END_MH
#endif // Service_h__
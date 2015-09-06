//  [3/11/2015 wuliangyu]

#ifndef Service_h__
#define Service_h__

#include "../Common/MHComInc.h"
#include "Message.h"
#include "Worker.h"

NS_BEGIN_MH

class Service:public Worker
{
public:
	Service(std::string name, boost::uint16_t tickTime);

	virtual void onStart();
	virtual void onRunning();
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
	
	std::queue<shared_ptr<Message>> _messageQueue;
	boost::mutex _muMsg;

private:
	std::string _name;
	bool _running;
	boost::uint16_t _tickTime;
	boost::uint64_t _tickCostTime;
};

NS_END_MH
#endif // Service_h__
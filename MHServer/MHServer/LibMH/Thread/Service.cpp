#include "Service.h"

NS_BEGIN_MH

Service::Service(BSPtr<BPTree> config)
:_name(NULL),
_tickTime(0),
_tickCostTime(0)
{
	if (config == NULL)
	{
		MH_FATAL("can't start services with null config");
		return;
	}

	_name = config->get<std::string>("name");
	_tickTime = config->get<MHUInt32>("tickTime");
}

Service::Service()
{

}

void Service::onStart()
{
}

void Service::onPreRunning()
{

}

void Service::onRunning()
{
	if (_tickTime <= 0)
	{
		return;
	}

	_running = true;
	boost::posix_time::ptime tickStart, tickEnd;
	boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;

	while (1)
	{
		tickStart = boost::posix_time::microsec_clock::universal_time();
		processAllMessage();
		
		if (!_running)
		{
			break;
		}

		onTick();
		tickEnd = boost::posix_time::microsec_clock::universal_time();

		time_elapse = tickEnd - tickStart;
		_tickCostTime = time_elapse.total_milliseconds();
		
		//MH_TRACE2(getName()+"ticktime", _tickCostTime);
		if (_tickCostTime < _tickTime)
		{
			boost::this_thread::sleep(boost::posix_time::millisec(_tickTime - _tickCostTime));
		}
	}
}

void Service::onPreFinish()
{
}

void Service::onFinish()
{
	MH_TRACE(getName() + " finish");
}

bool Service::postMessage(shared_ptr<Message> message)
{
	boost::mutex::scoped_lock lock(_muMsg);
	if (getWorkerStat() != Worker::WorkerRunning)
	{
		return false;
	}

	_messageQueue.push(message);
	return true;
}

void Service::processAllMessage()
{
	boost::mutex::scoped_lock lock(_muMsg);
	while (!_messageQueue.empty())
	{
		onMessage(_messageQueue.front());
		_messageQueue.pop();
	}
}

bool Service::onMessage(shared_ptr<Message> message)
{
	bool ret = false;
	switch (message->mId)
	{
	case MessageId::WorkerExit:
		_running = false;
		ret = true;
		break;
	default:
		break;
	}

	return ret;
}

NS_END_MH
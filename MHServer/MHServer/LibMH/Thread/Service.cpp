#include "Service.h"

NS_BEGIN_MH

Service::Service(std::string name, boost::uint16_t tickTime)
:_name(name),
_tickTime(tickTime),
_tickCostTime(0)
{
}

void Service::onStart()
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
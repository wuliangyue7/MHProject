//  [3/5/2015 wuliangyu]

#ifndef Worker_h__
#define Worker_h__

#include "../Common/MHComInc.h"
#include "boost/thread.hpp"
#include "Runable.hpp"

NS_BEGIN_MH

class Worker: public Runable
{
public:
	enum WorkerStat
	{
		WorkIdle,
		WorkerStarting,
		WorkerRunning,
		WorkerCancelling,
		WorkerFinished,
	};

	Worker();
	virtual ~Worker();

	virtual void run();

	virtual void onStart() = 0;
	virtual void onRunning() = 0;
	virtual void onFinish() = 0;

	inline WorkerStat getWorkerStat()
	{
		return _workerStat;
	}

private:
	boost::thread* _pThread;
	WorkerStat _workerStat;
};

NS_END_MH
#endif // Worker_h__
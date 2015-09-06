#include "Worker.h"
#include "../Common/MHComInc.h"

NS_BEGIN_MH

Worker::Worker()
 :_pThread(NULL),
 _workerStat(WorkIdle)
{
} 

Worker::~Worker()
{

}

void Worker::run()
{
	_workerStat = WorkerStarting;
	onStart();
	_workerStat = WorkerRunning;
	onRunning();
	_workerStat = WorkerCancelling;
	onFinish();
	_workerStat = WorkerFinished;
}

NS_END_MH

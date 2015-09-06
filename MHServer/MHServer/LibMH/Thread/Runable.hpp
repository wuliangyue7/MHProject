//  [3/5/2015 wuliangyu]

#ifndef Runable_h__
#define Runable_h__

#include "../Common/MHComInc.h"

NS_BEGIN_MH

class Runable
{
public:
	Runable(){}
	virtual ~Runable(){}

	virtual void run() = 0;
};

NS_END_MH

#endif // Runable_h__
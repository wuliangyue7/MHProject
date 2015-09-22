#include "Session.h"

NS_BEGIN_MH

Session::Session(shared_ptr<BSocket> sock)
:_sId(createSid())
{
}

Session::~Session()
{
}

std::string Session::getSid()
{
	return _sId;
}

void Session::onInit()
{

}

void Session::onDestory()
{

}

void Session::onTick()
{
}

NS_END_MH
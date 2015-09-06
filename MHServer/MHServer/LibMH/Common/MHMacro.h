//  [9/6/2015 wuliangyu]

#ifndef __MHMACRO_H__
#define __MHMACRO_H__

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include  <list>
#include <map>

#define NS_BEGIN_MH	namespace mh{
#define NS_END_MH	}
#define US_NS_MH	using namespace mh;
#define US_NS_STD	using namespace std;
#define US_NS_BOOST	using namespace boost;

#define ReturnVoidIfNull(__x) if((__x) == NULL) { return; }
#define ReturnFalseIfNull(__x) if((__x) == NULL) { return false; }

#define ASIO_TCP_SOCKET boost::asio::ip::tcp::socket

#define MHUInt8 boost::uint8_t
#define MHUInt16 boost::uint16_t
#define MHInt16 boost::int16_t
#define MHInt32 boost::int32_t
#define MHUInt32 boost::uint32_t

#define SgScopedLock(__x) boost::mutex::scoped_lock lock((__x))

#define MH_TRACE(__x) std::cout<<(__x)<<std::endl;
#define MH_TRACE2(__x, __y) std::cout<<(__x)<<(__y)<<std::endl;
#define MH_TRACE3(__x, __y, __z) std::cout<<(__x)<<(__y)<<__z<<std::endl;
#define MH_TRACE5(__x, __y, __z, __w, __v) std::cout<<(__x)<<(__y)<<__z<<__w<<__v<<std::endl;
#define SgInsSessionServMgr SessionServiceManager::getInstance()

#endif // __MHMACRO_h__
//  [9/6/2015 wuliangyu]

#ifndef __MHMACRO_H__
#define __MHMACRO_H__

#define NS_BEGIN_MH	namespace mh{
#define NS_END_MH	}
#define US_NS_MH	using namespace mh;
#define US_NS_STD	using namespace std;
#define US_NS_BOOST	using namespace boost;

#define APP_INS AppInfo::getInstance()
#define SetAppInfo(__key, __value) AppInfo::getInstance->setAppInfo(__x, __y);
#define GetAppInfo(__x) AppInfo::getInstance->getAppInfo(__x);

#define ReturnVoidIfNull(__x) if((__x) == NULL) { return; }
#define ReturnFalseIfNull(__x) if((__x) == NULL) { return false; }

#define NullStr NULL

#define MHUInt8 boost::uint8_t
#define MHUInt16 boost::uint16_t
#define MHInt16 boost::int16_t
#define MHInt32 boost::int32_t
#define MHUInt32 boost::uint32_t
#define MHUInt64 boost::uint64_t

#define BPTree boost::property_tree::ptree
#define BSPtr boost::shared_ptr
#define BSLock boost::mutex::scoped_lock
#define BMutex boost::mutex

#define	BIOServ boost::asio::io_service
#define	BSocket boost::asio::ip::tcp::socket

#define BFunc boost::function
#define BFuncVoid boost::function<void(void)>
#define BIntFuncVoid boost::function<int(void)>
#define BFuncInt boost::function<void(int)>
#define BIntFuncInt boost::function<int(int)>

#define MHBSLock(__x) boost::mutex::scoped_lock lock((__x))

#define MH_TRACE(__x) std::cout<<(__x)<<std::endl;
#define MH_TRACE2(__x, __y) std::cout<<(__x)<<(__y)<<std::endl;
#define MH_TRACE3(__x, __y, __z) std::cout<<(__x)<<(__y)<<__z<<std::endl;
#define MH_TRACE5(__x, __y, __z, __w, __v) std::cout<<(__x)<<(__y)<<__z<<__w<<__v<<std::endl;

#define MH_DEBUG(msg) MH_TRACE(msg)
#define MH_INFO(msg) MH_TRACE(msg)
#define MH_WARING(msg) MH_TRACE(msg)
#define MH_ERROR(msg) MH_TRACE(msg)
#define MH_FATAL(msg) MH_TRACE(msg)

#define MH_MAKESTR(__x, __str) \
{	\
	std::stringstream __strStream;	\
	__strStream __x;	\
	__strStream >> __str;	\
}

#define MAP_STR_STR_IT std::map<std::string, std::string>::iterator
#define MAP_STR_STR_VT std::map<std::string, std::string>::value_type

#define MAP_STR_INT_IT std::map<std::string, int>::iterator
#define MAP_STR_INT_VT std::map<std::string, int>::value_type

#define MAP_INT_STR_IT std::map<int, std::string>::iterator
#define MAP_INT_STR_VT std::map<int, std::string>::value_type

#define MAP_STR_ANY_IT std::map<std::string, boost::any>::iterator
#define MAP_STR_ANY_VT std::map<std::string, boost::any>::value_type

#define DEF_MH_ATTRS public: \
	inline bool setAttr(const std::string& key, any value, bool forceUpdate = true) \
	{\
		return _attrs.setAttr(key, value);\
	}\
	\
	template<typename T> T getAttr(const std::string& key, const T& defaultValue, bool withLock = false)	\
	{	\
		return _attrs.getAttr<T>(key, defaultValue, withLock);	\
	}	\
	\
private:	\
	Attrbute _attrs;

#define SET_ATTR_STRING(__attr, __key, __val) __attr.setAttr(__key, any(string(__val)))
#define GET_ATTR_STRING(__attr, __key, __defaultVal) __attr.getAttr<std::string>(__key, __defaultVal)

#define SET_ATTR_INT(__attr, __key, __val) __attr.setAttr(__key, __val)
#define GET_ATTR_INT(__attr, __key, __defaultVal) __attr.getAttr<int>(__key, __defaultVal)

#endif // __MHMACRO_h__
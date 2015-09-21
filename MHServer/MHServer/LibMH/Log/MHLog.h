//  [9/7/2015 wuliangyu]

#ifndef __MHLOG_H__
#define __MHLOG_H__

#include "../Common/MHComInc.h"

#include <boost/log/core.hpp>
#include <boost/log/common.hpp>  
#include <boost/log/expressions.hpp>  
#include <boost/log/attributes.hpp>  
#include <boost/log/sinks.hpp>  
#include <boost/log/sources/logger.hpp>  
#include <boost/log/sources/severity_logger.hpp>  
#include <boost/log/sources/record_ostream.hpp>  
#include <boost/log/utility/record_ordering.hpp> 
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

NS_BEGIN_MH

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

class MHLog
{
public: 
	void init();
	void log(std::string info);


private:
	boost::shared_ptr< logging::core > _logCore;
	src::logger _logSrc;
};


NS_END_MH

#endif // __MHLOG_H__
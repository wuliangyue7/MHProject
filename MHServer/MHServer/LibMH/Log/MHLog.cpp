#include "MHLog.h"

NS_BEGIN_MH

void MHLog::init()
{
	_logCore = logging::core::get();

	typedef sinks::synchronous_sink<sinks::text_ostream_backend> TextSink;

	BSPtr<TextSink> sink = boost::make_shared<TextSink>();
	sink->locked_backend()->add_stream(boost::make_shared<std::ofstream>("log/sign.log"));
	sink->set_formatter(
		expr::format("[%1%]<%2%>(%3%):%4%")
		% expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%M-%d %H:%M:%S") 
		% logging::trivial::severity
		% expr::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID")
		% expr::smessage
		);

	BSPtr<std::ostream> consoleStream(&std::clog, boost::null_deleter());
	sink->locked_backend()->add_stream(consoleStream);

	_logCore->add_sink(sink);

	logging::add_common_attributes();
	BOOST_LOG_SCOPED_THREAD_TAG("ThreadID", boost::this_thread::get_id());
	
}

void MHLog::log(std::string info)
{
	BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
	BOOST_LOG_TRIVIAL(info) << "An informational severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error) << "An error severity message";
	BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
}

NS_END_MH
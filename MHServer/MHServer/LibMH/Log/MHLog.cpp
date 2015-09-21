#include "MHLog.h"

NS_BEGIN_MH

void MHLog::init()
{
	_logCore = logging::core::get();
	logging::register_simple_formatter_factory< boost::log::trivial::severity_level, char >("Severity");
	logging::add_file_log(
		keywords::file_name = "log/sign_%Y-%m-%d_%H-%M-%S.%N.log",
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = "[%TimeStamp%] (%Severity%) : %Message%",
		keywords::min_free_space = 3 * 1024 * 1024
		);
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::debug);
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
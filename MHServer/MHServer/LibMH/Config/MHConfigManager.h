//  [9/7/2015 wuliangyu]

#ifndef __MHCONFIG_H__
#define __MHCONFIG_H__

#include "../Common/MHMacro.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>

#include <map>
#include <boost/shared_ptr.hpp>

US_NS_BOOST

NS_BEGIN_MH

namespace NS_BPTree = boost::property_tree;

class MHConfigManager
{
public:
	MHConfigManager();
	bool addConfig(const std::string& name, shared_ptr<NS_BPTree::ptree> data);
	shared_ptr<NS_BPTree::ptree> getConfig(const std::string& name);
	bool addConfigWithString(const std::string name, const std::string& data);
	bool addConfigWithFile(const std::string& file);

private:
	std::map<std::string, shared_ptr<NS_BPTree::ptree>> _mapConfig;
};

NS_END_MH

#endif // __MHCONFIG_H__
#include "MHConfigManager.h"

NS_BEGIN_MH

MHConfigManager::MHConfigManager()
:_mapConfig()
{
}

bool MHConfigManager::addConfig(const std::string& name, shared_ptr<NS_BPTree::ptree> data)
{
	std::pair<std::map<std::string, shared_ptr<NS_BPTree::ptree>>::iterator, bool>  it = _mapConfig.insert(std::map<std::string, shared_ptr<NS_BPTree::ptree>>::value_type(name, data));
	if (!it.second)
	{
		MH_TRACE2("addConfig failed!", name);
	}

	return it.second;
}

bool MHConfigManager::addConfigWithString(const std::string name, const std::string& data)
{
	std::stringstream strStream;
	shared_ptr<NS_BPTree::ptree> pt(new BPTree());

	strStream << data;
	try
	{
		NS_BPTree::json_parser::read_json<NS_BPTree::ptree>(strStream, *pt);
	}
	catch (NS_BPTree::ptree_error & e)
	{
		MH_TRACE3("addConfigWithString error", name, e.what());
		return false;
	}

	return addConfig(name, pt);
}

bool MHConfigManager::addConfigWithFile(const std::string& file)
{
	shared_ptr<NS_BPTree::ptree> pt(new BPTree());
	boost::filesystem::path p(file);

	try
	{
		NS_BPTree::json_parser::read_json<NS_BPTree::ptree>(file, *pt);
	}
	catch (NS_BPTree::ptree_error & e)
	{
		MH_TRACE3("addConfigWithFile error!", file, e.what());
		return false;
	}

	return addConfig(boost::filesystem::path(file).stem().string(), pt);
}

shared_ptr<NS_BPTree::ptree> MHConfigManager::getConfig(const std::string& name)
{
	std::map<std::string, shared_ptr<NS_BPTree::ptree>>::iterator it = _mapConfig.find(name);
	if (it == _mapConfig.end())
	{
		MH_TRACE2("getConfig failed!", name);
		return shared_ptr<NS_BPTree::ptree>(NULL);
	}

	return it->second;
}

NS_END_MH
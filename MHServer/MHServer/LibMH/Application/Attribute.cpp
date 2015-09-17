#include "Attribute.h"

US_NS_BOOST;
NS_BEGIN_MH

bool Attrbute::setAttr(const std::string& key, any value, bool forceUpdate)
{
	BSLock(_muMapAttr);
	
	bool ret;
	MAP_STR_ANY_IT item;
	item = _mapAttr.find(key);

	if (item != _mapAttr.end())
	{
		if (forceUpdate)
		{
			item->second = value;
			ret = true;
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		ret = _mapAttr.insert(MAP_STR_ANY_VT(key, value)).second;
	}

	return ret;
}

any Attrbute::getAttr(const std::string& key)
{
	any ret;
	MAP_STR_ANY_IT item;
	item = _mapAttr.find(key);
	if (item != _mapAttr.end())
	{
		ret = item->second;
	}

	return ret;
}

NS_END_MH
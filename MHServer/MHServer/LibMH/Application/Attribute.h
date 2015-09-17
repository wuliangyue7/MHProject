/*!
 * \file Attribute.h
 *
 * \author wuly
 * \date ¾ÅÔÂ 2015
 *
 * 
 */


#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include "../Common/MHComInc.h"
#include <typeinfo>

NS_BEGIN_MH

US_NS_BOOST;

class Attrbute
{
public:
	bool setAttr(const std::string& key, any value, bool forceUpdate = true);
	any getAttr(const std::string& key);

	template<typename T> T getAttr(const std::string& key, const T& defaultValue, bool withLock = false)
	{
		T ret = defaultValue;
		any val = getAttr(key);
		if (!val.empty())
		{
			try
			{
				ret = any_cast<T>(val);
			}
			catch (boost::bad_any_cast& e)
			{
				MH_WARING(e.what());
			}
		}

		return ret;
	}

private:
	BMutex _muMapAttr;
	std::map<std::string, any> _mapAttr;
};

NS_END_MH

#endif // __ATTRIBUTE_H__

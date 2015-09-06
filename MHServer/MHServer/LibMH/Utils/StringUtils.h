/*!
 * \file StringUtils.h
 *
 * \author wuly
 * \date ÎåÔÂ 2015
 *
 * 
 */


#ifndef __STRINGUTILS_H__
#define __STRINGUTILS_H__

#include <iostream>
#include <vector>
#include "../Common/MHMacro.h"

US_NS_STD

class StringUtils
{
public:
	static void trim(string& str, char chr);
	static vector<string> split(string& str, string pattern);
};

#endif // __StringUtils_H__

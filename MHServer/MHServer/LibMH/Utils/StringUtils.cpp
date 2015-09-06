#include "StringUtils.h"

void StringUtils::trim(string& str, char chr)
{
	string::size_type pos = str.find_first_of(chr);
	while (pos != string::npos)
	{
		str.erase(pos, 1);
		pos = str.find_first_of(chr);
	}
}

vector<string> StringUtils::split(string& str, string pattern)
{
	vector<string> ret;
	if (pattern.empty()) return ret;
	size_t start = 0, index = str.find_first_of(pattern, 0);
	while (index != str.npos)
	{
		if (start != index)
			ret.push_back(str.substr(start, index - start));
		start = index + 1;
		index = str.find_first_of(pattern, start);
	}
	if (!str.substr(start).empty())
		ret.push_back(str.substr(start));
	return ret;
}
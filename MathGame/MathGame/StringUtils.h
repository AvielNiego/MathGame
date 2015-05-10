#ifndef __STRING_UTILS_H_
#define __STRING_UTILS_H_

#include <sstream>

using namespace std;

class StringUtils
{
public:
	static string toString(int Number)
	{
		ostringstream ss;
		ss << Number;
		return ss.str();
	}
};

#endif
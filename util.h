#ifndef KHAKI_UTIL_H
#define KHAKI_UTIL_H

#include <memory>
#include <string>
#include <vector>

namespace khaki
{

class noncopyable {
public:
    noncopyable() {};
private:
    noncopyable(const noncopyable&);
    noncopyable& operator=(const noncopyable&);
};

class util {
public:
	static void strSplit(const std::string & src, const std::string & sep, std::vector<std::string>& tokens );

	static std::string string_format( const std::string fmt_str, ... );
};
}

#endif //KHAKI_UTIL_H
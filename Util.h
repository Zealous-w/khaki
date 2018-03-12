#ifndef KHAKI_UTIL_H
#define KHAKI_UTIL_H

#include <memory>
#include <string>
#include <vector>
#include <fcntl.h>

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

	static int getTime();
    static int getTimeMs();

    static int setNonBlock(int fd, bool value=true);
    
    static int setReuseAddr(int fd, bool value=true);
    static void setTcpNodelay(int fd);
};
}

#endif //KHAKI_UTIL_H
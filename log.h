#ifndef KHAKI_LOG_H
#define KHAKI_LOG_H

#include "util.h"

#include <string>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <time.h>
#include <utility>
#include <stdarg.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>
#include <map>
#include <string>

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace khaki {
extern log4cpp::Category& logger;
inline void InitKhakiLog(log4cpp::Category &logger, std::string filename, int level) {
	log4cpp::PatternLayout* layout = new log4cpp::PatternLayout(); 
	layout->setConversionPattern("%d: %p %c %x: %m%n");          
	log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender", filename);
	appender->setLayout(layout);    
	logger.setAdditivity(false);
	logger.setAppender(appender);
	logger.setPriority(level);    
}

#define log4cppInfo(logger, ...) \
	logger.info(__VA_ARGS__)
#define log4cppWarn(logger, ...) \
	logger.warn(__VA_ARGS__)
#define log4cppDebug(logger, ...) \
	logger.debug(__VA_ARGS__)

class Log : public khaki::noncopyable {
public:
	typedef std::map<int, std::string> MapLogLevelStr;
	enum LogLevel
	{
		E_LOG_DEBUG = 0,
		E_LOG_INFO  = 1,
		E_LOG_WARN  = 2,
		E_LOG_EROR  = 3,
		E_LOG_FATAL = 4,
	};

	Log()
	{ 
		level_ = E_LOG_DEBUG;
		mLogLv[E_LOG_DEBUG] = "DBUG";
		mLogLv[E_LOG_INFO] = "INFO";
		mLogLv[E_LOG_WARN] = "WARN";
		mLogLv[E_LOG_EROR] = "EROR";
		mLogLv[E_LOG_FATAL] = "FATL";
	}
	~Log(){}

	static Log& getLog()
	{
		static Log l;
		return l;
	}	

	void setLogLevel( int level ) { level_ = level; }

	void print(int level, int line, const char* file, const char* function, const char* fmt... )
	{
		char buffer[4 * 1024] = {0};
		char *begin = buffer;
		char *end = buffer + sizeof(buffer);

		va_list args;

		struct timeval now;
		gettimeofday(&now, NULL);
		const time_t seconds = now.tv_sec;

		struct tm t;
		localtime_r(&seconds, &t);

		begin += snprintf(begin, end - begin, 
				"%04d/%02d/%02d-%02d:%02d:%02d [%s] [%10s] %s:%d ",
		        t.tm_year + 1900,
		        t.tm_mon + 1,
		        t.tm_mday,
		        t.tm_hour,
		        t.tm_min,
		        t.tm_sec,
		        mLogLv[level].c_str(),
		        function,
		        file,
		        line);

		va_start(args, fmt);
		begin += vsnprintf(begin, end-begin, fmt, args);
		va_end(args);
		if ( level_ <= level ) printf("%s\n", buffer);
	}	
private:
	int level_;
	MapLogLevelStr mLogLv;
};

#define klog(level, ...) \
	do {\
		Log::getLog().print(level, __LINE__, __FILE__, __func__, __VA_ARGS__);\
	}while(0)

#define klog_debg(...) \
		klog(Log::LogLevel::E_LOG_DEBUG, __VA_ARGS__)
#define klog_info(...) \
		klog(Log::LogLevel::E_LOG_INFO, __VA_ARGS__)
#define klog_error(...) \
		klog(Log::LogLevel::E_LOG_EROR, __VA_ARGS__)
#define klog_warn(...) \
		klog(Log::LogLevel::E_LOG_WARN, __VA_ARGS__)
#define klog_fatal(...) \
		klog(Log::LogLevel::E_LOG_FATAL, __VA_ARGS__)

}
#endif //KHAKI_LOG_H
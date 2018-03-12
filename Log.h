#ifndef KHAKI_LOG_H
#define KHAKI_LOG_H
#include <iostream>
#include "Util.h"
#include <log4cpp/Category.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace khaki {
extern log4cpp::Category& logger;
inline void InitLog(log4cpp::Category &logger, std::string filename, int level) {
	log4cpp::PatternLayout* layoutFile = new log4cpp::PatternLayout(); 
	layoutFile->setConversionPattern("[%d] [%p]%x %m%n");          
	log4cpp::PatternLayout* layoutCout = new log4cpp::PatternLayout(); 
	layoutCout->setConversionPattern("[%d] [%p]%x %m%n");         
	log4cpp::RollingFileAppender* rollfileAppender = new log4cpp::RollingFileAppender("rollfileAppender", filename, 10*1024*1024, 100);
	rollfileAppender->setLayout(layoutFile);
	log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &std::cout);
	osAppender->setLayout(layoutCout);
	logger.setAdditivity(false);
	logger.setAppender(rollfileAppender);
	logger.setAppender(osAppender);
	logger.setPriority(level);    
}
#define LOGCOMMON(fmt) std::string("(").append(__FILE__).append(":").append("%d) ").append(fmt).c_str()
#define log4cppInfo(logger, fmt, ...) \
	logger.info(LOGCOMMON(fmt), __LINE__, ##__VA_ARGS__)
#define log4cppWarn(logger, fmt, ...) \
	logger.warn(LOGCOMMON(fmt), __LINE__, ##__VA_ARGS__)
#define log4cppDebug(logger, fmt, ...) \
	logger.debug(LOGCOMMON(fmt), __LINE__, ##__VA_ARGS__)
#define log4cppError(logger, fmt, ...) \
	logger.error(LOGCOMMON(fmt), __LINE__, ##__VA_ARGS__)
}
#endif //KHAKI_LOG_H
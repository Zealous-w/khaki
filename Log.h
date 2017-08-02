#ifndef KHAKI_LOG_H
#define KHAKI_LOG_H
#include <iostream>

#include <log4cpp/Category.hh>
#include <log4cpp/RollingFileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace khaki {
extern log4cpp::Category& logger;
inline void InitLog(log4cpp::Category &logger, std::string filename, int level) {
	log4cpp::PatternLayout* layoutFile = new log4cpp::PatternLayout(); 
	layoutFile->setConversionPattern("%d: %p %c %x: %m%n");          
	log4cpp::PatternLayout* layoutCout = new log4cpp::PatternLayout(); 
	layoutCout->setConversionPattern("%d: %p %c %x: %m%n");         
	log4cpp::RollingFileAppender* rollfileAppender = new log4cpp::RollingFileAppender("rollfileAppender", filename, 100*1024*1024, 100);
	rollfileAppender->setLayout(layoutFile);
	log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &std::cout);
	osAppender->setLayout(layoutCout);
	logger.setAdditivity(false);
	logger.setAppender(rollfileAppender);
	logger.setAppender(osAppender);
	logger.setPriority(level);    
}

#define log4cppInfo(logger, ...) \
	logger.info(__VA_ARGS__)
#define log4cppWarn(logger, ...) \
	logger.warn(__VA_ARGS__)
#define log4cppDebug(logger, ...) \
	logger.debug(__VA_ARGS__)
#define log4cppError(logger, ...) \
	logger.error(__VA_ARGS__)
}
#endif //KHAKI_LOG_H
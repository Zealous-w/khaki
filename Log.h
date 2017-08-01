#ifndef KHAKI_LOG_H
#define KHAKI_LOG_H
#include <iostream>

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

namespace khaki {
extern log4cpp::Category& logger;
inline void InitLog(log4cpp::Category &logger, std::string filename, int level) {
	log4cpp::PatternLayout* layout = new log4cpp::PatternLayout(); 
	layout->setConversionPattern("%d: %p %c %x: %m%n");          
	log4cpp::Appender* appender = new log4cpp::FileAppender("FileAppender", filename);
	appender->setLayout(layout);
	log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &std::cout);
	osAppender->setLayout(layout);
	logger.setAdditivity(false);
	logger.setAppender(appender);
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
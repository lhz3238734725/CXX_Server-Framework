#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <memory>
#include <list>

#include "LogLevel.h"
#include "LogAppender.h"

namespace cxxsf{

class Logger
{   
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string &name = "root");

    void log(LogLevel level, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();

    LogLevel getLevel() const;
    void setLevel(LogLevel level);

    const std::string& getName() const;
private:
    std::string m_name;
    LogLevel m_level;
    std::list<LogAppender::ptr> m_appenders;
};
}
#endif
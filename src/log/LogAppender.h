#ifndef __LOG_APPENDER_H__
#define __LOG_APPENDER_H__

#include <memory>

#include "LogLevel.h"
#include "LogEvent.h"
#include "LogFormatter.h"

namespace cxxsf{
    
class LogAppender
{
public:
    typedef std::shared_ptr<LogAppender> ptr;

    LogAppender();
    virtual ~LogAppender();

    virtual void log(LogLevel level, LogEvent::ptr event) = 0;
protected:
    LogLevel m_level;
    LogFormatter::ptr m_formater;
};
}


#endif
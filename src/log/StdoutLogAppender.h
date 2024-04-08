#ifndef __STDOUT_LOG_APPENDER_H__
#define __STDOUT_LOG_APPENDER_H__

#include "LogAppender.h"

namespace cxxsf{
class StdoutLogAppender : public LogAppender
{
private:
    /* data */
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;

    StdoutLogAppender();
    ~StdoutLogAppender();

    void log(LogLevel level, LogEvent::ptr event) override;
};
}

#endif
#ifndef __LOG_EVENT_H__
#define __LOG_EVENT_H__

#include <memory>
#include <stdint.h>
#include <string>
#include <sstream>

#include "Logger.h"

namespace cxxsf{

class LogEvent
{
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent(std::shared_ptr<Logger> logger, LogLevel level
            , const char* file, uint32_t line, uint32_t elapse 
            , uint32_t threadId, uint32_t filberId, uint64_t time
            , const std::string &threadName);

    const char *getFile() const;
    uint32_t getLine() const;
    uint32_t getThreadId() const;
    uint32_t getFilberId() const;
    uint32_t getElapse() const;
    uint64_t getTime() const;
    const std::string &getThreadName() const;
    std::string gerContent() const;
    std::shared_ptr<Logger> getLogger() const;
    LogLevel gerLevel() const;
    std::stringstream& getSS();

private:
    // 文件名
    const char *m_file = nullptr;
    // 行号
    uint32_t m_line = 0;
    // 线程ID
    uint32_t m_threadId = 0;
    // 携程ID
    uint32_t m_filberId = 0;
    // 程序启动到现在的毫秒数
    uint32_t m_elapse = 0;
    // 时间戳
    uint64_t m_time = 0;
    // 线程名称
    std::string m_threadName;
    // 日志内容流
    std::stringstream m_ss;
    // 日志器
    std::shared_ptr<Logger> m_logger;
    // 日志等级
    LogLevel m_level;
};
}

#endif
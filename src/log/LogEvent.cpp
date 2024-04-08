#include "LogEvent.h"

namespace cxxsf{
LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel level
        , const char* file, uint32_t line, uint32_t elapse 
        , uint32_t threadId, uint32_t filberId, uint64_t time
        , const std::string &threadName) 
        : m_logger(logger)
        , m_level(level)
        , m_file(file)
        , m_line(line)
        , m_elapse(elapse)
        , m_threadId(threadId)
        , m_filberId(filberId)
        , m_time(time)
        , m_threadName(threadName){

}

const char *LogEvent::getFile() const{
    return m_file;
}

uint32_t LogEvent::getLine() const{
    return m_line;
}

uint32_t LogEvent::getThreadId() const{
    return m_threadId;
}

uint32_t LogEvent::getFilberId() const{
    return m_filberId;
}

uint32_t LogEvent::getElapse() const{
    return m_elapse;
}

uint64_t LogEvent::getTime() const{
    return m_time;
}

const std::string &LogEvent::getThreadName() const{
    return m_threadName;
}

std::string LogEvent::gerContent() const{
    return m_ss.str();
}

std::shared_ptr<Logger> LogEvent::getLogger() const{
    return m_logger;
}

LogLevel LogEvent::gerLevel() const{
    return m_level;
}

std::stringstream& LogEvent::getSS(){
    return m_ss;
}

}
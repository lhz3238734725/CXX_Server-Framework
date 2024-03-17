#ifndef __CXXSF_LOG_H__
#define __CXXSF_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <stringstream>
#include <fstream>
#include <vector>

namespace cxxsf{

class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent();
private:
    const char *m_file = nullptr;
    int32_t  m_line = 0;
    uint32_t m_elapse = 0;
    uint32_t m_threadId = 0;
    uint32_t m_fiberId = 0;
    uint64_t m_time;
    std::string m_content;
};

enum class LogLevel{
    DEBUG = 1,
    INFO,
    WARN,
    ERROR,
    FATAL
};

class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    LogFormatter(const std::string &pattern);
    virtual void format(LogEvent::ptr event);
private:
    class FormatItem {
    public:
        typedef std::shared<FormatItem> ptr;

        virtual ~FormatItem() = {};
        virtual std::string format(std::ostream &os, LogEvent::ptr event) = 0;
    };

    void init();
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;

};

class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;

    LogAppender();
    virtual ~LogAppender() = {};
    virtual void log(LogLevel level, LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr formatter);
    LogFormatter::ptr getFormatter();
protected:
    LogLevel m_level;
    LogFormatter::ptr m_formatter;
};

class Logger{
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string & name = "root");
    void log(LogLevel level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

    LogLevel getLevel();
    void setLevel(LogLevel level);
private:
    std::string m_name;
    LogLevel m_level;
    std::list<LogAppender::ptr> m_appenders;
};

class StdoutLogAppender : public LogAppender {
public:
    typedef std::shared<StdoutLogAppender> ptr; 

    StdoutLogAppender();
    void log(LogLevel level, LogEvent::ptr event) override;
private:
};

class FileLogAppender : public LogAppender {
public:
    typedef std::shared<FileLogAppender> ptr; 

    FileLogAppender(const std::string &filename);
    void log(LogLevel level, LogEvent::ptr event) override; 

    bool reopen();
private:
    std::string m_filename;
    std::ofstream m_filestream;
};

}

#endif
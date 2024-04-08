#ifndef __LOG_FORMATTER_H__
#define __LOG_FORMATTER_H__

#include <memory>
#include <iostream>
#include <vector>

#include "LogLevel.h"
#include "LogEvent.h"
namespace cxxsf{

class LogFormatter
{
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    LogFormatter(const std::string &pattern);
    ~LogFormatter();

    std::string format(LogLevel level, LogEvent::ptr event);
public:
    class FormatItem{
    public:
        typedef std::shared_ptr<FormatItem> ptr;

        FormatItem();
        virtual ~FormatItem();

        virtual void format(std::ostream &os, LogLevel level, LogEvent event) = 0;
    };

    void init();
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
};

class MessageFormatItem : public LogFormatter::FormatItem{
public:
    MessageFormatItem(const std::string &fmt = "");
private:

};

class LevelFormatItem : public LogFormatter::FormatItem{
public:
    LevelFormatItem(const std::string &fmt = "");
private:

};

class ElapseFormatItem : public LogFormatter::FormatItem{
public:
    ElapseFormatItem(const std::string &fmt = "");
private:

};

class NameFormatItem : public LogFormatter::FormatItem{
public:
    NameFormatItem(const std::string &fmt = "");
private:

};

class ThreadIdFormatItem : public LogFormatter::FormatItem{
public:
    ThreadIdFormatItem(const std::string &fmt = "");
private:

};

class NewLineFormatItem : public LogFormatter::FormatItem{
public:
    NewLineFormatItem(const std::string &fmt = "");
private:

};

class DateTimeFormatItem : public LogFormatter::FormatItem{
public:
    DateTimeFormatItem(const std::string &fmt = "");
private:

};

class FileNameFormatItem : public LogFormatter::FormatItem{
public:
    FileNameFormatItem(const std::string &fmt = "");
private:

};

class LineFormatItem : public LogFormatter::FormatItem{
public:
    LineFormatItem(const std::string &fmt = "");
private:

};

class TabFormatItem : public LogFormatter::FormatItem{
public:
    TabFormatItem(const std::string &fmt = "");
private:

};

class FilberIdFormatItem : public LogFormatter::FormatItem{
public:
    FilberIdFormatItem(const std::string &fmt = "");
private:

};

class ThreadNameFormatItem : public LogFormatter::FormatItem{
public:
    ThreadNameFormatItem(const std::string &fmt = "");
private:

};

class StringFormatItem : public LogFormatter::FormatItem{
public:
    StringFormatItem(const std::string &str) : m_str(str){

    }

    void format(std::ostream &os, LogLevel level, LogEvent event){
        
    }
private:
    std::string m_str;
};

}

#endif
#ifndef __FILE_LOG_APPENDER_H__
#define __FILE_LOG_APPENDER_H__

#include <fstream>
#include "LogAppender.h"

namespace cxxsf{

class FileLogAppender : public LogAppender
{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;

    FileLogAppender();
    ~FileLogAppender();

    void log(LogLevel level, LogEvent::ptr event) override;
private:
    std::string m_filename;
    std::ofstream m_filestream;
};
}

#endif
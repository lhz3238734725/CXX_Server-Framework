#include "FileLogAppender.h"

namespace cxxsf{
FileLogAppender::FileLogAppender(){

}

FileLogAppender::~FileLogAppender(){

}

void FileLogAppender::log(LogLevel level, LogEvent::ptr event){
    if(level >= m_level){
        m_filestream << m_formater->format(level, event);
    }
}
}
#include "StdoutLogAppender.h"

#include <iostream>

namespace cxxsf{
StdoutLogAppender::StdoutLogAppender(){
}

StdoutLogAppender::~StdoutLogAppender(){
}

void StdoutLogAppender::log(LogLevel level, LogEvent::ptr event){
    if(level >= m_level){
        std::cout << m_formater->format(level, event);
    }
}
}
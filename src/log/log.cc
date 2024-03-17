#include "log.h"

namespace cxxsf{

LogFormatter::LogFormatter(const std::string &pattern){

}

void format(LogEvent::ptr event){
    std::stringstream ss;
    for(auto& i : m_items){
        i.format(ss, event);
    }

    return ss.str();
}

// %xxx %xxx{xxx} %%
void LogFormatter::init(){
    // str fmt  type(0 普通字符串 1 自定义类型字符串)
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string nstr;

    for (size_t i = 0; i < m_pattern.size(); ++i)
    {   
        // 判断是不是 % 字符
        if(m_pattern[i] != '%'){
            // 不是
            nstr.append(m_pattern[i], 1);
            continue;   
        }

        // 是
        if(i + 1 < m_pattern.size()){
            //判断是不是 %% 字符 
            if(m_pattern[i + 1] == '%'){
                nstr.append('%', 1);
                ++i;
                continue;
            }
        }

        // 进行%xxx 和 %xxx{xxx} 格式解析
        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;    // 存储 %xxx 中的xxx数据
        std::string fmt;    // 存储 {xxx} 中的xxx数据

        while (n < m_pattern.size())
        {
           if(fmt_status == 0){
                if(m_pattern[n] == '{'){
                    str = m_pattern.substr(i + 1, n - i - 1); 
                    fmt_status = 1;
                    fmt_begin = n;
                    ++n;
                    continue;
                }
           }else if (fmt_status == 1)
           {
                if(m_pattern[n] == '}'){
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    fmt_status = 0;
                    break;
                }
           }

           ++n;
           if( n == m_pattern.size()){
                if (str.empty())
                {
                    str.substr(i + 1);   
                }
           }
        }

        if(fmt_status == 0){
            if(!nstr.empty()){
                vec.push_back(std::make_tuple(nstr, "", 0));
                nstr.clear();
            }

            vec.push_back(std::make_tuple(str, fmt, 1));
        }else if (fmt_status == 1)
        {
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }   
    }

    if(!nstr.empty()){
        vec.push_back(std::make_tuple(nstr, "", 0));
    }

    static std::map<std::string, std::function<FormatItem::ptr(const std::string &fmt)>> s_format_items = {
#define XX(str, C) \
    {#str, [](const std::string& fmt){ return FormatItem::ptr(new C(fmt)) };}

#undef XX 
    };

    for (auto &i : vec)
    {
        if(std::get<2>(i) == 0){

        }else{

        }
    }
}

LogAppender::LogAppender(){

}

void LogAppender::setFormatter(LogFormatter::ptr formatter){
    m_formatter = formatter;
}

LogFormatter::ptr LogAppender::getFormatter(){
    return m_formatter;
}

Logger::Logger(const std::string & name = "root"){

}

void Logger::log(LogLevel level, LogEvent::ptr event){
    if(level >= m_level){
        for (auto &i : m_appenders)
        {
            i->log(level, event);   
        }
    }
}

void Logger::debug(LogEvent::ptr event){
    log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event){
    log(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);
}

void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);
}

void Logger::addAppender(LogAppender::ptr appender){
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender){
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
    {
        if(*it == appender){
            m_appenders.earse(it);
            break;
        }
    } 
}

LogLevel Logger::getLevel(){
    return m_level;
}

void Logger::setLevel(LogLevel level){
    m_level = level;
}

StdoutLogAppender::StdoutLogAppender(){

}

void StdoutLogAppender::log(LogLevel level, LogEvent::ptr event){
    if(level >= m_level){
        std::cout << m_formatter->format(event);
    }
}

FileLogAppender::FileLogAppender(const std::string &filename){

}

void FileLogAppender::reopen(){
    if(m_filestream){
        m_filestream.close();
    }
    m_filestream.open(m_filename);

    return !!m_filestream;
}

void FileLogAppender::log(LogLevel level, LogEvent::ptr event){
    if(level >= m_level){
        m_filestream << m_formatter->format(event);
    }
}

}
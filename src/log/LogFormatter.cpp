#include "LogFormatter.h"
#include <map>
#include <functional>

namespace cxxsf{
LogFormatter::LogFormatter(const std::string &pattern)
    : m_pattern(pattern){

}

LogFormatter::~LogFormatter(){

}

std::string LogFormatter::format(LogLevel level, LogEvent::ptr event){
    for (auto &i : m_items)
    {

    }   
}

// 格式类型 普通字符 %字母 %字母{} %%
void LogFormatter::init(){

    std::string commonStr;
    std::vector<std::tuple<std::string, std::string, int>> vec; // str(字符串)  fmt({})  type(0：表示普通字符 %% 1：%字母 %字母{})

    for (size_t i = 0; i < m_pattern.size(); ++i)
    {   
        // 普通字符
        if(m_pattern[i] != '%'){
            commonStr.append(m_pattern[i], 1);
            continue;
        }

        // %%
        if(i + 1 < m_pattern.size()){
            if(m_pattern[i + 1] == '%'){
                commonStr.append('%', 1);
                ++i;
                continue;
            }
        }

        // %字母 %字母{}
        size_t n = i + 1;
        size_t fmt_status = 0;
        size_t fmt_begin = 0;
        std::string str;
        std::string fmt;
        while (n < m_pattern.size())
        {
            if(fmt_status == 0 && !isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}'){
                str = m_pattern.substr(i + 1, n - (i + 1));
                break;
            }
            if(fmt_status == 0){
                if(m_pattern[n] == '{'){
                    str = m_pattern.substr(i + 1, n -(i + 1));
                    fmt_status = 1;
                    fmt_begin = n;
                    continue;
                }
            }else if(fmt_status == 1){
                if(m_pattern[n] == '}'){
                    fmt = m_pattern.substr(fmt_begin + 1, n -(fmt_begin + 1));
                    fmt_status = 0;
                    break;
                }
            }
        ++n;
        if(n == m_pattern.size()){
            if(str.empty()){
                str = m_pattern.substr(i+1);
            }
        }   
        }

        if(fmt_status == 0){
            if(!commonStr.empty()){
                vec.push_back(std::make_tuple(commonStr, "", 0));
                commonStr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
        }else{
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    }

    if(!commonStr.empty()){
        vec.push_back(std::make_tuple(commonStr, "", 0));
    }

    static std::map<std::string, std::function<FormatItem::ptr(const std::string &fmt)>> formatItems = {
#define XX(str, ObjName) \
    {#str, [](const std::string &fmt) { return FormatItem::ptr(new ObjName(fmt));}}

    XX(m, MessageFormatItem),       //m:消息
    XX(p, LevelFormatItem),         //p:日志级别
    XX(r, ElapseFormatItem),        //r:累计毫秒数
    XX(c, NameFormatItem),          //c:日志名称
    XX(t, ThreadIdFormatItem),      //t:线程id
    XX(n, NewLineFormatItem),       //n:换行
    XX(d, DateTimeFormatItem),      //d:时间
    XX(f, FileNameFormatItem),      //f:文件名
    XX(l, LineFormatItem),          //l:行号
    XX(T, TabFormatItem),           //T:tab
    XX(F, FilberIdFormatItem),      //F:协程id
    XX(N, ThreadNameFormatItem),    //N:线程名称
#undef XX
    };

    for(auto &i : vec){
        if(std::get<2>(i) == 0){
            m_items.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        }else{
            auto it = formatItems.find(std::get<0>(i));
            if(it == formatItems.end()){
                m_items.push_back(FormatItem::ptr(new StringFormatItem("<< error format %" + std::get<0>(i))));
            }else{
                m_items.push_back(it->second(std::get<1>(i)));
            }
        }
    }
}

}
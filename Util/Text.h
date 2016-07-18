#pragma once

#include <string>

namespace Util {

class Text
{
public:
    Text();
    ~Text();

public: // public classes

    struct Convert
    {
        static std::wstring     wcsFromUtf(const std::string &str);
        static std::string      utfFromWcs(const std::wstring &str);
    };

public: // class interface
    static void replaceAll(
        std::string &source, 
        const std::string &from, 
        const std::string &to);
    static void trimInPlace(std::string &text);
};

} // namespace Util

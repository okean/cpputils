#pragma once

#include <string>

namespace Util
{

class Text
{
public:
    Text();
    ~Text();

public: // class interface
    static void replaceAll(
        std::string &source, 
        const std::string &from, 
        const std::string &to);
};

} // namespace Util

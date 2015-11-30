#pragma once

#include <string>

namespace Util {

class NameValuePair
{
public:
    NameValuePair(
        const std::string &name,
        const std::string &value);
    NameValuePair(
        const std::string &str,
        const char & separator,
        bool trim = false);
    ~NameValuePair();

public: // interface
    const std::string & name() const;
    const std::string & value() const;
    
    std::string toString(const char & separator = '=') const;

private: // internal static helpers
    static void split(
        std::string &name,
        std::string &value,
        const std::string &str,
        const char & separator,
        bool trim);

private: //member variables
    std::string _name;
    std::string _value;
};

} // namespace Util

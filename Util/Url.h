#pragma once

#include <string>

namespace Util {

class Url
{
public:
    Url(const std::string &url);
    ~Url();

public: // interface
    operator const std::string () const;

private: // member variables
    std::string _url;
};

} // namespace Util
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

    const Url append(const std::string &path);

private: // internal class helpers
    static bool bwginWithForwardSlash(const std::string &path);

private: // internal helpers
    void removeForwardSlashFromUrl();
    void appendForwardSlashToUrl();

private: // member variables
    std::string _url;
};

} // namespace Util

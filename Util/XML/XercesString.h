#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <string>

namespace Util {
namespace XML {

class XercesString
{
public:
    XercesString(const std::string &xmlCh);
    virtual ~XercesString();

public: // interface
    operator const wchar_t* () const;

public: // class helpers
    static std::string convert(const wchar_t* xmlCh);

private: // member variables
    wchar_t* _xmlCh;
};

} // namespace XML
} // namespace Util
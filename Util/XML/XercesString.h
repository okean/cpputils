#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <string>

XercescForwardDeclare(DOMNode);

namespace Util {
namespace XML {

class XercesString
{
public:
    XercesString(const std::string &xmlCh);
    virtual ~XercesString();

public: // public typedefs
    typedef Xercesc::DOMNode DomNodeImpl;

public: // interface
    operator const wchar_t* () const;

public: // class helpers
    static std::string convert(const wchar_t* xmlCh);
    static std::string serialize(const DomNodeImpl* node);

private: // member variables
    wchar_t* _xmlCh;
};

} // namespace XML
} // namespace Util

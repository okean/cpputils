#pragma once

#include <string>

namespace Util {
namespace XML {

class XmlAttribute
{
public:
    XmlAttribute(const std::string &name);
    virtual ~XmlAttribute();

public: // interface
    const std::string & name() const;

private: // member variables
    std::string _name;
};

} // namespace XML
} // namespace Util

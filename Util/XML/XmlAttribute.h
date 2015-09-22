#pragma once

#include <string>

namespace Util {
namespace XML {

class XmlAttribute
{
public:
    XmlAttribute(const std::string &name);
    XmlAttribute(
        const std::string &name, 
        const std::string &value);
    virtual ~XmlAttribute();

public: // interface
    const std::string & name() const;
    const std::string & value() const;

private: // member variables
    std::string _name;
    std::string _value;
};

} // namespace XML
} // namespace Util

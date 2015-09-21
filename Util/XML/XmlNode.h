#pragma once

#include <string>

namespace Util {
namespace XML {

class XmlNode
{
public:
    XmlNode(const std::string &name);
    virtual ~XmlNode();

public: // interface
    const std::string & name() const;

private: // member variables
    std::string _name;
};

} // namespace Xml
} // namespace Util
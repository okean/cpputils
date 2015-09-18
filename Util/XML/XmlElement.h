#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <Util/NonCopyable.hpp>
#include <memory>

XercescForwardDeclare(DOMElement);

namespace Util {
namespace XML {

class XmlAttribute;

class XmlElement : public Util::NonCopyable
{
public:
    XmlElement(Xercesc::DOMElement &elem);
    virtual ~XmlElement();

public: // public typedefs
    typedef XML::XmlAttribute   XmlAttribute;

public: // interface
    bool        contains(const XmlAttribute & attr) const;
    std::string get(const XmlAttribute & attr) const;

private: // internal typedefs
    typedef Xercesc::DOMElement         DomElementImpl;

private: // member variables
    DomElementImpl &_impl;
};

typedef std::shared_ptr<XmlElement> XmlElementPtr;

} // namespace XML
} // namespace Util

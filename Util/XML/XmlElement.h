#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <Util/NonCopyable.hpp>
#include <memory>
#include <functional>
#include <vector>

XercescForwardDeclare(DOMElement);
XercescForwardDeclare(DOMNode);

namespace Util {
namespace XML {

class XmlElement;
typedef std::shared_ptr<XmlElement>     XmlElementPtr;
typedef std::vector<XmlElementPtr>      XmlElements;
typedef std::shared_ptr<XmlElements>    XmlElementsPtr;

class XmlAttribute;
class XmlNode;

class XmlElement : public Util::NonCopyable
{
public:
    XmlElement(Xercesc::DOMElement &elem);
    virtual ~XmlElement();

public: // public typedefs
    typedef XML::XmlAttribute               XmlAttribute;
    typedef XML::XmlNode                    XmlNode;

public: // interface
    bool            contains(const XmlAttribute &attr) const;
    std::string     get(const XmlAttribute &attr) const;
    void            set(const XmlAttribute &attr);
    
    std::string     text() const;
    std::string     name() const;

    XmlElementPtr   get(const XmlNode &node) const;
    XmlElementsPtr  nodes() const;
    void remove(const XmlElement &elem);
    void clear();

    operator Xercesc::DOMNode* () const;

private: // internal typedefs
    typedef Xercesc::DOMElement         DomElementImpl;
    typedef Xercesc::DOMNode            DomNodeImpl;

private: // internal class helpers
    static bool isElementNode(const DomNodeImpl &node);
    static bool isTextNode(const DomNodeImpl &node);

private: // internal helpers
    void forEachNode(std::function<bool(DomNodeImpl &)> onNode) const;

private: // member variables
    DomElementImpl &_impl;
};

typedef std::shared_ptr<XmlElement> XmlElementPtr;

} // namespace XML
} // namespace Util

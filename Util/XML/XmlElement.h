#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <Util/NonCopyable.hpp>
#include <memory>
#include <functional>
#include <vector>

XercescForwardDeclare(DOMElement);
XercescForwardDeclare(DOMNode);
XercescForwardDeclare(DOMDocument);

namespace Util {
namespace XML {

class XmlElement;
typedef std::shared_ptr<XmlElement>     XmlElementPtr;
typedef std::vector<XmlElementPtr>      XmlElements;

class XmlAttribute;
class XmlNode;

class XmlElement : public Util::NonCopyable
{
public:
    XmlElement(Xercesc::DOMElement &elem);
    virtual ~XmlElement();

public: // public typedefs
    typedef XML::XmlAttribute               XmlAttribute;
    typedef std::shared_ptr<XmlAttribute>   XmlAttributePtr;
    typedef std::vector<XmlAttributePtr>    XmlAttributes;
    typedef XML::XmlNode                    XmlNode;

public: // interface
    bool                contains(const XmlAttribute &attr) const;
    std::string         get(const XmlAttribute &attr) const;
    void                set(const XmlAttribute &attr);
    XmlAttributes       attributes() const;
    
    std::string         text() const;
    XmlElementPtr       set(const std::string &text);
    std::string         name() const;
    XmlElementPtr       get(const XmlNode &node) const;
    XmlElementPtr       add(const XmlNode &node);
    void                addCopy(const XmlElement &child);
    void                add(const XmlElement &child);
    XmlElements         nodes() const;
    void remove(const XmlElement &elem);
    void clear();

    std::string toString() const;

    operator Xercesc::DOMNode* () const;

private: // internal typedefs
    typedef Xercesc::DOMElement         DomElementImpl;
    typedef Xercesc::DOMNode            DomNodeImpl;
    typedef Xercesc::DOMDocument        DOMDocumentImpl;

private: // internal class helpers
    static bool isElementNode(const DomNodeImpl &node);
    static bool isTextNode(const DomNodeImpl &node);

private: // internal helpers
    void forEachNode(std::function<bool(DomNodeImpl &)> onNode) const;
    DOMDocumentImpl * xmlDoc() const;

private: // member variables
    DomElementImpl &_impl;
};

typedef std::shared_ptr<XmlElement> XmlElementPtr;

} // namespace XML
} // namespace Util

#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <Util/XML/XmlPlatform.h>
#include <memory>

XercescForwardDeclare(XercesDOMParser);
XercescForwardDeclare(DOMDocument);

namespace Util {
namespace XML {

class XmlElement;

class XmlDoc : public XML::XmlPlatform
{
public:
    XmlDoc(const std::string &content);
    virtual ~XmlDoc();

public: // public typedefs
    typedef std::shared_ptr<XML::XmlElement> XmlElementPtr;

public: // interface
    XmlElementPtr root() const;
    std::string toString() const;

private: // internal typedefs
    typedef Xercesc::XercesDOMParser        XmlDom;
    typedef std::unique_ptr<XmlDom>         XmlDomPtr;

private: // internal class helpers
    static XmlDomPtr createXmlDomParser(const std::string &content);

private: // internal typedefs
    typedef Xercesc::DOMDocument DomDocumentImpl;

private: // internal helpers
    DomDocumentImpl * xmlDoc() const;

private: // member variables
    XmlDomPtr _xml;
};

typedef std::shared_ptr<XmlDoc> XmlDocPtr;

} // namespace XML
} // namespace Util

#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <Util/XML/XmlPlatform.h>
#include <memory>

XercescForwardDeclare(XercesDOMParser);

namespace Util {
namespace XML {

class XmlDoc : public Util::XML::XmlPlatform
{
public:
    XmlDoc(const std::string &content);
    virtual ~XmlDoc();

private: // internal typedefs
    typedef Xercesc::XercesDOMParser        XmlDom;
    typedef std::unique_ptr<XmlDom>         XmlDomPtr;

private: // internal class helpers
    static XmlDomPtr createXmlDomParser(const std::string &content);

private: // member variables
    XmlDomPtr _xml;
};

typedef std::shared_ptr<XmlDoc> XmlDocPtr;

} // namespace XML
} // namespace Util

#include "stdafx.h"
#include "XmlDoc.h"
#include "XmlElement.h"
#include "XercesString.h"
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

using namespace Util::XML;

XmlDoc::XmlDoc(const std::string &content)
    : XmlPlatform{}
    , _xml{ createXmlDomParser(content) }
{
}

XmlDoc::~XmlDoc()
{
}

// interface

XmlElementPtr XmlDoc::root() const
{
    return std::make_shared<XmlElement>(
        *xmlDoc()->getDocumentElement());
}

std::string XmlDoc::toString() const
{
    return XercesString::serialize(xmlDoc());
}

XmlDoc::operator Xercesc::DOMDocument *() const
{
    return xmlDoc();
}

// internal class helpers

XmlDoc::XmlDomPtr XmlDoc::createXmlDomParser(const std::string &content)
{
    try
    {
        std::unique_ptr<xercesc::XercesDOMParser> xml{ std::make_unique<xercesc::XercesDOMParser>() };

        xercesc::MemBufInputSource buf(
            reinterpret_cast<const XMLByte*>(content.c_str()), 
            content.size(), 
            __FUNCTION__);


        xml->setValidationScheme(xercesc::XercesDOMParser::Val_Never);
        xml->setDoNamespaces(true);
        xml->setDoSchema(true);
        xml->setLoadExternalDTD(false);

        xml->parse(buf);

        return xml;
    }
    catch (const xercesc::XMLException &ex)
    {
        rethrowWithMessage(ex, "Invalid XML content");
    }

    return XmlDomPtr{};
}

// internal helpers

XmlDoc::DomDocumentImpl * XmlDoc::xmlDoc() const
{
    return _xml->getDocument();
}

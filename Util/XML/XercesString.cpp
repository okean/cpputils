#include "stdafx.h"
#include "XercesString.h"
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <memory>

using namespace Util::XML;

XercesString::XercesString(const std::string &xmlCh) 
    : _xmlCh{ xercesc::XMLString::transcode(xmlCh.c_str()) }
{
}

XercesString::~XercesString()
{
    xercesc::XMLString::release(&_xmlCh);
}

// interface

XercesString::operator const wchar_t* () const
{
    return _xmlCh;
}

// class helpers

std::string XercesString::convert(const wchar_t* xmlCh)
{
    char* tmp = xercesc::XMLString::transcode(xmlCh);

    const std::string str{ tmp };

    xercesc::XMLString::release(&tmp);

    return str;
}

std::string XercesString::serialize(const DomNodeImpl* node)
{
    static const XMLCh gLS[] = { xercesc::chLatin_L, xercesc::chLatin_S, xercesc::chNull };
    xercesc::DOMImplementation *impl =
        xercesc::DOMImplementationRegistry::getDOMImplementation(gLS);

    xercesc::DOMLSSerializer* serializer = 
        ((xercesc::DOMImplementationLS*)impl)->createLSSerializer();

    XMLCh* str = NULL;

    try 
    {
        str = serializer->writeToString(node);
    }
    catch (const xercesc::XMLException& ex)
    {
        const std::string message{ convert(ex.getMessage()) };

        throw std::exception(
            ("Failed to serialize: " + message).c_str());
    }
    catch (...)
    {
        throw std::exception("Unexpected Exception");
    }

    serializer->release();

    if (str)
    {
        return convert(str);
    }

    return "";
}

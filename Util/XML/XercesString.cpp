#include "stdafx.h"
#include "XercesString.h"
#include <xercesc/util/XMLString.hpp>
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

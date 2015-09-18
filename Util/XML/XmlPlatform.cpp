#include "stdafx.h"
#include "XmlPlatform.h"
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace Util;
using namespace Util::XML;

XmlPlatform::XmlPlatform() : NonCopyable{}
{
    try
    {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException &ex)
    {
        rethrowWithMessage(ex, "XML toolkit initialization error");
    }
}

XmlPlatform::~XmlPlatform()
{
    try
    {
        xercesc::XMLPlatformUtils::Terminate();
    }
    catch (const xercesc::XMLException &ex)
    {
        rethrowWithMessage(ex, "XML toolkit teardown error");
    }
}

// protected class helpers

void XmlPlatform::rethrowWithMessage(
    const Xercesc::XMLException &ex,
    const std::string &messaage)
{
    throw std::exception(
        (messaage + ": " + messageFrom(ex)).c_str());
}

std::string XmlPlatform::messageFrom(
    const Xercesc::XMLException &ex)
{
    char* tmp = xercesc::XMLString::transcode(ex.getMessage());

    const std::string message{ tmp };

    xercesc::XMLString::release(&tmp);

    return message;
}

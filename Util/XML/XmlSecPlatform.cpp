#include "stdafx.h"
#include "XmlSecPlatform.h"
#include "XercesString.h"
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>

using namespace Util::XML;

XmlSecPlatform::XmlSecPlatform()
    : XmlPlatform   {}
    , _provider     { std::make_shared<ProviderImpl>() }
{
    try
    {
        XSECPlatformUtils::Initialise();
    }
    catch (XSECException &ex)
    {
        rethrowWithMessage(ex, "Failed to init XSEC platform");
    }
}

XmlSecPlatform::~XmlSecPlatform()
{
    try
    {
        XSECPlatformUtils::Terminate();
    }
    catch (XSECException &ex)
    {
        rethrowWithMessage(ex, "Failed to terminate XSEC platform");
    }
}

// protected interface

XmlSecPlatform::ProviderImpl & XmlSecPlatform::provider() const
{
    return *_provider;
}

// protecte class helpers

void XmlSecPlatform::rethrowWithMessage(
    XSECException &ex,
    const std::string &messaage)
{
    throw std::exception(
        (messaage + ": " + XercesString::convert(ex.getMsg())).c_str());
}

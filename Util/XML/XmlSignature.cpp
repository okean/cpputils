#include "stdafx.h"
#include "XmlSignature.h"
#include "XmlDoc.h"
#include "Sec/X509Cert.h"
#include "Sec/RsaKey.h"
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>
#include <xsec/dsig/DSIGSignature.hpp>

using namespace Util::XML;
using namespace Util::XML::Sec;

XmlSignature::XmlSignature(const XmlDoc & xml)
    : XmlSecPlatform    {}
    , _signature        { createSignatureFromDoc(provider(), xml) }
    , _error            {}
{
}

XmlSignature::~XmlSignature()
{
    provider().releaseSignature(_signature);
}

// interface

const std::string & XmlSignature::error() const
{
    return _error;
}

bool XmlSignature::validate(
    const RsaKey &key,
    const std::string &errMsg)
{
    return false;
}

// internal static helpers

XmlSignature::SignaturePtr XmlSignature::createSignatureFromDoc(
    ProviderImpl &provider,
    const XmlDoc &xml)
{
    SignaturePtr signature{};

    try
    {
        signature = provider.newSignatureFromDOM(xml);
        signature->load();
    }
    catch (XSECException &ex)
    {
        rethrowWithMessage(ex, "An error occured during a signature load");
    }

    return signature;
}

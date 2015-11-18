#include "stdafx.h"
#include "XmlSignature.h"
#include "XmlDoc.h"
#include "XercesString.h"
#include "Sec/X509Cert.h"
#include "Sec/Key.h"
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>
#include <xsec/dsig/DSIGSignature.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyRSA.hpp>
#include <xsec/enc/XSECCryptoException.hpp>

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

bool XmlSignature::validate(const Key &key)
{
    bool validate = false;

    try
    {
        _signature->setSigningKey(key);

        validate = _signature->verify();
        
        if (!validate)
        {
            _error = XercesString::convert(_signature->getErrMsgs());
        }
    }
    catch (XSECException &ex)
    {
        _error = "An error occured during signature validation: "
            + XercesString::convert(ex.getMsg());
    }
    catch (XSECCryptoException &ex)
    {
        _error = "An error occured in the XML-Security-C Crypto routines: "
            + std::string(ex.getMsg());
    }

    return validate;
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

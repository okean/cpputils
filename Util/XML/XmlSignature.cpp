#include "stdafx.h"
#include "Xml.hpp"
#include "Sec/X509Cert.h"
#include "Sec/Key.h"
#include <xsec/framework/XSECProvider.hpp>
#include <xsec/framework/XSECException.hpp>
#include <xsec/dsig/DSIGSignature.hpp>
#include <xsec/dsig/DSIGReference.hpp>
#include <xsec/dsig/DSIGKeyInfoX509.hpp>
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyRSA.hpp>
#include <xsec/enc/XSECCryptoException.hpp>

using namespace Util::XML;
using namespace Util::XML::Sec;

XmlSignature::XmlSignature()
    : XmlSecPlatform    {}
    , _signature        { createSignature(provider()) }
    , _error            {}
    , _signed           (false)
{
}

XmlSignature::XmlSignature(const XmlDoc & xml)
    : XmlSecPlatform    {}
    , _signature        { createSignatureFromDoc(provider(), xml) }
    , _error            {}
    , _signed           (false)
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
        rethrowWithMessage(ex, "An error occured during signature validation");
    }
    catch (XSECCryptoException &ex)
    {
        throw std::exception(("An error occured in the XML-Security-C Crypto routines: "
            + std::string(ex.getMsg())).c_str());
    }

    return validate;
}

bool XmlSignature::addCertificateInfo(const X509Cert &cert)
{
    try
    {
        if (_signed)
        {
            DSIGKeyInfoX509 * keyInfoX509 = _signature->appendX509Data();

            XercesString base64Certificate{ cert.base64Encoded() };
            XercesString issuer{ cert.issuer() };
            XercesString serial{ cert.serial() };

            keyInfoX509->appendX509Certificate(base64Certificate);
            keyInfoX509->setX509IssuerSerial(issuer, serial);
        }
        else
        {
            _error = "addCertificateInfo() called prior to sign() method";

            return false;
        }
    }
    catch (XSECException &ex)
    {
        rethrowWithMessage(ex, "Failed to append certificate info");
    }

    return true;
}

void XmlSignature::sign(XmlDoc &xml, const Sec::Key &key)
{
    try
    {
        XmlElementPtr rootNode{ xml.root() };

        XmlElementPtr sigNode{ std::make_shared<XmlElement>(
            *_signature->createBlankSignature(xml, CANON_C14N_COM, SIGNATURE_RSA, HASH_SHA1)) };

        rootNode->add(*sigNode);

        DSIGReference * ref = _signature->createReference(MAKE_UNICODE_STRING(""));
        ref->appendEnvelopedSignatureTransform();

        _signature->setSigningKey(key);
        _signature->sign();

        _signed = true;
    }
    catch (XSECException &ex)
    {
        rethrowWithMessage(ex, "An error occured while signing xml");
    }
}

// internal static helpers

XmlSignature::SignaturePtr XmlSignature::createSignature(
    ProviderImpl &provider)
{
    SignaturePtr signature{};

    try
    {
        signature = provider.newSignature();
    }
    catch (XSECException &ex)
    {
        rethrowWithMessage(ex, "An error occured during a signature load");
    }

    return signature;
}

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

#include "stdafx.h"
#include "X509Cert.h"
#include <Util/Text.h>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>
#include <openssl/x509.h>

using namespace Util;
using namespace Util::XML::Sec;

X509Cert::X509Cert(const std::string &base64Encoded)
    : _x509{ loadCertificate(base64Encoded) }
    , _base64Encoded(base64Encoded)
    , _issuer(getIssuer(x509()))
{
}

X509Cert::~X509Cert()
{
}

// interface

const std::string & X509Cert::base64Encoded() const
{
    return _base64Encoded;
}

const std::string & X509Cert::issuer() const
{
    return _issuer;
}

// internal class helpers

X509Cert::X509ImplPtr X509Cert::loadCertificate(const std::string &cert)
{
    X509ImplPtr x509{ std::make_shared<X509Impl>() };

    x509->loadX509Base64Bin(cert.c_str(), cert.size());

    return x509;
}

std::string X509Cert::getIssuer(X509 * x509)
{
    std::string issuer{ 
        X509_NAME_oneline(X509_get_issuer_name(x509), NULL, 0) };

    // convert issuer into a more traditional looking DN
    issuer.erase(0, 1);
    Text::replaceAll(issuer, "/", ", ");

    return issuer;
}

// internal helpers

X509 * X509Cert::x509() const
{
    return _x509->getOpenSSLX509();
}

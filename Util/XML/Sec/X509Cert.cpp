#include "stdafx.h"
#include "X509Cert.h"
#include <Util/Text.h>
#include <xsec/enc/OpenSSL/OpenSSLCryptoX509.hpp>
#include <openssl/x509.h>
#include <openssl/x509v3.h>

using namespace Util;
using namespace Util::XML::Sec;

X509Cert::X509Cert(const std::string &base64Encoded)
    : _x509{ loadCertificate(base64Encoded) }
    , _base64Encoded(base64Encoded)
    , _issuer(getIssuer(x509()))
    , _serial(getSerial(x509()))
{
}

X509Cert::~X509Cert()
{
}

// class interface

std::string X509Cert::algorithmToString(const int pkeyNid)
{
    const char* buf = OBJ_nid2ln(pkeyNid);

    std::string alg(buf, strlen(buf));

    return std::move(buf);
}

// interface

bool X509Cert::isValid() const
{
    return status() > 0;
}

const std::string & X509Cert::base64Encoded() const
{
    return _base64Encoded;
}

const std::string & X509Cert::issuer() const
{
    return _issuer;
}

const std::string & X509Cert::serial() const
{
    return _serial;
}

const int X509Cert::version() const
{
    return static_cast<int>(X509_get_version(x509())) + 1;
}

const int X509Cert::signatureAlgorithm() const
{
    int pkeyNid = OBJ_obj2nid(x509()->cert_info->key->algor->algorithm);

    if (pkeyNid == NID_undef)
    {
        throw std::exception(
            "Unable to find specified signature algorithm name");
    }

    return pkeyNid;
}

const int X509Cert::status() const
{
    // 0 not a CA
    // 1 is a CA
    // 2 basicConstraints absent so "maybe" a CA
    // 3 basicConstraints absent but self signed V1.
    // 4 basicConstraints absent but keyUsage present and keyCertSign asserted.

    return X509_check_ca(x509());
}

// internal class helpers

X509Cert::X509ImplPtr X509Cert::loadCertificate(const std::string &cert)
{
    X509ImplPtr x509{ std::make_shared<X509Impl>() };

    x509->loadX509Base64Bin(cert.c_str(), cert.size());

    return x509;
}

std::string X509Cert::getIssuer(X509 *x509)
{
    std::string issuer{ 
        X509_NAME_oneline(X509_get_issuer_name(x509), NULL, 0) };

    // convert issuer into a more traditional looking DN
    issuer.erase(0, 1);
    Text::replaceAll(issuer, "/", ", ");

    return std::move(issuer);
}

std::string X509Cert::getSerial(X509 *x509)
{
    ASN1_INTEGER *serial = X509_get_serialNumber(x509);

    BIGNUM *bn = ASN1_INTEGER_to_BN(serial, NULL);
    if (!bn)
    {
        throw std::exception("Unable to convert ASN1INTEGER to BN");
    }

    char *tmp = BN_bn2dec(bn);
    if (!tmp)
    {
        BN_free(bn);

        throw std::exception("Unable to convert BN to decimal string");
    }

    std::string serialStr(tmp, strlen(tmp));

    BN_free(bn);
    OPENSSL_free(tmp);

    return std::move(serialStr);
}

// internal helpers

X509 * X509Cert::x509() const
{
    return _x509->getOpenSSLX509();
}

#include "stdafx.h"
#include "RsaKey.h"
#include <xsec/enc/OpenSSL/OpenSSLCryptoKeyRSA.hpp>
#include <openssl/bio.h>
#include <openssl/pem.h>

using namespace Util::XML::Sec;

RsaKey::RsaKey(const std::string &base64Encoded)
    : _rsaKey{ createRsaKey(base64Encoded) }
    , _base64Encoded(base64Encoded)
{
}

RsaKey::~RsaKey()
{
}

// interface

RsaKey::operator OpenSSLCryptoKeyRSA * () const
{
    return static_cast<OpenSSLCryptoKeyRSA*>(_rsaKey->clone());
}

const std::string & RsaKey::base64Encoded() const
{
    return _base64Encoded;
}

// internal static helpers

RsaKey::RsaKeyImplPtr RsaKey::createRsaKey(const std::string &base64EncodedKey)
{
    // create bio for private key
    BIO * bioMem = BIO_new(BIO_s_mem());
    BIO_puts(bioMem, base64EncodedKey.c_str());

    if (!bioMem)
    {
        throw std::exception("Unable to create a BIO object");
    }

    // Create private key with bio
    EVP_PKEY * pk = PEM_read_bio_PrivateKey(bioMem, NULL, NULL, NULL);

    if (!pk)
    {
        BIO_free_all(bioMem);

        throw std::exception("Unable to get public RSA key");
    }

    RsaKeyImplPtr rsaKey{ std::make_unique<RsaKeyImpl>(pk) };

    EVP_PKEY_free(pk);
    BIO_free_all(bioMem);

    return rsaKey;
}

#pragma once

#include <string>
#include <memory>

class OpenSSLCryptoX509;
struct x509_st;

namespace Util {
namespace XML {
namespace Sec {

class X509Cert
{
public:
    X509Cert(const std::string &base64Encoded);
    ~X509Cert();

public: // class interface
    static std::string algorithmToString(const int pkeyNid);

public: // interface
    bool isValid() const;

    const std::string & base64Encoded() const;
    const std::string & issuer() const;
    const std::string & serial() const;

    const int version() const;
    const int signatureAlgorithm() const;
    const int status() const;

private: // internal typedef
    typedef OpenSSLCryptoX509           X509Impl;
    typedef std::shared_ptr<X509Impl>   X509ImplPtr;
    typedef x509_st                     X509;

private: // internal class helpers
    static X509ImplPtr loadCertificate(const std::string &cert);
    static std::string getIssuer(X509 *x509);
    static std::string getSerial(X509 *x509);

private: // internal helpers
    X509 * x509() const;

private: // member variables
    X509ImplPtr _x509;
    std::string _base64Encoded;
    std::string _issuer;
    std::string _serial;
};

typedef std::shared_ptr<X509Cert>   X509CertPtr;

} // namespace Sec
} // namespace XML
} // namespace Util

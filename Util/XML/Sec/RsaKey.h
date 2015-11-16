#pragma once

#include <string>
#include <memory>

class OpenSSLCryptoKeyRSA;

namespace Util {
namespace XML {
namespace Sec {

class RsaKey
{
public:
    RsaKey(const std::string &base64Encoded);
    ~RsaKey();

public: // interface
    operator OpenSSLCryptoKeyRSA * () const;

    const std::string & base64Encoded() const;

private: // internal typedefs
    typedef OpenSSLCryptoKeyRSA             RsaKeyImpl;
    typedef std::unique_ptr<RsaKeyImpl>     RsaKeyImplPtr;

private: // internal class helpers
    static RsaKeyImplPtr createRsaKey(const std::string &base64EncodedKey);

private: // member variables
    RsaKeyImplPtr   _rsaKey;
    std::string     _base64Encoded;
};

typedef std::shared_ptr<RsaKey>     RsaKeyPtr;

} // namespace Util
} // namespace XML
} // namespace Sec

#pragma once

#include "Key.h"
#include <memory>

class XSECCryptoKey;
class OpenSSLCryptoKeyRSA;

namespace Util {
namespace XML {
namespace Sec {

class RsaKey : public Key 
{
public:
    RsaKey(const std::string &base64Encoded);
    virtual ~RsaKey();

public: // interface
    operator XSECCryptoKey * () const;

private: // internal typedefs
    typedef OpenSSLCryptoKeyRSA             RsaKeyImpl;
    typedef std::unique_ptr<RsaKeyImpl>     RsaKeyImplPtr;

private: // internal class helpers
    static RsaKeyImplPtr createRsaKey(const std::string &base64EncodedKey);

private: // member variables
    RsaKeyImplPtr   _rsaKey;
};

typedef std::shared_ptr<RsaKey>     RsaKeyPtr;

} // namespace Util
} // namespace XML
} // namespace Sec

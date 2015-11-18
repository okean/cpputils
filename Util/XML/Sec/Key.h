#pragma once

#include <string>

class XSECCryptoKey;

namespace Util {
namespace XML {
namespace Sec {

class Key
{
public:
    Key(const std::string &base64Encoded);
    virtual ~Key();

public: // interface
    virtual operator XSECCryptoKey * () const = 0;

    const std::string & base64Encoded() const;

private: // member variables
    std::string     _base64Encoded;
};

} // namespace Util
} // namespace XML
} // namespace Sec

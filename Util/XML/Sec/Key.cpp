#include "stdafx.h"
#include "Key.h"
#include <xsec/enc/XSECCryptoKey.hpp>

using namespace Util::XML::Sec;

Key::Key(const std::string &base64Encoded)
    : _base64Encoded(base64Encoded)
{
}

Key::~Key()
{
}

// interface

const std::string & Key::base64Encoded() const
{
    return _base64Encoded;
}

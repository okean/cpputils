#pragma once

#include "XmlSecPlatform.h"

class DSIGSignature;

namespace Util {
namespace XML {

class XmlDoc;

namespace Sec { class Key; }
namespace Sec { class X509Cert; }

class XmlSignature : public XmlSecPlatform
{
public:
    XmlSignature();
    XmlSignature(const XmlDoc &xml);
    virtual ~XmlSignature();

public: // interface
    const std::string & error() const;

    bool validate(const Sec::Key &key);
    void sign(XmlDoc &xml, const Sec::Key &key);

private: // internal typedef 
    typedef DSIGSignature       *SignaturePtr;

private: // internal class helpers
    static SignaturePtr createSignature(
        ProviderImpl &provider);
    static SignaturePtr createSignatureFromDoc(
        ProviderImpl &provider,
        const XmlDoc &xml);

private: // member variables
    SignaturePtr _signature;
    std::string  _error;
};

typedef std::shared_ptr<XmlSignature>   XmlSignaturePtr;

} // namespace XML
} // namespace Util

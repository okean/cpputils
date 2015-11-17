#pragma once

#include "XmlPlatform.h"
#include <memory>

class XSECProvider;
class XSECException;

namespace Util {
namespace XML {

class XmlSecPlatform : public XmlPlatform
{
public:
    XmlSecPlatform();
    virtual ~XmlSecPlatform();

protected: // protected internal typedefs
    typedef XSECProvider                    ProviderImpl;
    typedef std::shared_ptr<ProviderImpl>   ProviderPtr;

protected: // protected interface
    ProviderImpl & provider() const;

protected: // protected class helpers
    static void rethrowWithMessage(
        XSECException &ex,
        const std::string &messaage);

private: // member variables
    ProviderPtr _provider;
};

} // namespace Xml
} // namespace Util

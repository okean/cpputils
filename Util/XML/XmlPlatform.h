#pragma once

#include <Util/NonCopyable.hpp>
#include <Util/XML/XmlDependencies.hpp>
#include <string>

XercescForwardDeclare(XMLException);

namespace Util {
namespace XML {

class XmlPlatform : public Util::NonCopyable
{
public:
    XmlPlatform();
    virtual ~XmlPlatform();

protected: // protected class helpers
    static void rethrowWithMessage(
        const Xercesc::XMLException &ex, 
        const std::string &messaage);
    static std::string messageFrom(
        const Xercesc::XMLException &ex);
};

} // namespace XML
} // namespace Util

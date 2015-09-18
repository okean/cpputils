#pragma once

#include <Util/XML/XmlDependencies.hpp>
#include <Util/NonCopyable.hpp>
#include <memory>

XercescForwardDeclare(DOMElement);

namespace Util {
namespace XML {

class XmlElement : public Util::NonCopyable
{
public:
    XmlElement(const Xercesc::DOMElement &domElement);
    virtual ~XmlElement();
};

typedef std::shared_ptr<XmlElement> XmlElementPtr;

} // namespace XML
} // namespace Util

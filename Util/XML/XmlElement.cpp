#include "stdafx.h"
#include "XercesString.h"
#include "XmlElement.h"
#include "XmlAttribute.h"
#include <xercesc/dom/DOMElement.hpp>

using namespace Util;
using namespace Util::XML;

XmlElement::XmlElement(Xercesc::DOMElement &elem)
    : NonCopyable{}
    , _impl(elem)
{
}

XmlElement::~XmlElement()
{
}

// interface

bool XmlElement::contains(const XmlAttribute & attr) const
{
    return _impl.hasAttribute(XercesString(attr.name()));
}

std::string XmlElement::get(const XmlAttribute & attr) const
{
    const std::string attributeName{ attr.name() };

    if (attributeName.empty())
    {
        return "";
    }

    if (!_impl.hasAttribute(XercesString(attributeName)))
    {
        return "";
    }

    return XercesString::convert(
        _impl.getAttribute(XercesString(attributeName)));
}

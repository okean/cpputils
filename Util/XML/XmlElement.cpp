#include "stdafx.h"
#include "XercesString.h"
#include "XmlElement.h"
#include "XmlAttribute.h"
#include "XmlNode.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>

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

std::string XmlElement::name() const
{
    return XercesString::convert(_impl.getNodeName());
}

XmlElementPtr XmlElement::get(const XmlNode &node) const
{
    XmlElementPtr element{};

    if (node.name().empty())
    {
        return element;
    }

    forEachNode([&](xercesc::DOMNode &child)
    {
        if (isElementNode(child))
        {
            const std::string name{
                XercesString::convert(child.getNodeName()) };

            if (node.name() == name)
            {
                element = std::make_shared<XmlElement>(
                    dynamic_cast<xercesc::DOMElement &>(child));

                return false; // stop looping
            }
        }
        return true;
    });

    return element;
};

std::string XmlElement::getText() const
{
    std::string text{};

    forEachNode([&](xercesc::DOMNode &child)
    {
        if (isTextNode(child))
        {
            text.append(XercesString::convert(child.getTextContent()));
        }

        return true; // return true to continue looping
    });

    return text;
}

// internal class helpers

bool XmlElement::isElementNode(const DomNodeImpl &node)
{
    return node.getNodeType() == xercesc::DOMNode::NodeType::ELEMENT_NODE;
}

bool XmlElement::isTextNode(const DomNodeImpl &node)
{
    return node.getNodeType() == xercesc::DOMNode::NodeType::TEXT_NODE;
}

// internal helpers

void XmlElement::forEachNode(
    std::function<bool(DomNodeImpl &)> onNode) const
{
    for (xercesc::DOMNode *child = _impl.getFirstChild()
        ; child != NULL
        ; child = (*child).getNextSibling())
    {
        if (!onNode(*child)) // return false to stop looping nodes
        {
            break;
        }
    }
}

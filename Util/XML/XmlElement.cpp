#include "stdafx.h"
#include "XercesString.h"
#include "XmlElement.h"
#include "XmlAttribute.h"
#include "XmlNode.h"
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <algorithm>
#include <cassert>

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

void XmlElement::set(const XmlAttribute &attr)
{
    XercesString name   { attr.name() };
    XercesString value  { attr.value() };

    _impl.setAttribute(name, value);
}

XmlElement::XmlAttributes XmlElement::attributes() const
{
    XmlAttributes attributes;

    if (xercesc::DOMNamedNodeMap* map = _impl.getAttributes())
    {
        size_t count = map->getLength();

        attributes.reserve(count);

        for (size_t i = 0; i < count; i++)
        {
            xercesc::DOMNode* node = map->item(i);

            const std::string name  { XercesString::convert(node->getNodeName()) };
            const std::string value { XercesString::convert(node->getNodeValue()) };

            attributes.push_back(
                std::make_shared<XmlAttribute>(name, value));
        }
    }

    return std::move(attributes);
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

XmlElementPtr XmlElement::find(const XmlNode &node, const size_t index) const
{
    size_t count = 0;

    XmlElementPtr element = find(node, index, count);

    assert(count <= index);

    return element;
}

XmlElementPtr XmlElement::add(const XmlNode &node)
{
    if (Xercesc::DOMNode* child = xmlDoc()->createElement(XercesString(node.name())))
    {
        _impl.appendChild(child);

        return std::make_shared<XmlElement>(
            dynamic_cast<xercesc::DOMElement &>(*child));
    }

    return XmlElementPtr{};
}

XmlElementPtr XmlElement::addCopy(const XmlElement &child)
{
    XmlElementPtr element{ add(XmlNode(child.name())) };

    if (element)
    {
        element->set(child.text());

        for (auto node : child.nodes())
        {
            element->addCopy(*node);
        }

        for (auto attribute : child.attributes())
        {
            element->set(*attribute);
        }
    }

    return element;
}

void XmlElement::add(const XmlElement &child)
{
    if (xmlDoc() == child.xmlDoc())
    {
        _impl.appendChild(child);
    }
}

std::string XmlElement::text() const
{
    std::string text{};

    forEachNode([&](xercesc::DOMNode &child)
    {
        if (isTextNode(child))
        {
            xercesc::DOMText & textNode =
                dynamic_cast<xercesc::DOMText &>(child);

            text.append(XercesString::convert(textNode.getNodeValue()));
        }

        return true; // return true to continue looping
    });

    return text;
}

XmlElementPtr XmlElement::set(const std::string &text)
{
    if (Xercesc::DOMText* child = xmlDoc()->createTextNode(XercesString(text)))
    {
        _impl.appendChild(child);

        return std::make_shared<XmlElement>(_impl);
    }

    return XmlElementPtr{};
}

XmlElements  XmlElement::nodes() const
{
    XMLSize_t count = _impl.getChildElementCount();

    XmlElements elements;
    elements.reserve(count);

    forEachNode([&](xercesc::DOMNode &child)
    {
        if (isElementNode(child))
        {
            elements.push_back(
                std::make_shared<XmlElement>(
                dynamic_cast<xercesc::DOMElement &>(child)));
        }

        return true; // return true to continue looping
    });

    return std::move(elements);
}

void XmlElement::remove(const XmlElement &elem)
{
    if (xercesc::DOMNode* child = _impl.removeChild(elem))
    {
        child->release();
    }
}

void XmlElement::clear()
{
    for (auto it : nodes())
    {
        remove(*it);
    }
}

std::string XmlElement::toString() const
{
    return XercesString::serialize(&_impl);
}

XmlElement::operator Xercesc::DOMNode * () const
{
    return &_impl;
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

XmlElement::DOMDocumentImpl * XmlElement::xmlDoc() const
{
    return _impl.getOwnerDocument();
}

XmlElementPtr XmlElement::find(const XmlNode &node, const size_t index, size_t &count) const
{
    XmlElementPtr found{};

    for (auto child : nodes())
    {
        if (found)
        {
            break;
        }

        if (child->name() == node.name())
        {
            if (index == count)
            {
                found = child;
            }
            else
            {
                count++;
            }
        }
        else
        {
            found = child->find(node, index, count);
        }
    }

    return found;
}

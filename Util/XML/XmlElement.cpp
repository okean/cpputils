#include "stdafx.h"
#include "XmlElement.h"
#include <xercesc/dom/DOMElement.hpp>

using namespace Util;
using namespace Util::XML;

XmlElement::XmlElement(const Xercesc::DOMElement &)
    : NonCopyable{}
{
}

XmlElement::~XmlElement()
{
}

#include "stdafx.h"
#include "XmlAttribute.h"

using namespace Util::XML;

XmlAttribute::XmlAttribute(const std::string &name)
    : _name(name)
{
}

XmlAttribute::~XmlAttribute()
{
}

// interface

const std::string & XmlAttribute::name() const
{
    return _name;
}

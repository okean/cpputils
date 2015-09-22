#include "stdafx.h"
#include "XmlAttribute.h"

using namespace Util::XML;

XmlAttribute::XmlAttribute(const std::string &name)
    : _name(name)
    , _value("")
{
}

XmlAttribute::XmlAttribute(
    const std::string &name, 
    const std::string &value)
    : _name(name)
    , _value(value)
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

const std::string & XmlAttribute::value() const
{
    return _value;
}

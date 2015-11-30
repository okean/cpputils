#include "stdafx.h"
#include "NameValuePair.h"
#include <Util/Text.h>

using namespace Util;

NameValuePair::NameValuePair(
    const std::string & name,
    const std::string & value)
    : _name(name)
    , _value(value)
{
}

NameValuePair::NameValuePair(
    const std::string &str,
    const char & separator,
    bool trim)
{
    split(_name, _value, str, separator, trim);
}

NameValuePair::~NameValuePair()
{
}

// interface

const std::string & NameValuePair::name() const
{
    return _name;
}

const std::string & NameValuePair::value() const
{
    return _value;
}

std::string NameValuePair::toString(const char & separator) const
{
    return _name + separator + _value;
}

// internal static helpers
void NameValuePair::split(
    std::string &name,
    std::string &value,
    const std::string &str,
    const char & separator,
    bool trim)
{
    std::string namevalue{ str };

    if (trim)
    {
        Text::trimInPlace(namevalue);
    }

    auto pos = namevalue.find(separator);

    if (pos != std::string::npos)
    {
        name    = namevalue.substr(0, pos);
        value   = namevalue.substr(pos + 1);
    }
    else
    {
        name    = namevalue;
        value.clear();
    }
}

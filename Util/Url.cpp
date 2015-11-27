#include "stdafx.h"
#include "Url.h"

using namespace Util;

Url::Url(const std::string &url)
    : _url(url)
{
}

Url::~Url()
{
}

// interface

Url::operator const std::string() const
{
    return _url;
}

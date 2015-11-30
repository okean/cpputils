#include "stdafx.h"
#include "Url.h"
#include <Util/Text.h>

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

Url & Url::append(const std::string &path)
{
    std::string localPath = path;

    Text::trimInPlace(localPath);

    if (!_url.empty())
    {
        beginWithForwardSlash(path) ?
        removeForwardSlashFromUrl() :
        appendForwardSlashToUrl();
    }
  
    _url.append(localPath);

    return *this;
}

// internal class helpers

bool Url::beginWithForwardSlash(const std::string &path)
{
    if (!path.empty())
    {
        return path.front() == '/';
    }

    return false;
}

// internal helpers

void Url::removeForwardSlashFromUrl()
{
    if (_url.back() == '/')
    {
        _url.pop_back();
    }
}

void Url::appendForwardSlashToUrl()
{
    if (_url.back() != '/')
    {
        _url.push_back('/');
    }
}

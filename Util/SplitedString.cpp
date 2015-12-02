#include "stdafx.h"
#include "SplitedString.h"
#include <Util/Text.h>
#include <cassert>

using namespace Util;

SplitedString::SplitedString(
    const std::string &str,
    char sep,
    bool trim,
    bool skipEmpty)
    : _tokens{ split(str, sep, 1, trim, skipEmpty) }
{
}

SplitedString::SplitedString(
    const std::string &str,
    const char * sep,
    bool trim,
    bool skipEmpty)
    : _tokens{ split(str, sep, strlen(sep), trim, skipEmpty) }
{
}

SplitedString::~SplitedString()
{
}

// interface

SplitedString::Iterator SplitedString::begin() const
{
    return _tokens->begin();
}

SplitedString::Iterator SplitedString::end() const
{
    return _tokens->end();
}

size_t SplitedString::count() const
{
    return _tokens->size();
}

std::string & SplitedString::at(size_t pos) const
{
    assert(pos < count());

    return _tokens->at(pos);
}

std::string & SplitedString::operator[](size_t pos) const
{
    return at(pos);
}

// internal static helpers

template <typename Separator>
SplitedString::TokensPtr SplitedString::split(
    const std::string &str,
    Separator s,
    size_t len,
    bool trim,
    bool skipEmpty)
{
    TokensPtr tokens{ std::make_shared<Tokens>() };

    for (size_t start = 0, end = 0; 
         start < str.size(); 
         start = end + len)
    {
        end = str.find(s, start);

        if (end == std::string::npos)
        {
            end = str.size();
        }

        Token token = str.substr(start, end - start);

        if (trim)
        {
            Text::trimInPlace(token);
        }

        if (!token.empty() || !skipEmpty)
        {
            tokens->push_back(token);
        }
    }

    return tokens;
}

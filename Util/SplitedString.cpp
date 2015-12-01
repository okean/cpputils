#include "stdafx.h"
#include "SplitedString.h"

using namespace Util;

SplitedString::SplitedString(
    const std::string &str,
    const char * separator,
    bool trim,
    bool skipEmpty)
    : _tokens{ split(str, separator, trim, skipEmpty) }
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

// internal static helpers

SplitedString::TokensPtr SplitedString::split(
    const std::string &str,
    const char * separator,
    bool trim,
    bool skipEmpty)
{
    TokensPtr tokens{ std::make_shared<Tokens>() };

    for (size_t start = 0, end = 0; 
         end < str.size(); 
         start = end + strlen(separator))
    {
        end = str.find(separator, start);

        if (end == std::string::npos)
        {
            end = str.size();
        }

        Token token = str.substr(start, end - start);

        tokens->push_back(token);
    }

    return tokens;
}

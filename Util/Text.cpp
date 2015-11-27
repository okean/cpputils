#include "stdafx.h"
#include "Text.h"
#include <cctype>

using namespace Util;

Text::Text()
{
}

Text::~Text()
{
}

// class interface

void Text::replaceAll(
    std::string &source, 
    const std::string &from, 
    const std::string &to)
{
    if (from.empty())
    {
        return;
    }

    std::string str;
    str.reserve(source.length());  // avoids a few memory allocations

    size_t lastPos = 0, findPos;

    while ((findPos = source.find(from, lastPos)) != std::string::npos)
    {
        str.append(source, lastPos, findPos - lastPos);
        str += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    str += source.substr(lastPos);

    source.swap(str);
}

void Text::trimInPlace(std::string &text)
{
    const std::string whitespace{ "\f\n\r\t\v " };

    if (!text.empty() && std::isspace(text.front()))
    {
        auto skip = text.find_first_not_of(whitespace);

        if (skip == std::string::npos)
        {
            text.clear();
        }

        text.erase(text.begin(), text.begin() + skip);
    }

    if (!text.empty() && std::isspace(text.back()))
    {
        auto skip = text.find_last_not_of(whitespace) + 1;

        text.erase(text.begin() + skip, text.end());
    }
}

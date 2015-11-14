#include "stdafx.h"
#include "Text.h"

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

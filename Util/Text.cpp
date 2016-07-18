#include "stdafx.h"
#include "Text.h"
#include <Windows.h>
#include <cctype>
#include <cassert>

using namespace Util;

Text::Text()
{
}

Text::~Text()
{
}

// struct Convert

std::wstring Text::Convert::wcsFromUtf(const std::string &str)
{
    if (str.empty())
    {
        return std::wstring{};
    }

    int size = ::MultiByteToWideChar(
        CP_UTF8, 0,
        &str[0], str.size(),
        nullptr, 0);

    assert(size);

    std::wstring out(size, 0);

    if (size)
    {
        size = ::MultiByteToWideChar(
            CP_UTF8, 0,
            &str[0], str.size(),
            &out[0], out.size());

        assert(size);
    }

    return std::move(out);
}

std::string Text::Convert::utfFromWcs(const std::wstring &str)
{
    if (str.empty())
    {
        return std::string{};
    }

    int size = ::WideCharToMultiByte(
        CP_UTF8, 0,
        &str[0], str.size(),
        nullptr, 0,
        nullptr, nullptr);

    assert(size);

    std::string out(size, 0);

    if (size)
    {
        size = ::WideCharToMultiByte(
            CP_UTF8, 0,
            &str[0], str.size(),
            &out[0], out.size(),
            nullptr, nullptr);

        assert(size);
    }

    return std::move(out);
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
            return;
        }

        text.erase(text.begin(), text.begin() + skip);
    }

    if (!text.empty() && std::isspace(text.back()))
    {
        auto skip = text.find_last_not_of(whitespace) + 1;

        text.erase(text.begin() + skip, text.end());
    }
}

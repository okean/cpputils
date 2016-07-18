#include "stdafx.h"
#include <Util/Text.h>

using namespace Util;

TEST(Text, ConvertWcsFromUtf)
{
    std::wstring wcs{ L"qwertyéöóêå12345" };

    std::string  utf{ Text::Convert::utfFromWcs(wcs) };

    ASSERT_FALSE(utf.empty());

    std::wstring actual{ Text::Convert::wcsFromUtf(utf) };

    EXPECT_EQ(actual, wcs);
}

TEST(Text, ReplaceAll)
{
    std::string actual      { "text replace text all text" };
    std::string expected    { "test replace test all test" };

    Text::replaceAll(actual, "text", "test");

    EXPECT_EQ(expected, actual);
}

TEST(Text, TrimInPlace)
{
    std::string str{ "    \f\n\r\t\vstring to trim    \f\n\r\t\v" };

    Text::trimInPlace(str);

    EXPECT_EQ("string to trim", str);
}

TEST(Text, WhiteSpaceText)
{
    std::string str{ "    \f\n\r\t\v" };

    Text::trimInPlace(str);

    EXPECT_EQ("", str);
}

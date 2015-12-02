#include "stdafx.h"
#include <Util/Text.h>

using namespace Util;

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

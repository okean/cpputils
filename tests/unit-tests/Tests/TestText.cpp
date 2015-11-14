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

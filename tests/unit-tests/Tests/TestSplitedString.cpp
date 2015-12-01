#include "stdafx.h"
#include <Util/SplitedString.h>

using namespace Util;

TEST(SplitedString, Sanity)
{
    SplitedString splitedString("str1;str2;str3", ";");

    ASSERT_EQ(3, splitedString.count());

    size_t count = 0;
    const std::string expected[] {"str1", "str2", "str3"};

    for (auto str : splitedString)
    {
        EXPECT_EQ(expected[count], str);
        count++;
    }
}

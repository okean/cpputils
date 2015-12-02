#include "stdafx.h"
#include <Util/SplitedString.h>

using namespace Util;

namespace
{
    typedef std::vector<std::string>    Tokens;

    void test(const SplitedString &line, const Tokens &tokens)
    {
        ASSERT_EQ(tokens.size(), line.count());

        size_t count = 0;

        for (auto str : line)
        {
            EXPECT_EQ(tokens[count++], str);
        }
    }
}

TEST(SplitedString, Sanity)
{
    const SplitedString line    { "str1; str2; str3", ';' };
    const Tokens        tokens  { "str1", "str2", "str3" };

    test(line, tokens);
}

TEST(SplitedString, NoTrim)
{
    const SplitedString line    { "str1; str2; str3", ';', false };
    const Tokens        tokens  { "str1", " str2", " str3" };

    test(line, tokens);
}

TEST(SplitedString, EmptyToken)
{
    const SplitedString line0   { "", ';' };
    const Tokens        tokens0 {};

    test(line0, tokens0);

    const SplitedString line1   { "str1;;str3", ';' };
    const Tokens        tokens1 { "str1", "str3" };
    
    test(line1, tokens1);

    const SplitedString line2   { "str1; ; str3", ';' };
    const Tokens        tokens2 { "str1", "str3" };
    
    test(line2, tokens2);

    const SplitedString line3   { "str1;; str3", ';', false };
    const Tokens        tokens3 { "str1", " str3" };

    test(line3, tokens3);

    const SplitedString line4   { "str1; ; str3", ';', false };
    const Tokens        tokens4 { "str1", " ", " str3" };

    test(line4, tokens4);
}

TEST(SplitedString, StringSeparator)
{
    const SplitedString line    { "str1::str2::str3::", "::" };
    const Tokens        tokens  { "str1", "str2", "str3" };

    test(line, tokens);
}

TEST(SplitedString, ElementSelectionOperator)
{
    const SplitedString line{ "str0; str1; str2", ';' };

    EXPECT_EQ("str0", line[0]);
    EXPECT_EQ("str2", line[2]);

    EXPECT_DEATH(line[-1], "Assertion failed: pos < count");
    EXPECT_DEATH(line[3] , "Assertion failed: pos < count");
}

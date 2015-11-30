#include "stdafx.h"
#include <Util/NameValuePair.h>

using namespace Util;

TEST(NameValuePair, NameValue)
{
    NameValuePair pair("name", "value");

    EXPECT_EQ("name"    , pair.name());
    EXPECT_EQ("value"   , pair.value());
}

TEST(NameValuePair, Separator)
{
    NameValuePair pair1("name1=value1", '=');

    EXPECT_EQ("name1", pair1.name());
    EXPECT_EQ("value1", pair1.value());

    NameValuePair pair2("    name2=value2    ", '=', true);

    EXPECT_EQ("name2", pair2.name());
    EXPECT_EQ("value2", pair2.value());

}

TEST(NameValuePair, ToString)
{
    NameValuePair pair("name", "value");

    EXPECT_EQ("name=value", pair.toString());
    EXPECT_EQ("name:value", pair.toString(':'));
}

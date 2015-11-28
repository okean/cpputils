#include "stdafx.h"
#include <Util/Url.h>

using namespace Util;

TEST(Url, Initialization)
{
    const std::string example{ "http://example.com/" };

    const Url url(example);
    const std::string exampleUrl = url;

    EXPECT_EQ(example, exampleUrl);
}

TEST(Url, Append)
{
    Url url1{ "http://example.com/" };
    url1.append("test");
    EXPECT_EQ("http://example.com/test", static_cast<std::string>(url1));

    Url url2{ "http://example.com/" };
    url2.append("/test");
    EXPECT_EQ("http://example.com/test", static_cast<std::string>(url2));

    Url url3{ "http://example.com" };
    url3.append("test");
    EXPECT_EQ("http://example.com/test", static_cast<std::string>(url3));

    Url url4{ "http://example.com" };
    url4.append("/test");
    EXPECT_EQ("http://example.com/test", static_cast<std::string>(url4));

    Url url5{ "http://example.com/" };
    url5.append("    test    ");
    EXPECT_EQ("http://example.com/test", static_cast<std::string>(url5));

    Url url6{ "" };
    url6.append("test");
    EXPECT_EQ("test", static_cast<std::string>(url6));
}

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

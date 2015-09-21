#include "stdafx.h"
#include <Util/XML/Xml.hpp>

using namespace Util::XML;

namespace { XmlDocPtr       xml;  }
namespace { XmlElementPtr   root; }

TEST(Xml, CreateXmlDoc)
{
    std::stringstream content; 
    
    content << "<?xml version=\"1.0\"?>"
            << "<catalog id = \"ctg01\">"
            << "<book id = \"bk101\">"
            << "<author>Gambardella, Matthew</author>"
            << "<title>XML Developer's Guide</title>"
            << "</book>"
            << "</catalog>";
    
    ASSERT_NO_THROW(
        xml     = std::make_shared<XmlDoc>(content.str());
        root    = xml->root();
    );
}

TEST(Xml, GetRootElement)
{
    ASSERT_NE(nullptr, root);

    EXPECT_TRUE(root->contains(XmlAttribute("id")));
    EXPECT_FALSE(root->contains(XmlAttribute("foobar")));

    EXPECT_EQ("ctg01", root->get(XmlAttribute("id")));

    EXPECT_EQ("catalog", root->name());
}

namespace { XmlElementPtr child; }

TEST(Xml, GetChildElement)
{
    ASSERT_NE(nullptr, root);

    child = root->get(XmlNode("book"));
    XmlElementPtr missingChild = root->get(XmlNode("note"));

    ASSERT_NE(nullptr, child);
    ASSERT_EQ(nullptr, missingChild);

    EXPECT_TRUE(child->contains(XmlAttribute("id")));
    EXPECT_EQ("bk101", child->get(XmlAttribute("id")));
}

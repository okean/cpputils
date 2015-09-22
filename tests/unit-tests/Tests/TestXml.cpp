#include "stdafx.h"
#include <Util/XML/Xml.hpp>

using namespace Util::XML;

namespace { XmlDocPtr       xml;  }
namespace { XmlElementPtr   catalog; }

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
        catalog    = xml->root();
    );
}

TEST(Xml, GetRootElement)
{
    ASSERT_NE(nullptr, catalog);

    EXPECT_TRUE(catalog->contains(XmlAttribute("id")));
    EXPECT_FALSE(catalog->contains(XmlAttribute("foobar")));

    EXPECT_EQ("ctg01", catalog->get(XmlAttribute("id")));

    EXPECT_EQ("catalog", catalog->name());
}

namespace { XmlElementPtr book; }

TEST(Xml, GetChildElement)
{
    ASSERT_NE(nullptr, catalog);

    book = catalog->get(XmlNode("book"));
    XmlElementPtr element = catalog->get(XmlNode("note"));

    ASSERT_NE(nullptr, book);
    ASSERT_EQ(nullptr, element);

    EXPECT_TRUE(book->contains(XmlAttribute("id")));
    EXPECT_EQ("bk101", book->get(XmlAttribute("id")));
}

namespace { XmlElementPtr title; }

TEST(Xml, GetElementText)
{
    ASSERT_NE(nullptr, book);

    title = book->get(XmlNode("title"));

    ASSERT_NE(nullptr, title);
    
    EXPECT_EQ("XML Developer's Guide", title->text());
}

TEST(Xml, GetAllChilds)
{
    ASSERT_NE(nullptr, book);

    ASSERT_EQ(2, book->nodes()->size());
}

TEST(Xml, SetChildAttributes)
{
    ASSERT_NE(nullptr, book);

    const std::string attrName  { "ISBN" };
    const std::string attrValue { "978-0-553-27450-9" };

    book->set(XmlAttribute(attrName, attrValue));

    EXPECT_TRUE(book->contains(XmlAttribute(attrName)));
    EXPECT_EQ(attrValue, book->get(XmlAttribute(attrName)));

    const std::string newAttrValue{ "5-89815-410-8" };

    book->set(XmlAttribute(attrName, newAttrValue));

    EXPECT_EQ(newAttrValue, book->get(XmlAttribute(attrName)));
}

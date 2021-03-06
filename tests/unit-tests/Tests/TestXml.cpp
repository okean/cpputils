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

    ASSERT_EQ(2, book->nodes().size());
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

TEST(Xml, RemoveChilds)
{
    ASSERT_NE(nullptr, book);

    book->clear();

    EXPECT_EQ(0, book->nodes().size());

    catalog->clear();

    EXPECT_EQ(0, catalog->nodes().size());
}

namespace { XmlElementPtr   root; }

TEST(Xml, CreateEmptyDoc)
{
    ASSERT_NO_THROW(
        title.reset();
        book.reset();
        catalog.reset();
        xml.reset());

    ASSERT_NO_THROW(
        xml = std::make_shared<XmlDoc>("<object>");;
        root = xml->root();
    );

    ASSERT_NE(nullptr, root);

    EXPECT_EQ("object", root->name());
}

namespace { XmlElementPtr child1; }

TEST(Xml, AddChild)
{
    ASSERT_NE(nullptr, root);

    const std::string name1{ "child1" };

    child1 = root->add(XmlNode(name1));

    EXPECT_EQ(name1, child1->name());

    const std::string attr1{ "attr1" };
    const std::string val1{ "val1" };

    child1->set(XmlAttribute(attr1, val1));

    EXPECT_TRUE(child1->contains(XmlAttribute(attr1)));
    EXPECT_EQ(val1, child1->get(XmlAttribute(attr1)));

    const std::string text{ "text" };

    child1->set(text);

    EXPECT_EQ(text, child1->text());
    EXPECT_EQ(0, child1->nodes().size());
    child1->add(XmlNode("c1"));
    child1->add(XmlNode("c2"));
    EXPECT_EQ(2, child1->nodes().size());

    EXPECT_EQ(1, root->nodes().size());

    const std::string name2{ "child2" };

    XmlElementPtr child2 = root->add(XmlNode(name2));

    EXPECT_EQ(2, root->nodes().size());
}

TEST(Xml, Attributes)
{
    ASSERT_NE(nullptr, child1);

    EXPECT_EQ(1, child1->attributes().size());

    const std::string attr2{ "attr2" };
    const std::string val2{ "val2" };

    child1->set(XmlAttribute(attr2, val2));

    EXPECT_EQ(2, child1->attributes().size());
}

TEST(Xml, AddXmlElement)
{
    std::stringstream content;

    content << "<?xml version=\"1.0\"?>"
            << "<element id = \"obj01\">"
            << "<child1>value1</child1>"
            << "<child2>value2</child2>"
            << "<child10>value10</child10>"
            << "<child10>value-idx</child10>"
            << "</element>";

    XmlDocPtr xmldoc        { std::make_shared<XmlDoc>(content.str()) };
    XmlElementPtr element   { xmldoc->root() };

    XmlElementPtr elementCopy;

    ASSERT_NO_THROW(elementCopy  = root->addCopy(*element));
    EXPECT_EQ(3, root->nodes().size());
    
    XmlElementPtr child2{ elementCopy->get(XmlNode("child2")) };
    ASSERT_NE(nullptr, child2);
    EXPECT_EQ("value2", child2->text());

    ASSERT_NO_THROW(root->add(*element));
    EXPECT_EQ(3, root->nodes().size());

    XmlElementPtr child3 = child1->add(XmlNode("child3"));

    ASSERT_NO_THROW(root->add(*child3));
    EXPECT_EQ(4, root->nodes().size());
}

TEST(Xml, Find)
{
    ASSERT_NE(nullptr, root);

    XmlElementPtr child10{ root->find(XmlNode("child10")) };
    ASSERT_NE(nullptr, child10);
    EXPECT_EQ("value10", child10->text());

    XmlElementPtr child10Idx{ root->find(XmlNode("child10"), 1) };
    ASSERT_NE(nullptr, child10Idx);
    EXPECT_EQ("value-idx", child10Idx->text());

    child10->add(XmlNode("child10_1"));

    XmlElementPtr child10_1{ root->find(XmlNode("child10_1")) };
    EXPECT_NE(nullptr, child10_1);
}

TEST(Xml, Serialize)
{
    EXPECT_FALSE(root->toString().empty());
    EXPECT_FALSE(xml->toString().empty());
}

TEST(Xml, Dispose)
{
    child1.reset();
    root.reset();
    xml.reset();
}

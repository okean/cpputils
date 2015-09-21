#include "stdafx.h"
#include "XmlNode.h"

using namespace Util::XML;

XmlNode::XmlNode(const std::string &name)
    : _name(name)
{
}

XmlNode::~XmlNode()
{
}

// interface

const std::string & XmlNode::name() const
{
    return _name;
}

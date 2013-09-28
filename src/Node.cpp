#include "Node.h"

    Node::Node(string id)
    {
        this->id = id;
    }
    
    Node::~Node()
    {

    }

void Node::setId(string id)
{
    this->id = id;
}

string Node::getId()
{
    return this->id;
}

void Node::setAppearanceRef(string appearanceref)
{
    this->appearanceref = appearanceref;
}

string Node::getAppearanceRef()
{
    return this->appearanceref;
}

void Node::setTransforms(vector<Transform*> transforms)
{
    this->transforms = transforms;
}

vector<Transform*> Node::getTransforms()
{
    return this->transforms;
}

void Node::setChildrenNodeRef(vector<string> childrenNodeRef)
{
    this->childrenNodeRef = childrenNodeRef;
}

vector<string> Node::getChildrenNodeRef()
{
    return this->childrenNodeRef;
}


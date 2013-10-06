#include "Node.h"

Node::Node()
{
    
}

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

void Node::setChildrenNodeRef(vector<string> childrenNodeRef)
{
    this->childrenNodeRef = childrenNodeRef;
}

vector<string> Node::getChildrenNodeRef()
{
    return this->childrenNodeRef;
}

void Node::setPrimitives(vector<scene::Primitive*> primitives)
{
    this->primitives = primitives;
}

vector<scene::Primitive*> Node::getPrimitives()
{
    return this->primitives;
}

void Node::setMatrix(float* matrix)
{
    //memcpy(this->matrix, matrix,16*sizeof(float));
    for(unsigned int i = 0; i < 16; i++)
    {
        this->matrix[i] = matrix[i];
    }
}

float* Node::getMatrix()
{
    return this->matrix;
}


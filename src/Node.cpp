#include "Node.h"

Node::Node()
{
    
}

Node::Node(string id,bool display_list){
    this->use_list = display_list;
    this->id=id;
    this->the_object = 0x0;
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

void Node::setAnimationRef(string animationref)
{
    this->animationref = animationref;
}

string Node::getAppearanceRef()
{
    return this->appearanceref;
}
string Node::getAnimationRef()
{
    return this->animationref;
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
    memcpy(this->matrix, matrix,16*sizeof(float));
}

float* Node::getMatrix()
{
    return this->matrix;
}


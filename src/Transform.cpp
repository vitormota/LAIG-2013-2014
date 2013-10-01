//
//  Transform.cpp
//  LAIG - P1
//

#include "Transform.h"

Transform::Transform(string type)
{
    
}

Transform::~Transform()
{
    
}

Translate::Translate(float x, float y, float z): Transform(type)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Rotate::Rotate(string axis, float angle): Transform(type)
{
    this->axis = axis;
    this->angle = angle;
}

Scale::Scale(float x, float y, float z): Transform(type)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

string Translate::getType()
{
    return this->type;
}

string Rotate::getType()
{
    return this->type;
}

string Scale::getType()
{
    return this->type;
}
//
//  Transform.cpp
//  LAIG - P1
//

#include "Transform.h"

Transform::Transform()
{
    
}

Transform::~Transform()
{
    
}

Translate::Translate(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->type = "translate";
}

Rotate::Rotate(string axis, float angle)
{
    this->axis = axis;
    this->angle = angle;
    this->type = "transform";
}

Scale::Scale(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->type = "scale";
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
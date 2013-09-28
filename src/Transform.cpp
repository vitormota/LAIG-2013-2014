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
}

Rotate::Rotate(string axis, float angle)
{
    this->axis = axis;
    this->angle = angle;
}

Scale::Scale(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Translate::getMatrix()
{
    // TODO
}

void Rotate::getMatrix()
{
    // TODO
}

void Scale::getMatrix()
{
    // TODO
}
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
    
    if(axis == "x")
    {
        /*rotateMatrixX =
         {1.0, 0.0,        0.0,        0.0,
         0.0, cos(angle),-sin(angle), 0.0,
         0.0, sin(angle), cos(angle), 0.0,
         0.0, 0.0,         0.0,       1.0};
         }
         elseb
         if(axis == "y")
         {
         float rotateMatrixY =
         {cos(angle), 0.0, sin(angle), 0.0,
         0.0,        1.0, 0.0,        0.0,
         -sin(angle), 0.0, cos(angle), 0.0,
         0.0,        0.0,        0.0, 1.0};
         }
         else
         if(axis == "z")
         {
         float rotateMatrixZ[4][4] =
         {cos(angle),-sin(angle), 0.0, 0.0,
         sin(angle), cos(angle), 0.0, 0.0,
         0.0,        0.0,        1.0, 0.0,
         0.0,        0.0,        0.0, 1.0};
         }*/
    }
}

void Scale::getMatrix()
{
    
}
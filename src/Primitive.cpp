//
//  Primitive.cpp
//  LAIG - P1
//
//  Created by Maria Araújo on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Primitive.h"

Primitive::Primitive(string id)
{
    this->id = id;
    
}

Primitive::~Primitive()
{

}

void Primitive::setId(string id)
{
    this->id = id;
}

string Primitive::getId()
{
    return this->id;
}

Rectangle::Rectangle(string id,float xy1,float xy2) : Primitive(id)
{
    this->xy1 = xy1;
    this->xy2 = xy2;
}

Triangle::Triangle(string id, float xyz1,float xyz2,float xyz3) : Primitive(id)
{
    this->xyz1 = xyz1;
    this->xyz2 = xyz2;
    this->xyz3 = xyz3;
}

Cylinder::Cylinder(string id, float base, float top, float height, int slices, int stacks) : Primitive(id)
{
    this->base = base;
    this->top = top;
    this->height = height;
    this->slices = slices;
    this->stacks = stacks;
}

Sphere::Sphere(string id, float radius, int slices, int stacks) : Primitive(id)
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
}

Torus::Torus(string id, float inner, float outer, int slices, int loops) : Primitive(id)
{
    this->inner = inner;
    this->outer = outer;
    this->slices = slices;
    this->loops = loops;
}

void Rectangle::draw()
{
    
}

void Triangle::draw()
{
    
}

void Cylinder::draw()
{
    
}

void Sphere::draw()
{
    
}

void Torus::draw()
{
    
}


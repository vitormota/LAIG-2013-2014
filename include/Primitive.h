#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

#include <string>
using std::string;

class Primitive
{
private:
    string id;
    
public:
    Primitive(string id);
    ~Primitive();
    void setId(string id);
    string getId();
    virtual void draw(){}
    
};

// RECTANGLE
class Rectangle: public Primitive{

private:
    float xy1, xy2;
    
public:
    Rectangle(string id,float xy1,float xy2);
    virtual void draw();
};

// TRIANGLE
class Triangle: public Primitive{
    
private:
    float xyz1, xyz2, xyz3;
    
public:
    Triangle(string id, float xyz1, float xyz2, float xyz3);
    virtual void draw();
};

// CYLINDER
class Cylinder: public Primitive{
    
private:
    float base, top, height;
    int slices, stacks;
    
public:
    Cylinder(string id, float base, float top, float height, int slices, int stacks);
    virtual void draw();
};

// SPHERE
class Sphere: public Primitive{
    
private:
    float radius;
    int slices, stacks;
    
public:
    Sphere(string id, float radius, int slices, int stacks);
    virtual void draw();
};

// TORUS
class Torus: public Primitive{
    
private:
    float inner, outer;
    int slices, loops;
    
public:
    Torus(string id, float inner, float outer, int slices, int loops);
    virtual void draw();
};



#endif
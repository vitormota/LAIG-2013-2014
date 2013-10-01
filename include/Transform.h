//
//  Transform.h
//  LAIG - P1
//

#ifndef __LAIG___P1__Transform__
#define __LAIG___P1__Transform__

#include <iostream>
#include <string>
#include <math.h>
using std::string;

class Transform{
    
private:
    string type;
    
public:
    Transform(string type);
    ~Transform();
    virtual string getType(){ return this->type; }
    
};

// TRANSLATE
class Translate: public Transform {
    
private:
    float x, y, z; // to attribute
    const string type = "transform";
    
public:
    Translate(float x, float y, float z);
    virtual string getType();
};

// ROTATE
class Rotate: public Transform{
    
private:
    string axis;
    float angle;
    const string type = "rotate";
    
public:
    Rotate(string axis, float angle);
    virtual string getType();
    
};

// SCALE
class Scale: public Transform{
    
private:
    float x, y, z; // factor attribute
    const string type = "scale";
    
public:
    Scale(float x, float y, float z);
    virtual string getType();
};

#endif /* defined(__LAIG___P1__Transform__) */

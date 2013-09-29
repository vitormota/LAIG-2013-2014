//
//  Transform.h
//  LAIG - P1
//
//  Created by Maria Araújo on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __LAIG___P1__Transform__
#define __LAIG___P1__Transform__

#include <iostream>
#include <string>
#include <math.h>
using std::string;

class Transform{
    
private:
    
public:
    Transform();
    ~Transform();
    // TODO : Falta matrix da transformacao e criar com herança as classes translate, rotate e scale
    virtual void getMatrix(){}
    
};

// TRANSLATE
class Translate: public Transform{
    
private:
    float x, y, z; // to attribute
//    float translateMatrix[4][4] = {1.0, 0.0, 0.0, x,
//                                   0.0, 1.0, 0.0, y,
//                                   0.0, 0.0, 1.0, z,
//                                   0.0, 0.0, 0.0, 1.0};
    
public:
    Translate(float x, float y, float z);
    virtual void getMatrix();
};

// ROTATE
class Rotate: public Transform{
    
private:
    string axis;
    float angle;
    
    float rotateMatrixX[4][4];
    
    float rotateMatrixY[4][4];
    
    float rotateMatrixZ[4][4];
    
public:
    Rotate(string axis, float angle);
    virtual void getMatrix();
    
};

// SCALE
class Scale: public Transform{
    
private:
    float x, y, z; // factor attribute
//    float scaleMatrix[4][4] =
//      {   x, 0.0, 0.0, 0.0,
//        0.0,   y, 0.0, 0.0,
//        0.0, 0.0,   z, 0.0,
//        0.0, 0.0, 0.0, 0.0};
    
public:
    Scale(float x, float y, float z);
    virtual void getMatrix();
};

#endif /* defined(__LAIG___P1__Transform__) */

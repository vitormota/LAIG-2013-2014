//
//  Animation.h
//  LAIG - P2
//
//  Created by Maria Araújo on 07/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __LAIG___P2__Animation__
#define __LAIG___P2__Animation__

#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Animation
{
private:
    string id; // id of the primitive to animate
    string type;
    vector<vector<float>> controlPoints; // control points
    vector<vector<vector<float>>> controlPointsPairs; // control points pairs
    
public:
    Animation(string id, float span, string type);
    ~Animation();
    void setSpan(float span);
    float getSpan();
    void setControlPoints(vector<vector<float>> controlPoints);
    vector<vector<float>> getControlPoints();
    void init();
    void rotateObject();
    
    float span; // total time span (in seconds) of the animation
};

/* Linear Animation - Movement between a pair of control points */
class LinearAnimation: public Animation{
    
private:
    vector<vector<float>> controlPointsPair; // pair of control points
    double dx, dy, dz; // calculated small displacements between the pair of control points
    double total_displacement; // total displacement between the pair of control points
    
public:
    LinearAnimation(string id, float span, string type, vector<vector<float>> controlPointsPair);
    ~LinearAnimation();
    void setControlPointsPair(vector<vector<float>> controlPointsPair);
    vector<vector<float>> getControlPointsPair();
    void calculateDisplacements();
    void updatePrimitivePos();
};

#endif

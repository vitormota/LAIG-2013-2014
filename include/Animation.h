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
    string id;
    
public:
    Animation(string id);
    ~Animation();
};

/* Linear Animation */
class LinearAnimation: public Animation{
    
private:
    float span;
    string type;
    vector<float*> controlPoints;
    
public:
    LinearAnimation(string id, float span, string type, vector<float*> controlPoints);
    ~LinearAnimation();
};

#endif

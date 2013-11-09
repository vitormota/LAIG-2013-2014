//
//  Animation.cpp
//  LAIG - P2
//
//  Created by Maria Araújo on 07/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Animation.h"
#include "Scene.h"
#include "math.h"

/* Animation */

Animation::Animation(string id, float span, string type)
{
    this->id = id;
}

Animation::~Animation()
{
}

void Animation::setSpan(float span)
{
    this->span = span;
}

float Animation::getSpan()
{
    return this->span;
}

void Animation::init(){
    
    
    vector<float*> controlPointsPair = vector<float*>();
    for(unsigned int i = 0; i <= this->controlPoints.size(); i++){
        
        controlPointsPair[0] = this->controlPoints[i];
        controlPointsPair[1] = this->controlPoints[i+1];
        
        this->controlPointsPairs.push_back(controlPointsPair);
    }

    
     LinearAnimation* newLinearAnimation = new LinearAnimation(this->id, this->span, "linear", controlPointsPair);
  //TODO
    
}



void Animation::rotateObject(){
    
// TODO
    
}

/* Linear Animation */

LinearAnimation::LinearAnimation(string id, float span, string type, vector<float*> controlPointsPair): Animation(id, span, type)
{
    this->controlPointsPair = controlPointsPair;
    this->dx = 0;
    this->dy = 0;
    this->dz = 0;
    this->total_displacement = 0;
    calculateDisplacements();
    
}

LinearAnimation::~LinearAnimation()
{
}

void LinearAnimation::setControlPointsPair(vector<float*> controlPointsPair)
{
    this->controlPointsPair = controlPointsPair;
}

vector<float*> LinearAnimation::getControlPointsPair()
{
    return this->controlPointsPair;
}

void LinearAnimation::calculateDisplacements(){
    
    float* beginCP = this->controlPointsPair[0];
    float* endCP = this->controlPointsPair[1];
    
    float beginCP_xx = beginCP[0];
    float beginCP_yy = beginCP[1];
    float beginCP_zz = beginCP[2];
    
    float endCP_xx = endCP[0];
    float endCP_yy = endCP[1];
    float endCP_zz = endCP[2];
    
    double total_dx = endCP_xx - beginCP_xx;
    double total_dy = endCP_yy - beginCP_yy;
    double total_dz = endCP_zz - beginCP_zz;
    
    double total_dx_pow = (double) powl(total_dx, 2.0);
    double total_dy_pow = (double) powl(total_dy, 2.0);
    double total_dz_pow = (double) powl(total_dz, 2.0);
    
    this->total_displacement = (double) sqrtl(total_dx_pow + total_dy_pow + total_dz_pow);
    
    // the span is in seconds -> convert to milliseconds
    this->dx = (100/(this->span*1000)) * total_dx;
    this->dy = (100/(this->span*1000)) * total_dy;
    this->dz = (100/(this->span*1000)) * total_dz;
}



void LinearAnimation::updatePrimitivePos(){
    
    glTranslated(this->dx, this->dy, this->dz);
    
}

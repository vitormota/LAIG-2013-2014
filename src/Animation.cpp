//
//  Animation.cpp
//  LAIG - P2
//
//  Created by Maria Araújo on 07/11/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Animation.h"

/*
void Animation::initAnimation()
{
	delta_rotate = (double) mili_secs/1000.0 * ANGULAR_SPEED *360.0;
	delta_radius = (double) mili_secs/1000.0 * RADIUS_SPEED;
}

void Animation::updateAnimation(int dummy)
{
 
	glutTimerFunc(this->span, updateAnimation, 0);
}

void Animation::applyAnimation()
{
	//glRotated(obj_rotate, 0,1,0);
	glTranslated(obj_radius,0.0,0.0);
}*/

Animation::Animation(string id)
{
    this->id = id;
}

Animation::~Animation()
{
}

LinearAnimation::LinearAnimation(string id, float span, string type, vector<float*> controlPoints): Animation(id)
{
    this->span = span;
    this->type = type;
    this->controlPoints = controlPoints;
}


LinearAnimation::~LinearAnimation()
{
}
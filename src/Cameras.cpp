#include "Cameras.h"

namespace scene{

	Camera::~Camera(){}
	
	Perspective::Perspective(string id,bool enabled,float near,float far,float angle,float pos[3],float target[3])
		:Camera(id,enabled,near,far),
		pos(pos),target(target){}

	Perspective::~Perspective(){
		delete [] &pos,&target;
	}

	Ortho::Ortho(string id,bool enabled,float near,float far,float left,float right,float top,float bottom)
		:Camera(id,enabled,near,far),
		left(left),right(right),top(top),bottom(bottom){}

	Ortho::~Ortho(){}

}//scene
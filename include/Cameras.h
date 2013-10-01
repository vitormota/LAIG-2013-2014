#ifndef _CAMERAS_H
#define _CAMERAS_H

#include <string>
#if __APPLE__
#include <CGFcamera.h>
#elif __unix
#include <CGF/CGFcamera.h>
#elif _WIN32
#include "CGFcamera.h"
#endif

namespace scene{

	using namespace std;

	typedef struct{
		string initial_id;
	} global_cameras_vars;

	class Camera:public CGFcamera{
	public:
		Camera(string id,bool enabled,float near,float far)
			:CGFcamera(),id(id),enabled(enabled),near(near),far(far){}
		virtual ~Camera();

		string getId()const {return id;}
		bool isEnabled()const {return enabled;}
		
		//pure virtual makes class abstract
		virtual float getVars()const =0;
	protected:
		string id;
		bool enabled;
		float near,far;
	};

	class Perspective:public Camera{
	public:
		Perspective(string id,bool enabled,float near,float far,float angle,float pos[3],float target[3]);
		~Perspective();

		
	protected:
		float angle,
			*pos,
			*target;
	};

	class Ortho:public Camera{
	public:
		Ortho(string id,bool enabled,float near,float far,float left,float right,float top,float bottom);
		~Ortho();

	protected:
		float left,
			right,
			top,
			bottom;
	};

}//scene

#endif
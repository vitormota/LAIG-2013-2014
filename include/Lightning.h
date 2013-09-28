#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include <string>
#ifdef __APPLE__
#include "CGFlight.h"
#else
#include <CGFlight.h>
#endif


	using namespace std;

<<<<<<< HEAD
	class Lightning/*:public CGFlight*/{
        
    public:
        Lightning();
        ~Lightning();
=======
	typedef struct{
		bool doublesided;
		bool local;
		bool enabled;
		float ambient[4];
	} global_lightning_vars;

	class Light:public CGFlight{
	public:
		Light(string id,bool enabled,unsigned int light_id,
			float *pos,float location[4],float ambient[4],
			float difuse[4],float specular[4],float *dir=NULL);
		virtual ~Light();
>>>>>>> b025d1450191b30cdd6a03f0487632930308d71e

		string getId()const {return id;}
		bool isEnabled()const {return enabled;}

		//pure virtual makes class abstract
		virtual float getVars()const =0;
	protected:
		string id;
		bool enabled;
		float
			*location,
			*ambient,
			*difuse,
			*specular;
	};

	class Omni:public Lightning{
	public:
		Omni(string id,bool enabled,unsigned int light_id,
			float *pos,float location[4],float ambient[4],
			float difuse[4],float specular[4],float *dir=NULL);
		~Omni();

		
	private:
		
	};

	class Spot:public Lightning{
	public:
<<<<<<< HEAD
		Spot(string id, bool enabled, float *location, float *ambient,float *difuse, float *specular, float angle, float exponent,float *direction);
=======
		Spot(string id,bool enabled,unsigned int light_id,
			float *pos,float location[4],float ambient[4],
			float difuse[4],float specular[4],float angle,
			float exponent, float direction[3],float *dir=NULL);
>>>>>>> b025d1450191b30cdd6a03f0487632930308d71e
		~Spot();

	private:
		float
			angle,
			exponent,
			*direction;
	};

#endif
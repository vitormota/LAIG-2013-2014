#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include <string>
#ifdef __APPLE__
#include "CGFlight.h"
#else
#include <CGFlight.h>
#endif


	using namespace std;

	class Lightning/*:public CGFlight*/{
        
    public:
        Lightning();
        ~Lightning();

	};

	class Omni:public Lightning{
	public:
		Omni(string id,bool enabled,float *location,float *ambient,float *difuse,float *specular);
		~Omni();
	private:
		string id;
		bool enabled;
		float
			location[4],
			ambient[4],
			difuse[4],
			specular[4];
	};

	class Spot:public Lightning{
	public:
		Spot(string id, bool enabled, float *location, float *ambient,float *difuse, float *specular, float angle, float exponent,float *direction);
		~Spot();
	private:
		string id;
		bool enabled;
		float
			location[4],
			ambient[4],
			difuse[4],
			specular[4],
			angle,
			exponent,
			direction[3];
	};

#endif
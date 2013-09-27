#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include <string>
#include <CGFlight.h>

namespace scene{

	using namespace std;

	

	class Light:public CGFlight{

	};

	class Omni:public Light{
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

	class Spot:public Light{
	public:
		Spot(string id,bool enabled,float *location,float *ambient,float *difuse,float *specular,float angle,float exponent,float *direction);
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

} //scene

#endif
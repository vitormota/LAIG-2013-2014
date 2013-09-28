#include "Lightning.h"


using namespace std;

Light::Light(string id,bool enabled,unsigned int light_id,
             float *pos,float location[4],float ambient[4],
             float difuse[4],float specular[4],float *dir):CGFlight(light_id,pos,dir){
    this->enabled=enabled;
    this->id = id;
    this->location=location;
    this->specular =specular;
    this->ambient=ambient;
    this->difuse=difuse;
    
}

Light::~Light(){
    delete [] &location;
    delete [] &ambient;
    delete [] &difuse;
    delete [] &specular;
}

Omni::Omni(string id,bool enabled,unsigned int light_id,
           float *pos,float location[4],float ambient[4],
           float difuse[4],float specular[4],float *dir)
:Light(id,enabled,light_id,pos,location,ambient,difuse,specular,dir){}

Omni::~Omni(){
}

Spot::Spot(string id,bool enabled,unsigned int light_id,
           float *pos,float location[4],float ambient[4],
           float difuse[4],float specular[4],float angle,
           float exponent, float direction[4],float *dir)
:Light(id,enabled,light_id,pos,location,ambient,difuse,specular,dir){
    this->angle=angle;
    this->exponent=exponent;
    this->direction=direction;
}

Spot::~Spot(){
    delete [] &direction;
}

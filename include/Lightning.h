#ifndef _LIGHTNING_H
#define _LIGHTNING_H

#include <string>
#ifdef __APPLE__
#include "CGFlight.h"
#elif __unnix
#include <CGF/CGFlight.h>
#else 
#include <CGFlight.h>
#endif


using namespace std;

typedef struct {
    bool doublesided;
    bool local;
    bool enabled;
    float ambient[4];
} global_lightning_vars;

class Light {
public:
    Light(string id, bool enabled, unsigned int light_id,
            float *pos, float ambient[4],
            float difuse[4], float specular[4], float *dir = NULL);
    virtual ~Light();

    string getId()const {
        return id;
    }

    bool isEnabled()const {
        return enabled;
    }

    //pure virtual makes class abstract
    virtual float getVars()const = 0;
protected:
    string id;
    bool enabled;
    float
    *location,
    *ambient,
    *difuse,
    *specular;
};

class Omni : public Light {
public:
    Omni(string id, bool enabled, unsigned int light_id,
            float *pos, float ambient[4],
            float difuse[4], float specular[4], float *dir = NULL);
    ~Omni();

    float getVars()const{return 0;}

private:

};

class Spot : public Light {
public:

    Spot(string id, bool enabled, unsigned int light_id,
            float *pos, float ambient[4],
            float difuse[4], float specular[4], float angle,
            float exponent, float direction[3], float *dir = NULL);

    ~Spot();
    
    float getVars()const{return 0;}

private:
    float
    angle,
    exponent,
    *direction;
};

#endif
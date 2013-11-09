#ifndef _Lighting_H
#define _Lighting_H

#include <string>
#ifdef __APPLE__
#include "CGFlight.h"
#elif __unix
#include <CGF/CGFlight.h>
#else
#include <GL\glew.h>
#include "CGF\CGFlight.h"
#endif

using namespace std;

class Lighting {
public:
    Lighting();
    Lighting(string type, string id, bool enabled, float location[3],
    float ambient[4], float difuse[4], float specular[4]);
    ~Lighting();

    void setId(string id);
    void setType(string type);
    void setEnabled(bool enabled);
    void setLocation(float* location);
    void setAmbient(float* ambient);
    void setDiffuse(float* diffuse);
    void setSpecular(float* specular);
    string getId();
    float* getLocation();
    float* getAmbient();
    float* getDiffuse();
    float* getSpecular();
    string getType();
    
    // spot only
    void setAngle(float angle);
    void setExponent(float exponent);
    void setDirection(float* direction);
    float getAngle();
    float getExponent();
    float* getDirection();

    bool isEnabled();
   
private:
    // omni and spot
    string type; // type of light (omni/spot)
    string id;
    bool enabled;
    float location[3];
    float ambient[4];
    float diffuse[4];
    float specular[4];
    
    // spot only
    float angle;
    float exponent;
    float direction[3];
};

#endif
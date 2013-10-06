#include "Lighting.h"

#if __unix
#include <cstring>
#endif


using namespace std;

Lighting::Lighting()
{
    
}

Lighting::Lighting(string type, string id, bool enabled, float location[3],
                     float ambient[4], float diffuse[4], float specular[4]) {
    this->id = id;
    this->enabled = enabled;
    this->type=type;
    memcpy(this->location, location,3*sizeof(float));
    memcpy(this->specular, specular,4*sizeof(float));
    memcpy(this->ambient, ambient,4*sizeof(float));
    memcpy(this->diffuse, diffuse,4*sizeof(float));
    this->angle = 0;
    this->exponent = 0;
}

Lighting::~Lighting() {
    delete [] & location;
    delete [] & ambient;
    delete [] & diffuse;
    delete [] & specular;
}

void Lighting::setId(string id)
{
    this->id = id;
}

void Lighting::setType(string type)
{
    this->type = type;
}

void Lighting::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

void Lighting::setLocation(float* location)
{
    memcpy(this->location, location, 3*sizeof(float));
}

void Lighting::setAmbient(float* ambient)
{
    memcpy(this->ambient, ambient, 4*sizeof(float));
}

void Lighting::setDiffuse(float* diffuse)
{
    memcpy(this->diffuse, diffuse, 4*sizeof(float));
}

void Lighting::setSpecular(float* specular)
{
    memcpy(this->specular, specular, 4*sizeof(float));
}

string Lighting::getId()
{
    return this->id;
}

float* Lighting::getLocation()
{
    return this->location;
}

float* Lighting::getAmbient()
{
    return this->ambient;
}

float* Lighting::getDiffuse()
{
    return this->diffuse;
}

float* Lighting::getSpecular()
{
    return this->specular;
}

string Lighting::getType()
{
    return this->type;
}

void Lighting::setAngle(float angle)
{
    this->angle = angle;
}

void Lighting::setExponent(float exponent)
{
    this->exponent = exponent;
}

void Lighting::setDirection(float* direction)
{
    memcpy(this->direction, direction, 3*sizeof(float));
}

float Lighting::getAngle()
{
    return this->angle;
}

float Lighting::getExponent()
{
    return this->exponent;
}

float* Lighting::getDirection()
{
    return this->direction;
}


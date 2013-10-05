#include "Lightning.h"


using namespace std;

Lightning::Lightning()
{
    
}

Lightning::Lightning(string type, string id, bool enabled, float location[4],
                     float ambient[4], float diffuse[4], float specular[4]) {
    this->id = id;
    this->enabled = enabled;
    memcpy(this->location, location,4*sizeof(float));
    memcpy(this->specular, specular,4*sizeof(float));
    memcpy(this->ambient, ambient,4*sizeof(float));
    memcpy(this->diffuse, diffuse,4*sizeof(float));
}

Lightning::~Lightning() {
    delete [] & location;
    delete [] & ambient;
    delete [] & diffuse;
    delete [] & specular;
}

void Lightning::setId(string id)
{
    this->id = id;
}

void Lightning::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

void Lightning::setLocation(float* location)
{
    memcpy(this->location, location, 4*sizeof(float));
}

void Lightning::setAmbient(float* ambient)
{
    memcpy(this->ambient, ambient, 4*sizeof(float));
}

void Lightning::setDiffuse(float* diffuse)
{
    memcpy(this->diffuse, diffuse, 4*sizeof(float));
}

void Lightning::setSpecular(float* specular)
{
    memcpy(this->specular, specular, 4*sizeof(float));
}

string Lightning::getId()
{
    return this->id;
}

float* Lightning::getLocation()
{
    return this->location;
}

float* Lightning::getAmbient()
{
    return this->ambient;
}

float* Lightning::getDiffuse()
{
    return this->diffuse;
}

float* Lightning::getSpecular()
{
    return this->specular;
}

string Lightning::getType()
{
    return this->type;
}

void Lightning::setAngle(float angle)
{
    this->angle = angle;
}

void Lightning::setExponent(float exponent)
{
    this->exponent = exponent;
}

void Lightning::setDirection(float* direction)
{
    memcpy(this->direction, direction, 3*sizeof(float));
}

float Lightning::getAngle()
{
    return this->angle;
}

float Lightning::getExponent()
{
    return this->exponent;
}

float* Lightning::getDirection()
{
    return this->direction;
}


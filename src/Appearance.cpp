//
//  Appearance.cpp
//  LAIG - P1
//
//  Created by Maria Araújo on 03/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Appearance.h"

Appearance::Appearance()
{
    
}

Appearance::Appearance(string id,
           float emissive[4], float ambient[4], float diffuse[4],
           float specular[4], float shininess, string textureref,
           float texlength_s, float texlength_t)
{
}

Appearance::~Appearance() {
	
}

string Appearance::getId()
{
    return this->id;
}

float* Appearance::getEmissive()
{
    return this->emissive;
}

float* Appearance::getAmbient()
{
    return this->ambient;
}

float* Appearance::getDiffuse()
{
    return this->diffuse;
}

float* Appearance::getSpecular()
{
    return this->specular;
}

float Appearance::getShininess()
{
    return this->shininess;
}

string Appearance::getTextureref()
{
    return this->textureref;
}

float Appearance::getTexlength_s()
{
    return this->texlength_s;
}

float Appearance::getTexlength_t()
{
    return this->texlength_t;
}

void Appearance::setId(string id)
{
    this->id = id;
}

void Appearance::setTextureref(string textureref)
{
    this->textureref = textureref;
}

void Appearance::setEmissive(float* emissive)
{
    memcpy(this->emissive, emissive, 4*sizeof(float));
}

void Appearance::setAmbient(float* ambient)
{
    memcpy(this->ambient, ambient, 4*sizeof(float));
}

void Appearance::setDiffuse(float* diffuse)
{
    memcpy(this->diffuse, diffuse, 4*sizeof(float));
}

void Appearance::setSpecular(float* specular)
{
    memcpy(this->specular, specular, 4*sizeof(float));
}

void Appearance::setShininess(float shininess)
{
    this->shininess = shininess;
}

void Appearance::setTexlength_s(float texlength_s)
{
    this->texlength_s = texlength_s;
}

void Appearance::setTexlength_t(float texlength_t)
{
    this->texlength_t = texlength_t;
}
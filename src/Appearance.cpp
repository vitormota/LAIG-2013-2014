//
//  Appearance.cpp
//  LAIG - P1
//
//  Created by Maria Araújo on 03/10/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#include "Appearance.h"
#if __unix
#include <cstring>
#endif

Appearance::Appearance() {

}

Appearance::Appearance(string id,
	float emissive[4], float ambient[4], float diffuse[4],
	float specular[4], float shininess, string textureref,
	float texlength_s, float texlength_t) {
    this->id = id;
    memcpy(this->emissive, emissive, 4 * sizeof (float));
    memcpy(this->ambient, ambient, 4 * sizeof (float));
    memcpy(this->diffuse, diffuse, 4 * sizeof (float));
    memcpy(this->specular, specular, 4 * sizeof (float));
    this->shininess = shininess;
    this->textureref = textureref;
    this->texlength_s = texlength_s;
    this->texlength_t = texlength_t;
}

Appearance::Appearance(string id,
	float emissive[4], float ambient[4], float diffuse[4],
	float specular[4], float shininess) {
    this->id = id;
    memcpy(this->emissive, emissive, 4 * sizeof (float));
    memcpy(this->ambient, ambient, 4 * sizeof (float));
    memcpy(this->diffuse, diffuse, 4 * sizeof (float));
    memcpy(this->specular, specular, 4 * sizeof (float));
    this->shininess = shininess;
}

Appearance::~Appearance() {

}

string Appearance::getId() {
    return this->id;
}

float* Appearance::getEmissive() {
    return this->emissive;
}

float* Appearance::getAmbient() {
    return this->ambient;
}

float* Appearance::getDiffuse() {
    return this->diffuse;
}

float* Appearance::getSpecular() {
    return this->specular;
}

float Appearance::getShininess() {
    return this->shininess;
}

string Appearance::getTextureref() {
    return this->textureref;
}

float Appearance::getTexlength_s() {
    return this->texlength_s;
}

float Appearance::getTexlength_t() {
    return this->texlength_t;
}

void Appearance::setId(string id) {
    this->id = id;
}

void Appearance::setTextureref(string textureref) {
    this->textureref = textureref;
}

void Appearance::setEmissive(float* emissive) {
    memcpy(this->emissive, emissive, 4 * sizeof (float));
}

void Appearance::setAmbient(float* ambient) {
    memcpy(this->ambient, ambient, 4 * sizeof (float));
}

void Appearance::setDiffuse(float* diffuse) {
    memcpy(this->diffuse, diffuse, 4 * sizeof (float));
}

void Appearance::setSpecular(float* specular) {
    memcpy(this->specular, specular, 4 * sizeof (float));
}

void Appearance::setShininess(float shininess) {
    this->shininess = shininess;
}

void Appearance::setTexlength_s(float texlength_s) {
    this->texlength_s = texlength_s;
}

void Appearance::setTexlength_t(float texlength_t) {
    this->texlength_t = texlength_t;
}

/*void Appearance::apply()
{
    glDisable(GL_COLOR);
    glDisable(GL_COLOR_MATERIAL);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, this->ambient); // ambient
    glMaterialfv(GL_FRONT, GL_EMISSION, this->getEmissive()); // emissive
    glMaterialfv(GL_FRONT, GL_DIFFUSE, this->getDiffuse()); // diffuse
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->getSpecular()); // specular
    glMaterialf(GL_FRONT, GL_SHININESS, this->getShininess()); // shininess
}

void Appearance::setTextureWrap(unsigned int sWrap, unsigned int tWrap)
{
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tWrap);
}

void Appearance::setTexture(string file)
{
    //glEnable(GL_TEXTURE_2D);
}*/


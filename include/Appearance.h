/* 
 * File:   Appearance.h
 * Author: vitor-mota
 *
 * Created on September 29, 2013, 2:00 PM
 */

#ifndef APPEARANCE_H
#define	APPEARANCE_H

#if __unix
#include <CGF/CGFappearance.h>
#elif __APPLE__
#include "CGFappearance.h"
#endif

class Appearance {
    
private:
    string id;
    string textureref;
    float texlength_s, texlength_t;
    float emissive[4];
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float shininess;
    
public:

    Appearance();
    Appearance(string id,
	    float emissive[4], float ambient[4], float diffuse[4],
	    float specular[4], float shininess, string textureref,
               float texlength_s, float texlength_t);
    ~Appearance();
    string getId();
    string getTextureref();
    float* getEmissive();
    float* getAmbient();
    float* getDiffuse();
    float* getSpecular();
    float getShininess();
    float getTexlength_s();
    float getTexlength_t();
    void setId(string id);
    void setTextureref(string textureref);
    void setEmissive(float* emissive);
    void setAmbient(float* ambient);
    void setDiffuse(float* diffuse);
    void setSpecular(float* specular);
    void setShininess(float shininess);
    void setTexlength_s(float texlength_s);
    void setTexlength_t(float texlength_t);
};


#endif	/* APPEARANCE_H */


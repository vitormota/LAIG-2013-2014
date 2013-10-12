/* 
 * File:   Appearance.h
 * Author: vitor-mota
 *
 * Created on September 29, 2013, 2:00 PM
 */

#ifndef APPEARANCE_H
#define	APPEARANCE_H

/*#if __unix
#include <CGF/CGFappearance.h>
#elif __APPLE__
#include "CGFappearance.h"
#endif*/



#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <GL/glui.h>
#endif

using std::string;


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
    
    void apply();
    void setTextureWrap(unsigned int sWrap, unsigned int tWrap);
    void setTexture(string file);
};


#endif	/* APPEARANCE_H */


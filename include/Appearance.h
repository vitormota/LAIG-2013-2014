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

class Appearance : public CGFappearance {
public:

    Appearance(string id,
	    float emissive[4], float ambient[4], float diffuse[4],
	    float specular[4], float shininess, string textureref,
	    float texlength_s, float texlength_t)
    : CGFappearance(ambient, diffuse, specular, shininess),
    id(id), texlength_s(texlength_s), textlength_t(texlength_t),
    textureRef(textureref), emissive(emissive) {
    }

    ~Appearance() {
	delete[] &emissive;
    }

    string id, textureRef;
    float texlength_s, textlength_t;
    float *emissive; //???? what's this????

};


#endif	/* APPEARANCE_H */


/* 
 * File:   Texture.h
 * Author: vitor-mota
 *
 * Created on September 29, 2013, 1:48 PM
 */

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>
#if __unix
#include <CGF/CGFtexture.h>
#elif __APPLE__
#include "CGFtexture.h"
#endif

using namespace std;

class Texture {
public:
    string id;
    string file;
    
    Texture(string id,string file);
    ~Texture();
};

#endif	/* TEXTURE_H */


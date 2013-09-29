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

class Texture:public CGFtexture{
public:
    string id;
    
    Texture(string id,string path)
            :CGFtexture(path),id(id){}
    ~Texture(){}
};

#endif	/* TEXTURE_H */


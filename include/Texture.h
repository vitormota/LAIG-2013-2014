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
#else
#include "CGF\CGFtexture.h"
#endif

using namespace std;

class Texture {
private:
    string id;
    string file;
public:
    Texture();
    Texture(string id,string file);
    ~Texture();
    string getId();
    string getFile();
    void setId(string id);
    void setFile(string file);
};

#endif	/* TEXTURE_H */


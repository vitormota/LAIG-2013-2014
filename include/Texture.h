#ifndef TEXTURE_H
#define	TEXTURE_H

#if __unix
#include <CGF/CGFtexture.h>
#elif __APPLE__
#include "CGFtexture.h"
#else
#include "CGF\CGFtexture.h"
#endif

#include <string>

using std::string;

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


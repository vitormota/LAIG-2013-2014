#include "Texture.h"

Texture::Texture()
{
    
}

Texture::Texture(string id,string file)
{
    this->id = id;
    this->file = file;
}

Texture::~Texture()
{}

string Texture::getId()
{
    return this->id;
}

string Texture::getFile()
{
    return this->file;
}

void Texture::setId(string id)
{
    this->id = id;
}

void Texture::setFile(string file)
{
    this->file = file;
}
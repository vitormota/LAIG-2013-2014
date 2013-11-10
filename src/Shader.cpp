#include "Shader.h"

Shader::Shader(string basetext,string secondText,string vertex,string frag){
	tempo = 0.0;
	//init("data/appValues.vert", "data/dualVaryingColor.frag");
#if _WIN32
	init(vertex.c_str(),frag.c_str());
#else
    init("texshader.vert", "texshader.frag"); // MAC OS X version
#endif
	CGFshader::bind();

	// Initialize parameter in memory
	normScale=0.0;
	
	// Store Id for the uniform "normScale", new value will be stored on bind()
	scaleLoc = glGetUniformLocation(id(), "normScale");

#if _WIN32
	baseTexture=new CGFtexture(basetext.c_str());
	secTexture=new CGFtexture(secondText.c_str());
#else
    /* MAC OS X version */
	baseTexture=new CGFtexture("water.jpg");
	secTexture=new CGFtexture("watermap.jpg");
#endif

	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "baseImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseImageLoc, 0);

	// repeat if you use more textures in your shader(s)
	secImageLoc = glGetUniformLocation(id(), "secondImage");
	glUniform1i(secImageLoc, 1);

	timeLoc = glGetUniformLocation(id(), "time"); 
}


Shader::Shader()
{
	tempo = 0.0;
	//init("data/appValues.vert", "data/dualVaryingColor.frag");
#if _WIN32
	init("data/texshader.vert", "data/texshader.frag");
#else
    init("texshader.vert", "texshader.frag"); // MAC OS X version
#endif
	//init("data/textureDemo2.vert", "data/textureDemo2.frag");

	CGFshader::bind();

	// Initialize parameter in memory
	normScale=0.0;
	
	// Store Id for the uniform "normScale", new value will be stored on bind()
	scaleLoc = glGetUniformLocation(id(), "normScale");

#if _WIN32
	baseTexture=new CGFtexture("data/water.jpg");
	secTexture=new CGFtexture("data/watermap.jpg");
#else
    /* MAC OS X version */
	baseTexture=new CGFtexture("water.jpg");
	secTexture=new CGFtexture("watermap.jpg");
#endif

	// get the uniform location for the sampler
	baseImageLoc = glGetUniformLocation(id(), "baseImage");

	// set the texture id for that sampler to match the GL_TEXTUREn that you 
	// will use later e.g. if using GL_TEXTURE0, set the uniform to 0
	glUniform1i(baseImageLoc, 0);

	// repeat if you use more textures in your shader(s)
	secImageLoc = glGetUniformLocation(id(), "secondImage");
	glUniform1i(secImageLoc, 1);

	timeLoc = glGetUniformLocation(id(), "time"); 
}

void Shader::bind(void)
{
	CGFshader::bind();
	glUniform1f(timeLoc, tempo);

	// update uniforms
	glUniform1f(scaleLoc, normScale);

	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

	// do the same for other textures
	glActiveTexture(GL_TEXTURE1);

	secTexture->apply();

	glActiveTexture(GL_TEXTURE0);

}

void Shader::update(float time)
{
	tempo = time;
}


Shader::~Shader(void)
{
	delete(baseTexture);
}

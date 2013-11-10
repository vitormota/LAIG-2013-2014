#ifndef _SHADER_H_
#define _SHADER_H_

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL\glew.h>
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <GL/glui.h>

#endif

#include "CGFshader.h"
#include "CGFtexture.h"

class Shader :	public CGFshader
{
public:
	Shader();
	virtual void bind(void);
	~Shader(void);
	void setScale(float s);
	float normScale;

protected:
	CGFtexture * baseTexture;
	CGFtexture * secTexture;

	GLint baseImageLoc;
	GLint secImageLoc;

	GLint scaleLoc;
};

#endif // _DEMO_SHADER_H_
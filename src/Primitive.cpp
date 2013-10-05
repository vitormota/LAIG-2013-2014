//
//  Primitive.cpp
//  LAIG - P1
//

#include "Primitive.h"

namespace scene{

    Primitive::Primitive()
    {
        
    }
    
	Primitive::Primitive(string id)
	{
		this->id = id;
	}

	Primitive::~Primitive()
	{
        
	}

	void Primitive::setId(string id)
	{
		this->id = id;
	}

	string Primitive::getId()
	{
		return this->id;
	}
    
    Cylinder::~Cylinder()
    {
        gluDeleteQuadric(cylinderQuadric);
    }
	Rectangle::Rectangle(string id,float x1, float y1, float x2, float y2) : Primitive(id)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
	}

	Triangle::Triangle(string id, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) : Primitive(id)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->x3 = x3;
		this->y1 = y1;
		this->y2 = y2;
		this->y3 = y3;
		this->z1 = z1;
		this->z2 = z2;
		this->z3 = z3;
	}

	Cylinder::Cylinder(string id, float base, float top, float height, int slices, int stacks) : Primitive(id)
	{
		this->base = base;
		this->top = top;
		this->height = height;
		this->slices = slices;
		this->stacks = stacks;

		cylinderQuadric = gluNewQuadric();
		gluQuadricTexture(cylinderQuadric, GL_TRUE);
		gluQuadricDrawStyle(cylinderQuadric, GLU_FILL);
		gluQuadricNormals(cylinderQuadric, GLU_SMOOTH);
		gluQuadricOrientation(cylinderQuadric, GLU_OUTSIDE);
	}

	Sphere::Sphere(string id, float radius, int slices, int stacks) : Primitive(id)
	{
		this->radius = radius;
		this->slices = slices;
		this->stacks = stacks;
        
        sphereQuadric = gluNewQuadric();
        gluQuadricDrawStyle(sphereQuadric, GLU_FILL);
        gluQuadricNormals(sphereQuadric, GLU_SMOOTH);
        gluQuadricOrientation(sphereQuadric, GLU_OUTSIDE);
        gluQuadricTexture(sphereQuadric, GL_TRUE);
	}

	Torus::Torus(string id, float inner, float outer, int slices, int loops) : Primitive(id)
	{
		this->inner = inner;
		this->outer = outer;
		this->slices = slices;
		this->loops = loops;
	}

	void Rectangle::draw()
	{
		glPushMatrix();

		glBegin(GL_QUADS);

        glTexCoord2d(x1, y1);
		glVertex2f(x1, y1);
        glTexCoord2d(x2, y1);
		glVertex2f(x2, y1);
        glTexCoord2d(x2, y2);
		glVertex2f(x2, y2);
        glTexCoord2d(x1, y2);
		glVertex2f(x1, y2);

		glEnd();

		glPopMatrix();
	}

	void Triangle::draw()
	{
		glPushMatrix();

        //glEnable(GL_NORMALIZE);
        
		glBegin(GL_TRIANGLES);

        glTexCoord3d(x1, y1, z1);
		glVertex3f(x1, y1, z1);
        glTexCoord3d(x2, y2, z2);
		glVertex3f(x2, y2, z2);
        glTexCoord3d(x3, y3, z3);
		glVertex3f(x3, y3, z3);

		glEnd();

		glPopMatrix();
	}

	void Cylinder::draw()
	{
        glEnable(GL_NORMALIZE);
        
		// top of the cylinder
		glPushMatrix();

        cylinderQuadric = gluNewQuadric();
		gluDisk(cylinderQuadric,0,base,slices,stacks);
		glTranslated(0, 0, height);
		gluDisk(cylinderQuadric, 0, top, slices, stacks);

		glPopMatrix();

		glPushMatrix();
        cylinderQuadric = gluNewQuadric();
		gluCylinder(cylinderQuadric, base, top, height, slices, stacks);
		glPopMatrix();

		// base of the cylinder
		glPushMatrix();
		glRotated(180,0,1,0);
		gluDisk(cylinderQuadric, 0 , base, slices, stacks);
		glPopMatrix();
	}

	void Sphere::draw()
	{
		glPushMatrix();
		gluSphere(sphereQuadric, radius, slices, stacks);
		glPopMatrix();
	}

	void Torus::draw()
	{
		glPushMatrix();
        
        glEnable(GL_NORMALIZE);
        glEnable(GL_TEXTURE_GEN_S);
        glEnable(GL_TEXTURE_GEN_T);
        
		glutSolidTorus(inner, outer, slices, loops);
        
        glDisable(GL_TEXTURE_GEN_S);
        glDisable(GL_TEXTURE_GEN_T);
        
		glPopMatrix();
	}



}


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

    void Primitive::setTexlength_s(float texlength_s)
    {
        this->texlength_s = texlength_s;
    }
    
    void Primitive::setTexlength_t(float texlength_t)
    {
        this->texlength_t = texlength_t;
    }
    
	string Primitive::getId()
	{
		return this->id;
	}
    
    float Primitive::getTexlength_s()
    {
        return this->texlength_s;
    }
    
    float Primitive::getTexlength_t()
    {
        return this->texlength_t;
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
		gluQuadricDrawStyle(cylinderQuadric, GLU_FILL);
		gluQuadricNormals(cylinderQuadric, GLU_SMOOTH);
		gluQuadricOrientation(cylinderQuadric, GLU_OUTSIDE);
        gluQuadricTexture(cylinderQuadric, GL_TRUE);
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
        glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
        glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
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
        
        /*
        // p1, p2, p3: triangle vertexes p2
        e1 = p2-p1;
        e2 = p3-p1;
        n = cross(edge1, edge2).normalize();
        
        // vector supports: x,y,z or type float
        
        struct vector e1, e2, n;
        float l;
        e1.x = p2.x - p1.x;
        e1.y = p2.y - p1.y;
        e1.z = p2.z - p1.z;
        e2.x = p3.x - p1.x;
        e2.y = p3.y - p1.y;
        e3.z = p3.z - p1.z;
        n e1
        n.x = (e1.y * e2.z)
        n.y = (e1.z * e2.x)
        n.z = (e1.x * e2.y)
        - (e1.z * e2.y);
        - (e1.x * e2.z);
        - (e1.y * e2.x);
        
        // Normalize (divide by root of dot product)
        l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z); n.x /= l;
        n.y /= l;
        n.z /= l;*/
	}

	void Cylinder::draw()
	{
        //glEnable(GL_NORMALIZE);
        
		// top of the cylinder
		glPushMatrix();

		gluDisk(cylinderQuadric,0,base,slices,stacks);
		glTranslated(0, 0, height);
		gluDisk(cylinderQuadric, 0, top, slices, stacks);

		glPopMatrix();

		glPushMatrix();
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


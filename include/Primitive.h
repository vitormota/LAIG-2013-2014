#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

#include <string>
#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <GL/glui.h>
#endif


using std::string;

namespace scene{

	class Primitive
	{
	private:
		string id;
        float texlength_s;
        float texlength_t;

	public:
        Primitive();
		Primitive(string id);
		~Primitive();
		void setId(string id);
        void setTexlength_s(float texlength_s);
        void setTexlength_t(float texlength_t);
		string getId();
        float getTexlength_s();
        float getTexlength_t();
		virtual void draw(){}
        float *get_normal_newell(float **vertices, int size);
        
        float **verticesRectangle; // vertices of the rectangle primitive
        float **verticesTriangle; // vertices of the triangle primitive
        float *normalRectangle; // normal of the rectangle primitive
        float *normalTriangle; // normal of the triangle primitive

	};

	/* Rectangle */
	class Rectangle: public Primitive{

	private:
		float x1, y1, x2, y2;
		float **vertices;
		float *normal;
        float height,length;

	public:
		Rectangle(string id,float x1, float y1, float x2, float y2);
		virtual void draw();
	};

	/* Triangle */
	class Triangle: public Primitive{

	private:
		float x1, y1, z1, x2, y2, z2, x3, y3, z3;

	public:
		Triangle(string id, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
		virtual void draw();
	};

	/* Cylinder */
	class Cylinder: public Primitive{

	private:
		float base, top, height;
		int slices, stacks;
		GLUquadric* cylinderQuadric;

	public:
		Cylinder(string id, float base, float top, float height, int slices, int stacks);
        ~Cylinder();
		virtual void draw();
	};

	/* Sphere */
	class Sphere: public Primitive{

	private:
		float radius;
		int slices, stacks;
        GLUquadric* sphereQuadric;

	public:
		Sphere(string id, float radius, int slices, int stacks);
		virtual void draw();
	};

	/* Torus */
	class Torus: public Primitive{

	private:
		float inner, outer;
		int slices, loops;

	public:
		Torus(string id, float inner, float outer, int slices, int loops);
		virtual void draw();
	};

}





#endif
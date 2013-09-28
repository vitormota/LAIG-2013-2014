#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

#include <string>
#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <gl\glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <gl\glui.h>
#endif


using std::string;

namespace scene{

	class Primitive
	{
	private:
		string id;

	public:
		Primitive(string id);
		~Primitive();
		void setId(string id);
		string getId();
		virtual void draw(){}

	};

	// RECTANGLE
	class Rectangle: public Primitive{

	private:
		float x1, y1, x2, y2;

	public:
		Rectangle(string id,float x1, float y1, float x2, float y2);
		virtual void draw();
	};

	// TRIANGLE
	class Triangle: public Primitive{

	private:
		float x1, y1, z1, x2, y2, z2, x3, y3, z3;

	public:
		Triangle(string id, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
		virtual void draw();
	};

	// CYLINDER
	class Cylinder: public Primitive{

	private:
		float base, top, height;
		int slices, stacks;
		GLUquadric* cylinderQuadric;

	public:
		Cylinder(string id, float base, float top, float height, int slices, int stacks);
		virtual void draw();
	};

	// SPHERE
	class Sphere: public Primitive{

	private:
		float radius;
		int slices, stacks;

	public:
		Sphere(string id, float radius, int slices, int stacks);
		virtual void draw();
	};

	// TORUS
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
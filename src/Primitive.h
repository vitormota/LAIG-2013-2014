#ifndef _PRIMITIVE_H
#define _PRIMITIVE_H

#include "Node.h"

namespace scene{

	class Rectangle:public Node{
	public:
		Rectangle(string id,float *p1,float *p2)
			:Node(id){
				this->p1=p1;
				this->p2=p2;
			}
		float *p1,*p2;
		void draw();
	};

	class Triangle:public Node{
	public:
		Triangle(string id, float *p1,float *p2,float *p3)
			:Node(id){
				this->p1=p1;
				this->p2=p2;
				this->p3=p3;
		}
		float *p1,*p2,*p3;
		void draw();
	};

	class Cylinder:public Node{
	public:
		Cylinder(string id, float base,float top,float height,int slices,int stacks)
			:Node(id),base(base),top(top),height(height),slices(slices),stacks(stacks){}
		float base,top,height;
		int slices,stacks;
		void draw();
	};

}//scene

#endif
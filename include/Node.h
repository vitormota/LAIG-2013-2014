#ifndef _NODE_H
#define _NODE_H

#include <CGFobject.h>
#include <string>
#include <vector>

using namespace std;

namespace scene{

	enum primitives{
		COMPLEX, RECTANGLE, TRIANGLE, SPHERE, CYLINDER, TORUS
	};

	class Node:public CGFobject{
	public:
		Node(std::string id):
			name(id){;}
		Node(const Node &n);
		~Node();

		std::string name;
		std::vector<std::string> children;
		float trasnforms[16];
		///0 means complex object
		int primitive_type;

		virtual void draw();
	
	private:
		
	};

}//scene

#endif
#ifndef _NODE_H
#define _NODE_H

#ifdef __APPLE__
#include "CGFobject.h"
#else
#include <CGFobject.h>
#endif

#include "Transform.h"
#include "Primitive.h"

#include <string>
#include <vector>

using namespace std;

namespace scene{

	enum primitives{
		COMPLEX, RECTANGLE, TRIANGLE, SPHERE, CYLINDER, TORUS
	};

	class Node:public CGFobject{
	
    public:
        Node(string id);
        ~Node();
        
		/*Node(std::string id):
			name(id){;}
		Node(const Node &n);


		float transforms[16];
		///0 means complex object
		int primitive_type;
        */
        
		virtual void draw(){}
	
	private:
        string id;
        vector<Transform*> transforms;
        vector<Node*> children;
        vector<Primitive*> primitives;
        
		
	};

}//scene

#endif
#ifndef _NODE_H
#define _NODE_H

#ifdef __APPLE__
#include "CGFobject.h"
#else
#include <CGF/CGFobject.h>
#endif

#include "Transform.h"
#include "Primitive.h"

#include <string>
#include <vector>

using namespace std;

	enum primitives{
		COMPLEX, RECTANGLE, TRIANGLE, SPHERE, CYLINDER, TORUS
	};

	class Node{
	
    public:
        Node();
        Node(string id);
        ~Node();
        void setId(string id);
        void setAppearanceRef(string appearanceref);
        void setTransforms(vector<Transform*> transforms);
        void setPrimitives(vector<scene::Primitive*> primitives);
        void setChildrenNodeRef(vector<string> childrenNodeRef);
        string getId();
        string getAppearanceRef();
        vector<Transform*> getTransforms();
        vector<string> getChildrenNodeRef();
        vector<scene::Primitive*> getPrimitives();
        
        
		// TODO: Transform* getSingleTransform(); // multiply the matrixes of all the transforms vector
        
		virtual void draw(){}
	
	private:
        string id;
        string appearanceref;
        vector<Transform*> transforms; // transforms of the node
        vector<string> childrenNodeRef; // noderef's of the children
        vector<scene::Primitive*> primitives; // primitives of the node
        
		
	};


#endif
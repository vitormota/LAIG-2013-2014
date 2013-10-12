#ifndef _NODE_H
#define _NODE_H

#ifdef __APPLE__
#include "CGFobject.h"
#elif __unix
#include <CGF/CGFobject.h>
#elif _WIN32
#include "CGF\CGFobject.h"
#endif

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
        void setPrimitives(vector<scene::Primitive*> primitives);
        void setChildrenNodeRef(vector<string> childrenNodeRef);
        void setMatrix(float* matrix);
        string getId();
        string getAppearanceRef();
        vector<string> getChildrenNodeRef();
        vector<scene::Primitive*> getPrimitives();
        float* getMatrix();
        
		virtual void draw(){}
	
	private:
        string id;
        string appearanceref;
        vector<string> childrenNodeRef; // noderef's of the children
        vector<scene::Primitive*> primitives; // primitives of the node
        float matrix[16];
		
	};


#endif
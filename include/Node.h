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

using std::string;
using std::vector;

	enum primitives{
		COMPLEX, RECTANGLE, TRIANGLE, SPHERE, CYLINDER, TORUS
	};

	class Node{
	
    public:
        Node();
        Node(string id,bool display_list);
        ~Node();
        void setId(string id);
        void setAppearanceRef(string appearanceref);
        void setAnimationRef(string animationref);
        void setPrimitives(vector<scene::Primitive*> primitives);
        void setChildrenNodeRef(vector<string> childrenNodeRef);
        void setMatrix(float* matrix);
        string getId();
        string getAppearanceRef();
        string getAnimationRef();
        vector<string> getChildrenNodeRef();
        vector<scene::Primitive*> getPrimitives();
        
        //-----> NEW (TP02-Display Lists)
        //the list identifier where the
        //object will be cached
        GLuint the_object;
        //flag to specify the use of list
        bool use_list;
        //-----> END NEW
        
        float* getMatrix();
        
		virtual void draw(){}
	
	private:
        string id;
        string appearanceref, animationref;
        vector<string> childrenNodeRef; // noderef's of the children
        vector<scene::Primitive*> primitives; // primitives of the node
        float matrix[16];
		
	};


#endif
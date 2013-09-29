//
//  Scene.h
//  LAIG - P1
//

#ifndef __LAIG___P1__Scene__
#define __LAIG___P1__Scene__

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

#include <iostream>
#include "CGFscene.h"
#include "CGFappearance.h"
#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#include "Primitive.h"
#include "Graph.h"

class Scene : public CGFscene
{
    
public:
	void init();
	void display();
    void setGraph(Graph* sceneGraph);
    Graph* getGraph();
    void processGraph(); // process all the nodes of the graph in order
    void processNode(string id);
    
	~Scene();
    
    /* TESTING */
    CGFlight* light0;
	CGFlight* light1;
    CGFlight* light2;
    
    scene::Primitive* p;
    CGFappearance* pAppearance;
    
    Graph* sceneGraph;
    
    /* TESTING */
};

#endif /* defined(__LAIG___P1__Scene__) */

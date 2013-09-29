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
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <GL/glui.h>
#endif

#if __APPLE__
#include "CGFscene.h"
#include "CGFappearance.h"
#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#elif __unix
#include "CGF/CGFscene.h"
#include "CGF/CGFappearance.h"
#include "CGF/CGFscene.h"
#include "CGF/CGFaxis.h"
#include "CGF/CGFapplication.h"
#include "CGF/CGFobject.h"
#endif

#include <iostream>
#include <vector>
#include <map>
#include "Primitive.h"
#include "Graph.h"
#include "Lightning.h"
#include "Texture.h"
#include "Appearance.h"

class Scene : public CGFscene {
private:

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

    vector<Light*> lights;
    std::map<string,Texture*> texture_mapping;
    std::map<string,Appearance*> appearance_mapping;



};

#endif /* defined(__LAIG___P1__Scene__) */

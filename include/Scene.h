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
#elif _WIN32
#include "CGFscene.h"
#include "CGFappearance.h"
#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#endif


#include <iostream>
#include <vector>
#include <map>
#include "Primitive.h"
#include "Graph.h"
#include "Lightning.h"
#include "Texture.h"
#include "Appearance.h"

using std::map;
using std::string;


class Scene : public CGFscene {
private:

public:

    void init();
    void display();
    void setGraph(Graph* sceneGraph);
    void setAppearances(map<string,Appearance*> appearancesMap);
    void setTextures(map<string,Texture*> texturesMap);
    void setLights(map<string,Lightning*> lightningMap);
    void setBackground(float* background);
    void setDrawmode(string drawmode);
    void setShading(string shading);
    void setCullface(string cullface);
    void setCullorder(string cullorder);
    
    Graph* getGraph();
    map<string,Appearance*> getAppearances();
    map<string,Texture*> getTextures();
    map<string,Lightning*> getLights();
    float* getBackground();
    string getDrawmode();
    string getShading();
    string getCullface();
    string getCullorder();
    
    
    void processGraph(); // process all the nodes of the graph in order
    void processNode(string id);

    ~Scene();

    scene::Primitive* p;

    Graph* sceneGraph;

    /* globals */
    float background[4];
    string drawmode;
    string shading;
    string cullface;
    string cullorder;
    
    
    map<string,Texture*> texture_mapping;
    map<string,Appearance*> appearancesMap;
    map<string,Texture*> texturesMap;
    map<string,Lightning*> lightningMap;
    
    map<string, CGFappearance*> appearances;
    vector<CGFlight*> lights;
    vector<CGFtexture*> textures;



};

#endif /* defined(__LAIG___P1__Scene__) */

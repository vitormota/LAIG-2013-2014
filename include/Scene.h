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
#include "Lighting.h"
#include "Texture.h"
#include "Appearance.h"
#include "Camera.h"

#include <stack>

using std::map;
using std::string;

class Scene : public CGFscene {
private:

public:

    float txt_s, txt_t;

    void init();
    void display();
    void setGraph(Graph* sceneGraph);
    void setAppearances(map<string, Appearance*> appearancesMap);
    void setTextures(map<string, Texture*> texturesMap);
    void setLights(map<string, Lighting*> lightningMap);
    void setCameras(map<string, scene::Camera*> camerasMap);
    void setBackground(float* background);
    void setDrawmode(string drawmode);
    void setShading(string shading);
    void setCullface(string cullface);
    void setCullorder(string cullorder);

    void setDoublesided(bool doublesided);
    void setLocal(bool local);
    void setEnabled(bool enabled);
    void setAmbient(float* ambient);

    void setInitial(string initial);

    Graph* getGraph();
    map<string, Appearance*> getAppearances();
    map<string, Texture*> getTextures();
    map<string, Lighting*> getLights();
    map<string, scene::Camera*> getCameras();
    float* getBackground();
    string getDrawmode();
    string getShading();
    string getCullface();
    string getCullorder();

    bool getDoublesided();
    bool getLocal();
    bool getEnabled();
    float* getAmbient();

    string getInitial();

    CGFappearance *mat_wall;

    void processGraph(); // process all the nodes of the graph in order
    void processNode(string id);

    ~Scene();

    Graph* sceneGraph;

    /* globals element attributes */
    float background[4];
    string drawmode;
    string shading;
    string cullface;
    string cullorder;

    /* lighting element attributes */
    bool doublesided;
    bool local;
    bool enabled;
    float ambient[4];

    /* cameras element attribute */
    string initial;

    CGFlight *light2;

    map<string, Texture*> texture_mapping;
    map<string, Appearance*> appearancesMap;
    map<string, Texture*> texturesMap;
    map<string, Lighting*> lightingMap;
    map<string, scene::Camera*> camerasMap;

    map<string, CGFappearance*> appearances;
    vector<CGFlight*> lights;
    vector<CGFtexture*> textures;
    vector<CGFcamera*> cameras;

    stack<CGFappearance*> app_stack;


};

#endif /* defined(__LAIG___P1__Scene__) */

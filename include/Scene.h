#ifndef __LAIG___P1__Scene__
#define __LAIG___P1__Scene__

#if __APPLE__
#include "CGFscene.h"
#include "CGFappearance.h"
#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "CGFobject.h"
#include "CGFcamera.h"
#include "CGFshader.h"
#elif __unix
#include "CGF/CGFscene.h"
#include "CGF/CGFappearance.h"
#include "CGF/CGFscene.h"
#include "CGF/CGFaxis.h"
#include "CGF/CGFapplication.h"
#include "CGF/CGFobject.h"
#include "CGF/CGFshader.h"
#elif _WIN32
#include "CGF\CGFscene.h"
#include "CGF\CGFappearance.h"
#include "CGF\CGFscene.h"
#include "CGF\CGFaxis.h"
#include "CGF\CGFapplication.h"
#include "CGF\CGFobject.h"
#include "CGF\CGFshader.h"
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
#include "Animation.h"

#include <stack>
#include <string>

#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL\glew.h>
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <GL/glui.h>
#endif

using std::map;
using std::string;


class Scene: public CGFscene {
private:

public:

    void init();
    void display();
    void setGraph(Graph* sceneGraph);
    void setAppearances(map<string,Appearance*> appearancesMap);
    void setTextures(map<string,Texture*> texturesMap);
    void setLights(map<string,Lighting*> lightningMap);
    void setCameras(map<string,Camera*> camerasMap);
    void setCamerasId(map<string, unsigned int> camerasId);
    void setAnimations(map<string,Animation*> animations);
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
    map<string,Appearance*> getAppearances();
    map<string,Texture*> getTextures();
    map<string,Lighting*> getLights();
    map<string,Camera*> getCameras();
    map<string, unsigned int> getCamerasId();
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
    
    void processGraph(); // process all the nodes of the graph in order
    void processNode(string id);
    
    void changeCamera(string cameraId);

    //----> NEW (TP02- Display Lists)
    vector<int*> diplay_lists;
    int current_list_index;

	scene::Waterline *wl;
	CGFshader *s;
    //----> END NEW
    
    // Animations
    static void updateAnimations(int dummy);
    
    ~Scene();

    Graph* sceneGraph;
    
    // 1 if light is enabled, 0 if light is disabled
    int* light_0;
    int* light_1;
    int* light_2;
    int* light_3;
    int* light_4;
    int* light_5;
    int* light_6;
    int* light_7;
    
    bool light0Exists;
    bool light1Exists;
    bool light2Exists;
    bool light3Exists;
    bool light4Exists;
    bool light5Exists;
    bool light6Exists;
    bool light7Exists;

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
    
    stack<CGFappearance*> app_stack;
    stack<string> app_refStack; // references of the appearances in the app_stack (app_stack.top reference == app_refStack.top)
    
    /* cameras element attribute */
    string initial;
    
    string currentCameraId;
    
    void setCurrentCameraId(string currentCameraId);
    
    float cameraAspect; // aspect = GLUwindowWidth/GLUwindowHeight
    
    float txt_s, txt_t; // texlength_s/texlength_t
    
    map<string,Texture*> texture_mapping;
    map<string,Appearance*> appearancesMap;
    map<string,Texture*> texturesMap;
    map<string,Lighting*> lightingMap;
    map<string,Camera*> camerasMap;
    map<string, unsigned int> camerasId; // camera attribute id and Interface id
    map<string,Animation*> animations;
    
    map<string, CGFappearance*> appearances;
    vector<string> lightsId;
    vector<CGFtexture*> textures;
    
    void setDrawingMode(unsigned int mode);
    unsigned int getDrawingMode();
    int mode;
    void changeLightEnableDisable(unsigned int light_id); // enable/disable light with the id = light_id
   
	void update(unsigned long t);
};

#endif /* defined(__LAIG___P1__Scene__) */

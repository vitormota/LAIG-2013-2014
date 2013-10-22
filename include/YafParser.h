#ifndef __LAIG___P1__YafParser__
#define __LAIG___P1__YafParser__

#include <iostream>
#include <string>
#include <map>
#include "tinyxml.h"
#include "Lighting.h"
#include "Primitive.h"
#include "Graph.h"
#include "Node.h"
#include "Scene.h"
#include "Camera.h"
#include "math.h"

namespace Parser {

    using namespace std;

    enum ERRORS {
        globals_error = 1, cameras_error, lighting_error, textures_error,
        appearances_error, graph_error, file_not_found
    };

    enum node_i {
        GLOBALS, CAMERAS, LIGHTING, OMNI, SPOT, PERSPECTIVE, ORTHO, TEXTURE, APPEARANCES,
        APPEARANCE, GRAPH, NODE, TRANSFORMS, TRANSLATE, ROTATE, SCALE, APPEARANCEREF, ANIMATIONREF, CHILDREN,
        RECTANGLE, TRIANGLE, CYLINDER, SPHERE, TORUS, PLANE, PATCH, VEHICLE, WATERLINE, NODEREF
    };

    class YafParser {
    public:

        YafParser();
        YafParser(string filename);
        ~YafParser();

        /* Initial method for parsing
         ** return 0 success, or above means error */
        int loadYaf();
        Graph* getGraph();
        map<string, Appearance*> getAppearances();
        map<string, Texture*> getTextures();
        map<string, Lighting*> getLights();
        map<string,Camera*> getCameras();
        string getInitial();
        
        /* globals */
        float background[4];
        string drawmode;
        string shading;
        string cullface;
        string cullorder;
        
        /* lighting */
        bool doublesided;
        bool local;
        bool enabled;
        float ambient[4];
        
        /* cameras */
        string initial; // id of the initial camera
        
        /* transforms matrix */
        float m[16];

    private:
        string _filename;
        TiXmlDocument* doc;

        TiXmlElement* globalsElement;
        TiXmlElement* camerasElement;
        TiXmlElement* lightingElement;
        TiXmlElement* texturesElement;
        TiXmlElement* appearancesElement;
        TiXmlElement* graphElement;

        bool loadGlobals(TiXmlElement* globalsElement);
        bool loadCameras(TiXmlElement* camerasElement);
        bool loadLighting(TiXmlElement* lightingElement);
        bool loadTextures(TiXmlElement* texturesElement);
        bool loadAppearances(TiXmlElement* appearancesElement);
        bool loadGraph(TiXmlElement* graphElement);
    
        /* cameras */
        map<string, Camera*> camerasMap;
        
        /* lighting */
        map<string, Lighting*> lightingMap;

        /* textures */
        map<string, Texture*> texturesMap;

        /* appearances */
        map<string, Appearance*> appearancesMap;
        
        /* graph */
        Graph* sceneGraph;

    };
}


#endif /* defined(__LAIG___P1__YafParser__) */

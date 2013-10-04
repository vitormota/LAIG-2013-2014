//
//  YafParser.h
//  LAIG - P1
//

#ifndef __LAIG___P1__YafParser__
#define __LAIG___P1__YafParser__

#include <iostream>
#include <string>
#include <map>
#include "tinyxml.h"
#include "Lightning.h"
#include "Primitive.h"
#include "Graph.h"
#include "Node.h"
#include "Scene.h"

namespace Parser {

    using namespace std;

    enum ERRORS {
        globals_error = 1, cameras_error, lightning_error, textures_error,
        appearances_error, graph_error, file_not_found
    };

    enum node_i {
        GLOBALS, CAMERAS, LIGHTNING, OMNI, SPOT, PERSPECTIVE, ORTHO, TEXTURE, APPEARANCES,
        APPEARANCE, GRAPH, NODE, TRANSFORMS, TRANSLATE, ROTATE, SCALE, APPEARANCEREF, CHILDREN,
        RECTANGLE, TRIANGLE, CYLINDER, SPHERE, TORUS, NODEREF
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
        bool loadLightning(TiXmlElement* lightingElement);
        bool loadTextures(TiXmlElement* texturesElement);
        bool loadAppearances(TiXmlElement* appearancesElement);
        bool loadGraph(TiXmlElement* graphElement);

        // globals attributes
        string drawmode;
        string shading;
        string cullface;
        string cullorder;
        float *background;
        
        // lightning 
        bool doublesided;
        bool local;
        bool enabled;
        float *ambient;
        
    private:

        /* globals */
        //float[4] background;


        /* cameras */
        string initial; // id of the initial camera?
        //map<string, Camera*> camerasMap; // TODO : create Camera class (because it can be perspective or ortho)

        /* lightning */
        //map<string, Lightning*> lightningMap; // TODO : create Lightning class

        /* textures */
        //map<string, Texture*> texturesMap;
        
        

        /* appearances */
        map<string, Appearance*> appearancesMap;
        
        /* graph */
        Graph* sceneGraph;

    };
}


#endif /* defined(__LAIG___P1__YafParser__) */

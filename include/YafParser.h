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

namespace Parser {
    
	using namespace std;
    
	enum ERRORS {
		globals_error = 1, cameras_error, lightning_error, textures_error, 
		appearances_error, graph_error, file_not_found
	};
	enum node_i {
		GLOBALS, CAMERAS, LIGHTNING, OMNI, SPOT, PERSPECTIVE, ORTHO, TEXTURE, APPEARANCES,
		APPEARANCE, GRAPH, NODE, TRANSFORMS, TRANSLATE, ROTATE, SCALE, APPEARANCEREF, CHILDREN, RECTANGLE, TRIANGLE, CYLINDER, SPHERE, TORUS, NODEREF
	};
    
	class YafParser {
	
    public:
        
        YafParser();
        YafParser(string filename);
        ~YafParser(void);
       
        /* Initial method for parsing
         ** return 0 success, or above means error */
        int loadYaf(void);
        
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
        
        
        /* globals */
        //float[4] background = "1.0 1.0 1.0 1.0";
        string drawmode = "fill"; // predefined value = "fill"
        string shading = "flat"; // predefined value = "flat"
        string cullface = "none"; // predefined value = "none"
        string cullorder = "CW"; // predefined value = "CW"
        
        /* cameras */
        string initial = "0"; // id of the initial camera?
        //map<string, Camera*> camerasMap; // TODO : create Camera class (because it can be perspective or ortho)
        
        /* lightning */
        //map<string, Lightning*> lightningMap; // TODO : create Lightning class
        
        /* textures */
        //map<string, Texture*> texturesMap; // TODO : create Texture class

        /* appearances */
        //map<string, Appearance*> appearancesMap; // TODO : create Appearance class

        
        
        //map<string,Primitive*> PrimitivesMap;
        
        /* transforms */
        // map<string, Transform*> transformsMap; // TODO : create Transform class
        
	};
}


#endif /* defined(__LAIG___P1__YafParser__) */

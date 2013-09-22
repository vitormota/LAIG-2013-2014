//
//  YafParser.h
//  LAIG - P1
//

#ifndef __LAIG___P1__YafParser__
#define __LAIG___P1__YafParser__

#include <iostream>
#include <string>
#include "tinyxml.h"

namespace Parser {
    
	using namespace std;
    
	enum ERRORS {globals_error = 1, cameras_error, file_not_found};
	enum node_i {GLOBALS, CAMERAS, LIGHTNING, PERSPECTIVE, ORTHO};
    
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
        
	};
}


#endif /* defined(__LAIG___P1__YafParser__) */

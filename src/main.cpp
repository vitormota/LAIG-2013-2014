/*
--------------------------
----- LAIG TP 01 ---------
--------------------------

-> .yaf parser

 */

#include <string>
#ifdef __APPLE__
#include <GLUT/GLUT.h>
#include "CGFapplication.h"
#else
#include <GL/glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <GL/glui.h>
#endif

#include <string>
#include <iostream>
#include <exception>
#include "YafParser.h"
#if __unix
#include <CGF/CGFapplication.h>
#elif _WIN32
#include <CGFapplication.h>
#endif
#include "Scene.h"

using std::cout;
using std::exception;

using namespace std;

//------- DECLARATIONS 

//------- END DEC'S

int main(int argc, char* argv[]) {
    
	CGFapplication app = CGFapplication();
    
	try {
		app.init(&argc, argv);
        
        cout << "\n--> Loading .yaf file <--\n\n";
        
        Parser::YafParser* f = new Parser::YafParser();
        switch(f->loadYaf()){
            case Parser::file_not_found:
                cout << "File not found or ill formed xml.";
                break;
        }
        //cin.get();
        
        Graph* sceneGraph = f->getGraph();
        map<string, Appearance*> appearancesMap = f->getAppearances();
        map<string, Texture*> texturesMap = f->getTextures();
        map<string, Lightning*> lightningMap = f->getLights();
        
        Scene* newScene = new Scene();
        newScene->setGraph(sceneGraph);
        newScene->setAppearances(appearancesMap);
        newScene->setTextures(texturesMap);
        newScene->setLights(lightningMap);
        
		app.setScene(newScene);
		app.setInterface(new CGFinterface());
		
		app.run();
	}
	catch(GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	}
	catch(exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}
    
	return 0;
}
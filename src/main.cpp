/*
--------------------------
----- LAIG TP 01 ---------
--------------------------

-> .yaf parser

*/

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

#include <string>
#include <iostream>
#include <exception>
#include "YafParser.h"
#include "CGFapplication.h"
#include "Scene.h"

using std::cout;
using std::exception;

using namespace std;

//------- DECLARATIONS 

//------- END DEC'S

int main(int argc, char* argv[]) {
    
   cout << "\n--> Loading .yaf file <--\n\n";
    
    Parser::YafParser* f = new Parser::YafParser();
	switch(f->loadYaf()){
        case Parser::file_not_found:
            cout << "File not found or ill formed xml.";
            break;
	}
	//cin.get();
    
    Graph* sceneGraph = f->getGraph();
    
	CGFapplication app = CGFapplication();
    
	try {
		app.init(&argc, argv);
        
        Scene* newScene = new Scene();
        newScene->setGraph(sceneGraph);
        
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

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
    
	CGFapplication app = CGFapplication();
    
	try {
		app.init(&argc, argv);
        
		app.setScene(new Scene());
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
    
    cout << "\n--> Loading .yaf file <--\n\n";
    
    Parser::YafParser f = Parser::YafParser();
	switch(f.loadYaf()){
        case Parser::file_not_found:
            cout << "File not found or ill formed xml.";
            break;
	}
	cin.get();
    
	return 0;
}

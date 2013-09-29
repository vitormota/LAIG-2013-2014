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
#endif
#include "Scene.h"

using std::cout;
using std::exception;

using namespace std;

//------- DECLARATIONS 

//------- END DEC'S

int main(int argc, char* argv[]) {

    Scene *restaurant_scene = new Scene();
    
    cout << "\n--> Loading .yaf file <--\n\n";

    Parser::YafParser* f = new Parser::YafParser(restaurant_scene);
    
    switch (f->loadYaf()) {
        case Parser::file_not_found:
            cout << "File not found or ill formed xml.";
            break;
    }
    //cin.get();

    Graph* sceneGraph = f->getGraph();

    CGFapplication app = CGFapplication();

    try {
        app.init(&argc, argv);

        
        restaurant_scene->setGraph(sceneGraph);

        app.setScene(restaurant_scene);
        app.setInterface(new CGFinterface());

        app.run();
    } catch (GLexception& ex) {
        cout << "Erro: " << ex.what();
        return -1;
    } catch (exception& ex) {
        cout << "Erro inesperado: " << ex.what();
        return -1;
    }

    return 0;
}

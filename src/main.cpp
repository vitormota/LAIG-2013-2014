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
#include <gl/glut.h>
#endif
#ifdef __APPLE__
#include <gl/glui.h>
#else
#include <gl/glui.h>
#endif

#include <string>
#include <iostream>
#include "YafParser.h"

using namespace std;

//------- DECLARATIONS 

//------- END DEC'S


int main(void){

	cout << "\n--> Loading .yaf file <--\n\n";
    
	Parser::YafParser f = Parser::YafParser();
	switch(f.loadYaf()){
	case 3:
		cout << "File not found or ill formed xml.";
		break;
	}
	cin.get();
	return 0;
}

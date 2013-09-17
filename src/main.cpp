/*
	--------------------------
	----- LAIG TP 01 ---------
	--------------------------

	-> .yaf parser

*/

#include <string>
#include <iostream>
#include "tinyxml2.h"
#include <CGFinterface.h>

using namespace std;

//------- DECLARATIONS 
/* Initial method for parsing
** return 0 success, or above means error */
int startReading();
enum ERRORS { globals = 1, cameras};

//------- END DEC'S

int main (){
	
	cout << "Loading .yaf file\n";
	startReading();
	cin.get();
	return 0;
}

int startReading(){
	tinyxml2::XMLDocument doc;
	doc.LoadFile( "yaf.xml" );
	tinyxml2::XMLElement *e = doc.FirstChildElement();
	cout << e->Name();
	return 0;
}
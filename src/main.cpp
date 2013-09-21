/*
--------------------------
----- LAIG TP 01 ---------
--------------------------

-> .yaf parser

*/

#include <string>
#include <iostream>
#include "yaf_parser.h"

using namespace std;

//------- DECLARATIONS 

//------- END DEC'S



int main (){

	cout << "Loading .yaf file\n";
	yaf_parser::Parser f;
	switch(f.start()){
	case 3:
		cout << "File not found ir ill formed xml.";
		break;
	}
	cin.get();
	return 0;
}




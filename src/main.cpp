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
	f.start();
	cin.get();
	return 0;
}




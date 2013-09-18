#include "yaf_parser.h"

namespace string_parsing{
	int float_reader(const char *,float *);
} //string_parsing


namespace yaf_parser{

	int Parser::start(){
		tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument;
		if(doc->LoadFile( "yaf.xml" ) != tinyxml2::XML_SUCCESS){
			return file_nf;
		}
		tinyxml2::XMLElement *e = doc->FirstChildElement("yaf");
		tinyxml2::XMLElement *r = doc->RootElement();
		cout << e->Name() << endl;
		if(!globals(e)) return globals_error;
		cout << "Globals processed.\n";
		return 0;
	}

	bool Parser::globals(XMLElement *elem){
		XMLNode *node = elem->FirstChildElement("globals");
		if(node==NULL) return false;
		float bkgd[4];
		bool error = false;
		char *s = (char*) node->ToElement()->Attribute("background");
		cout <<  s
			<< endl;
		string_parsing::float_reader(s,bkgd);
		s= (char*) node->ToElement()->Attribute("drawmode");
		if(strcmp(s,"fill")!=0 && strcmp(s,"line")!=0 && strcmp(s,"point")!=0){
			cout << "Invalid drawmode..." << endl;
			error = true;
		}
		s= (char*) node->ToElement()->Attribute("shading");
		if(strcmp(s,"flat")!=0 && strcmp(s,"gouraud")!=0){
			cout << "Invalid shading..." << endl;
			error = true;
		}
		s= (char*) node->ToElement()->Attribute("cullface");
		if(strcmp(s,"none")!=0 && strcmp(s,"back")!=0 && strcmp(s,"front")!=0 && strcmp(s,"both")!=0){
			cout << "Invalid cullface..." << endl;
			error = true;
		}
		s= (char*) node->ToElement()->Attribute("cullorder");
		if(strcmp(s,"CCW")!=0 && strcmp(s,"CW")!=0){
			cout << "Invalid cullorder..." << endl;
			error = true;
		}
		if(error)return false;
		return true;
	}
}

/// <summary>
/// Attemps to read multiple floats from a given char *
/// and writes them to a float * one by one.
/// All floats must be seperated by a space " "
/// and it is not necessary to have a decimal part i.e. ".0"
/// </summary>
/// <param name="c">The char array (string) containing the text to parse</param>
/// <param name="p">The float array to store the numbers read</param>
/// <returns>0 on success<p>1 on invalid character read</returns>
int string_parsing::float_reader(const char *c,float *p){
	char f[15];
	char value;
	int i = 0,v=0,n=0;
	for(;;){
		value = c[i++];
		if(value >=48 && value <=57){
			//number
			f[v++]=value;
			continue;
		}
		if(value==46){
			//found decimal marker
			f[v++]=value;
			continue;
		}
		if(value==32){
			//space found
			f[v]=value;
			p[n++] = (float) atof(f);
			v = 0;
		}
		if(value == 0){
			//reached end
			f[v]=value;
			p[n] = (float) atof(f);
			return 0;
		}
		if(value < 48 && value != 32){
			//not a valid character
			return 1;
		}
	}
}
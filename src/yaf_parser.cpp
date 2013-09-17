#include "yaf_parser.h"

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
		char *s = (char*) node->ToElement()->Attribute("background");
		cout <<  s;
		return true;
	}
}
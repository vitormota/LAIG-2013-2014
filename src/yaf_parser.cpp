#include "yaf_parser.h"

namespace string_parsing{
	const int NO_ERROR=0,ERROR=1;
	int float_reader(const char *,float *);
} //string_parsing


namespace yaf_parser{

	const char node_NF[] = "No such node ";
	const char *node_names[10] = {"globals","cameras","lightning","perspective","ortho"};

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
		if(!cameras(e)) return cameras_error;
		cout << "Cameras processed.\n";
		return 0;
	}

	bool Parser::globals(XMLElement *elem){
		XMLNode *node = elem->FirstChildElement(node_names[GLOBALS]);
		if(node==NULL){
			cout << node_NF
				<< node_names[GLOBALS]
			<< endl;
			return false;
		}
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

	bool Parser::cameras(XMLElement *elem){
		XMLNode *node = elem->FirstChildElement(node_names[CAMERAS]);
		if(node==NULL){
			cout << 
				node_NF <<
				node_names[CAMERAS] <<
				endl;
			return false;
		}
		XMLNode *child = node->FirstChildElement();
		if(child==NULL){
			cout << node_NF << 
				node_names[PERSPECTIVE] << 
				"," << 
				node_names[ORTHO] << 
				endl;
			return false;
		}
		bool error = true;
		char *initial = (char*) node->ToElement()->Attribute("initial");
		if(initial==NULL){
			cout << "Initial camera not found, using first read."
				<< endl;
		}
		char *id;
		float near=0,far=0,angle=0,pos[3],target[3],
			left=0,right=0,top=0,bottom=0;
		while(child){
			id = (char*) child->ToElement()->Attribute("id");
			if(strcmp(child->ToElement()->Name(),node_names[PERSPECTIVE])==0){
				//perspective found
				if(!id ||
					child->ToElement()->QueryFloatAttribute("near",&near) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("far",&far) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("angle",&angle) != XML_NO_ERROR ||
					string_parsing::float_reader(child->ToElement()->Attribute("pos"),pos) != string_parsing::NO_ERROR ||
					string_parsing::float_reader(child->ToElement()->Attribute("target"),target) != string_parsing::NO_ERROR)
				{
					//bad perspective found
					cout <<  node_names[PERSPECTIVE] <<
						" id: " <<
						id <<
						" has invalid field(s), ignoring.\n";
				}else{
					cout << node_names[PERSPECTIVE] <<
						" id: " <<
						id <<
						", processed." <<
						endl;
					//pre-requesite, at least one so, flag off
					if(error) error = false;
				}
			}else if(strcmp(child->ToElement()->Name(),node_names[ORTHO])==0){
				//ortho found
				if(!id ||
					child->ToElement()->QueryFloatAttribute("near",&near) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("far",&far) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("left",&left) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("right",&right) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("top",&top) != XML_NO_ERROR ||
					child->ToElement()->QueryFloatAttribute("bottom",&bottom) != XML_NO_ERROR)
				{
					//bad ortho found
					cout <<  node_names[ORTHO] <<
						" id: " <<
						id <<
						" has invalid field(s), ignoring.\n";
				}else{
					cout << node_names[ORTHO] <<
						" id: " <<
						id <<
						", processed." <<
						endl;
					//pre-requesite, at least one so, flag off
					if(error) error = false;
				}
			}
			//next sibling camera
			child = child->NextSiblingElement();
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
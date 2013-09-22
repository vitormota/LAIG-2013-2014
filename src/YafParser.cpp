//
//  YafParser.cpp
//  LAIG - P1
//

#include "YafParser.h"


namespace StringParsing {

	const int NO_ERROR = 0, ERROR = 1;
	int FloatReader(const char *,float *);

} //StringParsing


namespace Parser {

	const char attribute_not_found[] = "No such attribute";
	const char element_not_found[] = "No such element";
	const char *node_names[10] = {"globals","cameras","lightning","perspective","ortho","texture"};

	YafParser::YafParser()
	{
		this->_filename = "yaf.xml";
	}

	YafParser::YafParser(string filename)
	{
		this->_filename = filename;
		loadYaf();
	}

	YafParser::~YafParser(void)
	{
		delete(doc);
	}

	int YafParser::loadYaf(void){

		// Read XML from file
		doc = new TiXmlDocument(_filename.c_str());

		bool loadOkay = doc->LoadFile();

		if (!loadOkay)
		{
			return file_not_found;
		}

		TiXmlElement* yafElement = doc->FirstChildElement("yaf");

		if (yafElement == NULL)
		{
			printf("Main yaf block element not found! Exiting!\n");
			exit(1);
		}

		//tinyxml2::XMLElement *r = doc->RootElement();
		//cout << e->Name() << endl;

		globalsElement = yafElement->FirstChildElement("globals");
		camerasElement = yafElement->FirstChildElement("cameras");
		lightingElement = yafElement->FirstChildElement("lighting");
		texturesElement = yafElement->FirstChildElement("textures");
		appearancesElement = yafElement->FirstChildElement("appearances");
		graphElement = yafElement->FirstChildElement("graph");

		if(!loadGlobals(globalsElement)) return globals_error;
		//make output readable
		cout << "----------------------\n";
		cout << "- globals processed. -\n";
		cout << "----------------------\n\n";
		if(!loadCameras(camerasElement)) return cameras_error;
		cout << "----------------------\n";
		cout << "- cameras processed. -\n";
		cout << "----------------------\n\n";
		if(!loadTextures(texturesElement)) return textures_error;
		cout << "-----------------------\n";
		cout << "- textures processed. -\n";
		cout << "-----------------------\n\n";

		return 0;
	}

	bool YafParser::loadGlobals(TiXmlElement* globalsElement){

		//XMLNode *node = elem->FirstChildElement(node_names[GLOBALS]);

		if(globalsElement == NULL){
			cout << element_not_found
				<< node_names[GLOBALS]
			<< endl;
			return false;
		}

		char *attributeStr;

		// background attribute
		float backgroundFloatValues[4];
		bool error = false;
		attributeStr = (char*) globalsElement->Attribute("background");

		//cout << attributeStr << endl;

		StringParsing::FloatReader(attributeStr, backgroundFloatValues);

		// drawmode attribute
		attributeStr = (char*) globalsElement->Attribute("drawmode");

		if(strcmp(attributeStr,"fill")!=0 && strcmp(attributeStr,"line")!=0 && strcmp(attributeStr,"point")!=0){
			cout << "Invalid drawmode..." << endl;
			error = true;
		}

		// shading attribute
		attributeStr = (char*) globalsElement->Attribute("shading");

		if(strcmp(attributeStr,"flat")!=0 && strcmp(attributeStr,"gouraud")!=0){
			cout << "Invalid shading..." << endl;
			error = true;
		}

		// cullface attribute
		attributeStr = (char*) globalsElement->Attribute("cullface");

		if(strcmp(attributeStr, "none")!=0 && strcmp(attributeStr,"back")!=0 && strcmp(attributeStr,"front")!=0 && strcmp(attributeStr,"both")!=0){
			cout << "Invalid cullface..." << endl;
			error = true;
		}

		// cullorder attribute
		attributeStr = (char*) globalsElement->Attribute("cullorder");
		if(strcmp(attributeStr,"CCW")!=0 && strcmp(attributeStr,"CW")!=0){
			cout << "Invalid cullorder..." << endl;
			error = true;
		}

		if(error)
		{return false;}
		else
		{return true;}
	}

	bool YafParser::loadCameras(TiXmlElement* camerasElement){

		//XMLNode *node = elem->FirstChildElement(node_names[CAMERAS]);

		if(camerasElement == NULL){
			cout <<
				element_not_found <<
				node_names[CAMERAS] <<
				endl;
			return false;
		}

		TiXmlElement *perspectiveElement = camerasElement->FirstChildElement();

		if(perspectiveElement == NULL){
			cout << element_not_found <<
				node_names[PERSPECTIVE] <<
				"," <<
				node_names[ORTHO] <<
				endl;
			return false;
		}

		char *initialElementStr = (char*) camerasElement->Attribute("initial");
		if(initialElementStr == NULL){
			cout << "Initial camera not found, using first read."
				<< endl;
		}

		// perspective element

		bool error = true;
		char *id;

		float near = 0, far = 0, angle = 0, pos[3], target[3], left = 0, right = 0, top = 0, bottom = 0;

		while(perspectiveElement){

			id = (char*) perspectiveElement->Attribute("id");

			//BUG ---->   if((char*) perspectiveElement->ToText() == node_names[PERSPECTIVE]){ ??
			if(strcmp(perspectiveElement->Value(),node_names[PERSPECTIVE])==0){

				//perspective found
				if(!id ||
					perspectiveElement->QueryFloatAttribute("near",&near) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("far",&far) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("angle",&angle) != TIXML_SUCCESS ||
					StringParsing::FloatReader(perspectiveElement->Attribute("pos"),pos) != StringParsing::NO_ERROR ||
					StringParsing::FloatReader(perspectiveElement->Attribute("target"),target) != StringParsing::NO_ERROR)
				{
					//bad perspective found
					cout << node_names[PERSPECTIVE] << " id: " << id << " has invalid field(s), ignoring.\n";
				}
				else
				{
					cout << node_names[PERSPECTIVE] <<
						" id: " << id << ", processed." << endl;
					//pre-requesite, at least one so, flag off
					if(error) error = false;
				}
			}else if(strcmp(perspectiveElement->Value(),node_names[ORTHO])==0){
				//ortho found
				if(!id ||
					perspectiveElement->QueryFloatAttribute("near",&near) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("far",&far) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("left",&left) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("right",&right) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("top",&top) != TIXML_SUCCESS ||
					perspectiveElement->QueryFloatAttribute("bottom",&bottom) != TIXML_SUCCESS)
				{
					//bad ortho found
					cout <<  node_names[ORTHO] <<
						" id: " <<
						id <<
						" has invalid field(s), ignoring.\n";
				}
				else{
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
			perspectiveElement = perspectiveElement->NextSiblingElement();
		}
		if(error)return false;
		cout << endl;
		return true;
	}

	bool YafParser::loadTextures(TiXmlElement *texturesElement){
		if(texturesElement == NULL){
			cout <<
				element_not_found <<
				node_names[TEXTURE] <<
				endl;
			return false;
		}
		int count = 0;
		char *id,*file;
		texturesElement = texturesElement->FirstChildElement();
		while(texturesElement){
			id = (char*) texturesElement->Attribute("id");
			file = (char*) texturesElement->Attribute("file");
			if(!id || !file){
				//Bad texture
				cout << node_names[TEXTURE] <<
					" id: " <<
					" has invalid field(s), ignoring.\n";
			}else{
				//valid texture
				//this id must be saved, for cross-reference
				//with an appearance with same id
				cout << node_names[TEXTURE] <<
					" id: " <<
					id <<
					", processed." <<
					endl;
				count ++;
			}
			//next texture
			texturesElement = texturesElement->NextSiblingElement();
		}
		//print how many where read
		cout << "Found " << 
			count <<
			" texture(s).\n\n";
		return true;
	}

	bool YafParser::loadAppearances(TiXmlElement *appearancesElement){

		return true;
	}
}

/// <summary>
/// Attemps to read multiple floats from a given char *
/// and writes them to a float * one by one.
/// All floats must be seperated by a space " "
/// and it is not necessary to have a decimal part i.e. ".0"
/// </summary>
/// <param name="text">The char array (string) containing the text to parse</param>
/// <param name="floatNumbers">The float array to store the numbers read</param>
/// <returns>0 on success<p>1 on invalid character read</returns>
int StringParsing::FloatReader(const char *text, float *floatNumbers) {
	char f[15];
	char value;
	int i = 0, v = 0, n = 0;

	for(;;){
		value = text[i++];
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
			floatNumbers[n++] = (float) atof(f);
			v = 0;
		}
		if(value == 0){
			//reached end
			f[v]=value;
			floatNumbers[n] = (float) atof(f);
			return 0;
		}
		if(value < 48 && value != 32){
			//not a valid character
			return 1;
		}
	}
}
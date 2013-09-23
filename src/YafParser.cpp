//
//  YafParser.cpp
//  LAIG - P1
//

#include "YafParser.h"


namespace StringParsing {

	const int ERROR = 0;
	int FloatReader(const char *,float *);

} //StringParsing


namespace Parser {

	const char attribute_not_found[] = "No such attribute";
	const char element_not_found[] = "No such element";
	const char *node_names[10] = {"globals","cameras","lightning","omni",
		"spot","perspective","ortho","texture", "appearance"};

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
		if(!loadLightning(lightingElement)) return lightning_error;
		cout << "------------------------\n";
		cout << "- lightning processed. -\n";
		cout << "------------------------\n\n";
		if(!loadTextures(texturesElement)) return textures_error;
		cout << "-----------------------\n";
		cout << "- textures processed. -\n";
		cout << "-----------------------\n\n";
		if(!loadAppearances(appearancesElement)) return appearances_error;
		cout << "-----------------------\n";
		cout << "- appearances processed. -\n";
		cout << "-----------------------\n\n";

		return 0;
	}

	bool YafParser::loadGlobals(TiXmlElement* globalsElement){

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
					StringParsing::FloatReader(perspectiveElement->Attribute("pos"),pos) != 3 ||
					StringParsing::FloatReader(perspectiveElement->Attribute("target"),target) != 3)
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

	bool YafParser::loadLightning(TiXmlElement *lightningElement){
		if(lightingElement == NULL){
			cout <<
				element_not_found <<
				node_names[LIGHTNING] <<
				endl;
			return false;
		}
		TiXmlElement *child = lightingElement->FirstChildElement();
		if(!child){
			cout << element_not_found <<
				node_names[OMNI] <<
				"," <<
				node_names[SPOT] <<
				endl;
			return false;
		}
		bool doublesided=false,local=false,enabled=false;
		float ambient[4];
		if(strcmp(lightingElement->Attribute("doublesided"),"true")){
			doublesided=true;
		}
		if(strcmp(lightingElement->Attribute("enabled"),"true")){
			enabled=true;
		}
		if(strcmp(lightingElement->Attribute("local"),"true")){
			local=true;
		}
		if(StringParsing::FloatReader(lightingElement->Attribute("ambient"),ambient)!=4){
			//error ambient attr does not have at least 4 values
			cout << "Bad ambient attribute\n";
		}
		char *id;
		bool enabled_child=false;
		float location[4],ambient_child[4],diffuse[4],specular[4],angle=0,exponent=0,direction[3];
		int count =0;
		while(child){
			bool error = false,spot=false;
			id = (char*) child->Attribute("id");
			if(!strcmp(child->Attribute("enabled"),"true")){
				enabled_child=true;
			}
			if(!id ||
				StringParsing::FloatReader(child->Attribute("location"),location) != 4 ||
				StringParsing::FloatReader(child->Attribute("ambient"),ambient_child) != 4 ||
				StringParsing::FloatReader(child->Attribute("diffuse"),diffuse) != 4 ||
				StringParsing::FloatReader(child->Attribute("specular"),specular) != 4)
			{
				//bad base attributes
				error = true;
			}
			char* s = (char*) child->Value();
			if(!error && !strcmp(child->Value(),node_names[SPOT])){
				//it is a spot camera
				//extra attr to parse
				spot = true;
				if(child->QueryFloatAttribute("angle",&angle) != TIXML_SUCCESS ||
					child->QueryFloatAttribute("exponent",&exponent) != TIXML_SUCCESS ||
					StringParsing::FloatReader(child->Attribute("direction"),direction)!=3)
				{
					//bad spot camera
					error = true;
				}
			}
			if(!error){
				//save camera
				cout << child->Value() << " id: " << id << " processed.\n";
				count ++;
			}else{
				cout <<  child->Value() <<
					" id: " <<
					id <<
					" has invalid field(s), ignoring.\n";
			}
			child = child->NextSiblingElement();
		}
		cout << "Found " <<
			count <<
			" light(s)\n\n";
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
		TiXmlElement* textureElement = texturesElement->FirstChildElement();

		while(textureElement){
			id = (char*) textureElement->Attribute("id");
			file = (char*) textureElement->Attribute("file");
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
			textureElement = textureElement->NextSiblingElement();
		}
		//print how many where read
		cout << "Found " << 
			count <<
			" texture(s).\n\n";
		return true;
	}

	bool YafParser::loadAppearances(TiXmlElement *appearancesElement){

		if(appearancesElement == NULL){
			cout <<
				element_not_found <<
				node_names[TEXTURE] <<
				endl;
			return false;
		}

		int count = 0;
		char *id, *textureref;
		float emissiveFloatValues[4];
		float ambientFloatValues[4];
		float diffuseFloatValues[4];
		float specularFloatValues[4];
		char *emissiveStr;
		char *ambientStr;
		char *diffuseStr;
		char *specularStr;
		char *shininessStr;

		/* Texturas: de forma a manter as texturas numa escala adequada, o mapeamento de coordenadas de vértices de polígonos (retângulo, triângulo ou outros, mas não em quádricas) sobre o sistema referencial das texturas deve respeitar a escala definida na textura. Por exemplo, se texlength_s=3 , significa que uma ocorrência da textura, em comprimento, deve cobrir com exatidão um polígono de comprimento 3 unidades; mas se texlength_t=0.4 , então deve cobrir um comprimento de 0.4 unidades. Aceita-se que posteriores utilizações de escalamentos sobre os objetos respetivos venham a invalidar esta regra. */

		float shininess, texlength_s, texlength_t;

		TiXmlElement* appearanceElement = appearancesElement->FirstChildElement();

		while(appearanceElement){
			id = (char*) appearanceElement->Attribute("id");
			emissiveStr = (char*) appearanceElement->Attribute("emissive");
			ambientStr = (char*) appearanceElement->Attribute("ambient");
			diffuseStr = (char*) appearanceElement->Attribute("diffuse");
			specularStr = (char*) appearanceElement->Attribute("specular");
			shininessStr = (char*) appearanceElement->Attribute("shininess");
			textureref = (char*) appearanceElement->Attribute("textureref");

			// id attribute

			if(!id){

				// invalid id
				cout << node_names[APPEARANCE] << " id: " << " has invalid field(s), ignoring.\n";
			}
			else{
				// valid id
				cout << node_names[APPEARANCE] << " id: " << id << ", processed." << endl;

			}


			// emissive attribute

			if(!emissiveStr)
			{

				// invalid emission
				cout << node_names[APPEARANCE] << " emission: " << " has invalid field(s), ignoring.\n";

			}
			else{

				// valid emission
				StringParsing::FloatReader(emissiveStr, emissiveFloatValues);
				cout << node_names[APPEARANCE] << " emission: " << emissiveStr << ", processed." << endl;

			}

			// ambient attribute

			if(!ambientStr)
			{

				// invalid ambient
				cout << node_names[APPEARANCE] << " ambient: " << " has invalid field(s), ignoring.\n";

			}
			else{

				// valid ambient
				StringParsing::FloatReader(ambientStr, ambientFloatValues);
				cout << node_names[APPEARANCE] << " ambient: " << ambientStr << ", processed." << endl;

			}

			// diffuse attribute

			if(!diffuseStr)
			{

				// invalid diffuse
				cout << node_names[APPEARANCE] << " diffuse: " << " has invalid field(s), ignoring.\n";

			}
			else{

				// valid diffuse
				StringParsing::FloatReader(diffuseStr, diffuseFloatValues);
				cout << node_names[APPEARANCE] << " diffuse: " << diffuseStr << ", processed." << endl;

			}

			// specular attribute

			if(!specularStr)
			{

				// invalid specular
				cout << node_names[APPEARANCE] << " specular: " << " has invalid field(s), ignoring.\n";

			}
			else{

				// valid specular
				StringParsing::FloatReader(specularStr, specularFloatValues);
				cout << node_names[APPEARANCE] << " specular: " << specularStr << ", processed." << endl;

			}

			// WORK IN PROGRESS

			// next appearance
			appearanceElement = appearanceElement->NextSiblingElement();
			count ++;
		}

		// print how many where read
		cout << "Found " << count << " appearance(s).\n\n";


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
/// <returns>0 on error<p>1+ on success meaning how many where read</returns>
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
			floatNumbers[n++] = (float) atof(f);
			return n;
		}
		if((value < 48 || value > 57) && value != 32){
			//not a valid character
			return ERROR;
		}
	}
}
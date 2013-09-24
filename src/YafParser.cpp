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
	const char *node_names[24] = {"globals","cameras","lightning","omni",
		"spot","perspective","ortho","texture", "appearances", "appearance", "graph", "node", "transforms", "translate", "rotate", "scale", "appearanceref", "children", "rectangle", "triangle", "cylinder", "sphere", "torus", "noderef"};
    
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
        if(!loadGraph(graphElement)) return graph_error;
		cout << "-----------------------\n";
		cout << "-   graph processed.  -\n";
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
			//char* s = (char*) child->Value();
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
    
    
    // TODO textureref, texlength_s e textlength_t sao atributos opcionais se for usada uma textura
    bool YafParser::loadAppearances(TiXmlElement *appearancesElement){
        
		if(appearancesElement == NULL){
			cout <<
            element_not_found <<
            node_names[TEXTURE] <<
            endl;
			return false;
		}
        
		int count = 0; // number of appearance elements
		char *id, *textureref;
		float emissive[4];
		float ambient[4];
		float diffuse[4];
		float specular[4];
		char *emissiveStr;
		char *ambientStr;
		char *diffuseStr;
		char *specularStr;
		char *shininessStr;
        char *texlength_sStr;
        char *texlength_tStr;
        
		/* Texturas: de forma a manter as texturas numa escala adequada, o mapeamento de coordenadas de vértices de polígonos (retângulo, triângulo ou outros, mas não em quádricas) sobre o sistema referencial das texturas deve respeitar a escala definida na textura. Por exemplo, se texlength_s=3 , significa que uma ocorrência da textura, em comprimento, deve cobrir com exatidão um polígono de comprimento 3 unidades; mas se texlength_t=0.4 , então deve cobrir um comprimento de 0.4 unidades. Aceita-se que posteriores utilizações de escalamentos sobre os objetos respetivos venham a invalidar esta regra. */
        
		float shininess[1], texlength_s[1], texlength_t[1];
        
		TiXmlElement* appearanceElement = appearancesElement->FirstChildElement();
        
        // check if there is at least one appearance element
        if(appearanceElement == NULL){
			cout << element_not_found <<
            node_names[APPEARANCES] <<
            "," <<
            node_names[APPEARANCE] <<
            endl;
			return false;
		}
        
		while(appearanceElement){
			id = (char*) appearanceElement->Attribute("id");
			emissiveStr = (char*) appearanceElement->Attribute("emissive");
			ambientStr = (char*) appearanceElement->Attribute("ambient");
			diffuseStr = (char*) appearanceElement->Attribute("diffuse");
			specularStr = (char*) appearanceElement->Attribute("specular");
			shininessStr = (char*) appearanceElement->Attribute("shininess");
			textureref = (char*) appearanceElement->Attribute("textureref");
            texlength_sStr = (char*) appearanceElement->Attribute("texlength_s");
            texlength_tStr = (char*) appearanceElement->Attribute("texlength_t");
            
            
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
            
			if(!emissiveStr || (StringParsing::FloatReader(emissiveStr, emissive) != 4))
			{
                
				// invalid emission
				cout << node_names[APPEARANCE] << " emissive: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid emission
				cout << node_names[APPEARANCE] << " emissive: " << emissiveStr << ", processed." << endl;
                
			}
            
			// ambient attribute
            
			if(!ambientStr || (StringParsing::FloatReader(ambientStr, ambient)) != 4)
			{
                
				// invalid ambient
				cout << node_names[APPEARANCE] << " ambient: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid ambient
				cout << node_names[APPEARANCE] << " ambient: " << ambientStr << ", processed." << endl;
                
			}
            
			// diffuse attribute
            
			if(!diffuseStr || (StringParsing::FloatReader(diffuseStr, diffuse)) != 4)
			{
                
				// invalid diffuse
				cout << node_names[APPEARANCE] << " diffuse: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid diffuse
				cout << node_names[APPEARANCE] << " diffuse: " << diffuseStr << ", processed." << endl;
                
			}
            
			// specular attribute
            
			if(!specularStr || (StringParsing::FloatReader(specularStr, specular)) != 4)
			{
                
				// invalid specular
				cout << node_names[APPEARANCE] << " specular: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid specular
				cout << node_names[APPEARANCE] << " specular: " << specularStr << ", processed." << endl;
                
			}
            
            // shininess attribute
            
            if(!shininessStr || (StringParsing::FloatReader(shininessStr, shininess)) != 1)
			{
                
				// invalid shininess
				cout << node_names[APPEARANCE] << " shininess: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid shininess
				cout << node_names[APPEARANCE] << " shininess: " << shininessStr << ", processed." << endl;
                
			}
            
            // textureref attribute
            
            if(!textureref){
                
				// invalid textureref
				cout << node_names[APPEARANCE] << " textureref: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid textureref
				cout << node_names[APPEARANCE] << " textureref: " << textureref << ", processed." << endl;
                
			}
            
            
            // texlength_s attribute
            
            if(!texlength_sStr || (StringParsing::FloatReader(texlength_sStr, texlength_s)) != 1)
			{
                
				// invalid texlength_s
				cout << node_names[APPEARANCE] << " texlength_s: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid texlength_s
				cout << node_names[APPEARANCE] << " texlength_s: " << texlength_sStr << ", processed." << endl;
                
			}
            
            // texlength_t attribute
            
            if(!texlength_tStr || (StringParsing::FloatReader(texlength_tStr, texlength_t)) != 1)
			{
                
				// invalid texlength_t
				cout << node_names[APPEARANCE] << " texlength_t: " << " has invalid field(s), ignoring.\n";
                
			}
			else{
                
				// valid texlength_t
				cout << node_names[APPEARANCE] << " texlength_t: " << texlength_tStr << ", processed." << endl;
                
			}
            
			// next appearance
			appearanceElement = appearanceElement->NextSiblingElement();
			count ++;
		}
        
		// print how many where read
		cout << "Found " << count << " appearance(s).\n\n";
        
		return true;
	}
    
    
    bool YafParser::loadGraph(TiXmlElement* graphElement)
    {
        if(graphElement == NULL){
			cout << element_not_found
            << node_names[GRAPH]
			<< endl;
			return false;
		}
        
        char *rootid;
        
        // rootid attribute
        rootid = (char*) graphElement->Attribute("rootid");
        
        if(!rootid){
            
            // invalid rootid
            cout << node_names[GRAPH] << " rootid: " << " has invalid field(s), ignoring.\n";
        }
        else{
            // valid rootid
            cout << node_names[GRAPH] << " rootid: " << rootid << ", processed." << endl;
            
        }
        
        int count = 0; // number of node elements
        
        TiXmlElement* nodeElement = graphElement->FirstChildElement();
        
        // check if there is at least one node element
        if(nodeElement == NULL){
			cout << element_not_found <<
            node_names[GRAPH] <<
            "," <<
            node_names[NODE] <<
            endl;
			return false;
		}
        
        
        while(nodeElement){
            
            char *node_id;
            
            // id attribute of the element node
            node_id = (char*) nodeElement->Attribute("id");
            
            if(!node_id){
                
                // invalid id
                cout << node_names[NODE] << " id: " << " has invalid field(s), ignoring.\n";
            }
            else{
                // valid id
                cout << node_names[NODE] << " id: " << node_id << ", processed." << endl;
                
            }
            
            // transforms element
            
            TiXmlElement* transformsElement = nodeElement->FirstChildElement("transforms");
            
            if(transformsElement == NULL){
                cout << element_not_found
                << node_names[TRANSFORMS]
                << endl;
                return false;
            }
            
            
            // check all transformations (translate, rotate or scale)
            
            TiXmlElement* transformationElement = transformsElement->FirstChildElement();
            
            
            while(transformationElement)
            {
                
                // if the element is "translate"
                if(strcmp(transformationElement->Value(), "translate") == 0)
                {
                    // to attribute
                    
                    float to[3];
                    char *toStr;
                    
                    toStr = (char*) transformationElement->Attribute("to");
                    
                    
                    if(!toStr || (StringParsing::FloatReader(toStr, to) != 3))
                    {
                        
                        // invalid to
                        cout << node_names[TRANSLATE] << " to: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid to
                        cout << node_names[TRANSLATE] << " to: " << toStr << ", processed." << endl;
                        
                    }
                    
                }
                // if the element is "rotate"
                else
                    if(strcmp(transformationElement->Value(), "rotate") == 0)
                    {
                        // axis attribute
                        
                        char *axis;
                        
                        axis = (char*) transformationElement->Attribute("axis");
                        
                        // the axis has to be "x, y or z"
                        if(!axis || (strcmp("x", axis) && strcmp("y", axis) && strcmp("x", axis)))
                        {
                            
                            // invalid axis
                            cout << node_names[ROTATE] << " axis: " << " has invalid field(s), ignoring.\n";
                            
                        }
                        else{
                            
                            // valid axis
                            cout << node_names[ROTATE] << " axis: " << axis << ", processed." << endl;
                            
                        }
                        
                        // angle attribute
                        
                        float angle[1];
                        char *angleStr;
                        
                        angleStr = (char*) transformationElement->Attribute("angle");
                        
                        if(!angleStr || (StringParsing::FloatReader(angleStr, angle)) != 1)
                        {
                            
                            // invalid angle
                            cout << node_names[ROTATE] << " angle: " << " has invalid field(s), ignoring.\n";
                            
                        }
                        else{
                            
                            // valid angle
                            cout << node_names[ROTATE] << " angle: " << angleStr << ", processed." << endl;
                            
                        }
                        
                    }
                // if the element is "scale"
                    else
                        if(strcmp(transformationElement->Value(), "scale") == 0)
                        {
                            
                            // factor attribute
                            
                            float factor[3];
                            char *factorStr;
                            
                            factorStr = (char*) transformationElement->Attribute("factor");
                            
                            
                            if(!factorStr || (StringParsing::FloatReader(factorStr, factor) != 3))
                            {
                                
                                // invalid factor
                                cout << node_names[SCALE] << " factor: " << " has invalid field(s), ignoring.\n";
                                
                            }
                            else{
                                
                                // valid factor
                                cout << node_names[SCALE] << " factor: " << factorStr << ", processed." << endl;
                                
                            }
                        }
                
                // next transformation
                transformationElement = transformationElement->NextSiblingElement();
                
            }
            
            // appearanceref element
            
            TiXmlElement* appearancerefElement = nodeElement->FirstChildElement("appearanceref");
            
            char *appearanceref_id;
            
            // id attribute of the element appearanceref
            
            appearanceref_id = (char*) appearancerefElement->Attribute("id");
            
            if(!appearanceref_id){
                
                // invalid appearanceref_id
                cout << node_names[APPEARANCEREF] << " id: " << " has invalid field(s), ignoring.\n";
            }
            else{
                // valid appearanceref_id
                cout << node_names[APPEARANCEREF] << " id: " << appearanceref_id << ", processed." << endl;
                
            }
            
            // children element
            
            TiXmlElement* childrenElement = nodeElement->FirstChildElement("children");
            
            if(childrenElement == NULL){
                cout << element_not_found
                << node_names[CHILDREN]
                << endl;
                return false;
            }
            
            
            // check all children (rectangle, triangle, cylinder, sphere, torus or noderef)
            
            TiXmlElement* childElement = childrenElement->FirstChildElement();
            
            
            while(childElement)
            {
                
                // if the element is "rectangle"
                if(strcmp(childElement->Value(), "rectangle") == 0)
                {
                    // xy1 attribute
                    
                    float xy1[2];
                    char *xy1Str;
                    
                    xy1Str = (char*) childElement->Attribute("xy1");
                    
                    if(!xy1Str || (StringParsing::FloatReader(xy1Str, xy1)) != 2)
                    {
                        
                        // invalid xy1
                        cout << node_names[RECTANGLE] << " xy1: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid xy1
                        cout << node_names[RECTANGLE] << " xy1: " << xy1Str << ", processed." << endl;
                        
                    }
                    
                    // xy2 attribute
                    
                    float xy2[2];
                    char *xy2Str;
                    
                    xy2Str = (char*) childElement->Attribute("xy2");
                    
                    if(!xy2Str || (StringParsing::FloatReader(xy2Str, xy2)) != 2)
                    {
                        
                        // invalid xy2
                        cout << node_names[RECTANGLE] << " xy2: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid xy2
                        cout << node_names[RECTANGLE] << " xy2: " << xy2Str << ", processed." << endl;
                        
                    }
                    
                }
                // if the element is "triangle"
                else
                if(strcmp(childElement->Value(), "triangle") == 0)
                {
                    // xyz1 attribute
                    
                    float xyz1[3];
                    char *xyz1Str;
                    
                    xyz1Str = (char*) childElement->Attribute("xyz1");
                    
                    if(!xyz1Str || (StringParsing::FloatReader(xyz1Str, xyz1)) != 3)
                    {
                        
                        // invalid xyz1
                        cout << node_names[TRIANGLE] << " xyz1: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid xyz1
                        cout << node_names[TRIANGLE] << " xyz1: " << xyz1Str << ", processed." << endl;
                        
                    }
                    
                    // xyz2 attribute
                    
                    float xyz2[3];
                    char *xyz2Str;
                    
                    xyz2Str = (char*) childElement->Attribute("xyz2");
                    
                    if(!xyz2Str || (StringParsing::FloatReader(xyz2Str, xyz2)) != 3)
                    {
                        
                        // invalid xyz2
                        cout << node_names[TRIANGLE] << " xyz2: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid xyz2
                        cout << node_names[TRIANGLE] << " xyz2: " << xyz2Str << ", processed." << endl;
                        
                    }
                    
                    // xyz3 attribute
                    
                    float xyz3[3];
                    char *xyz3Str;
                    
                    xyz3Str = (char*) childElement->Attribute("xyz3");
                    
                    if(!xyz3Str || (StringParsing::FloatReader(xyz3Str, xyz3)) != 3)
                    {
                        
                        // invalid xyz3
                        cout << node_names[TRIANGLE] << " xyz3: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid xyz3
                        cout << node_names[TRIANGLE] << " xyz3: " << xyz3Str << ", processed." << endl;
                        
                    }
                    
                }
                // if the element is "cylinder"
                else
                if(strcmp(childElement->Value(), "cylinder") == 0)
                {
                    // base attribute
                    
                    float base[1];
                    char *baseStr;
                    
                    baseStr = (char*) childElement->Attribute("base");
                    
                    if(!baseStr || (StringParsing::FloatReader(baseStr, base)) != 1)
                    {
                        
                        // invalid base
                        cout << node_names[CYLINDER] << " base: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid base
                        cout << node_names[CYLINDER] << " base: " << baseStr << ", processed." << endl;
                        
                    }
                    
                    // top attribute
                    
                    float top[1];
                    char *topStr;
                    
                    topStr = (char*) childElement->Attribute("top");
                    
                    if(!topStr || (StringParsing::FloatReader(topStr, top)) != 1)
                    {
                        
                        // invalid top
                        cout << node_names[CYLINDER] << " top: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid top
                        cout << node_names[CYLINDER] << " top: " << topStr << ", processed." << endl;
                        
                    }
                    
                    // height attribute
                    
                    float height[1];
                    char *heightStr;
                    
                    heightStr = (char*) childElement->Attribute("height");
                    
                    if(!heightStr || (StringParsing::FloatReader(heightStr, height)) != 1)
                    {
                        
                        // invalid height
                        cout << node_names[CYLINDER] << " height: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid height
                        cout << node_names[CYLINDER] << " height: " << heightStr << ", processed." << endl;
                        
                    }

                    // slices attribute
    
                    int slices = 0;
                    int retSlices;
                    
                    retSlices = childElement->QueryIntAttribute("slices", &slices);
                    
                    if(slices <= 0 || (retSlices != TIXML_SUCCESS))
                    {
                        
                        // invalid slices
                        cout << node_names[CYLINDER] << " slices: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid slices
                        cout << node_names[CYLINDER] << " slices: " << slices << ", processed." << endl;
                        
                    }
                    
                    // stacks attribute
                    
                    int stacks = 0;
                    int retStacks;
                    
                    retStacks = childElement->QueryIntAttribute("stacks", &stacks);
                    
                    if(slices <= 0 || (retStacks != TIXML_SUCCESS))
                    {
                        
                        // invalid stacks
                        cout << node_names[CYLINDER] << " stacks: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid stacks
                        cout << node_names[CYLINDER] << " stacks: " << stacks << ", processed." << endl;
                        
                    }
                    
                }
                else
                // if the element is "sphere"
                if(strcmp(childElement->Value(), "sphere") == 0)
                {
                    
                    // radius attribute
                    
                    float radius[1];
                    char *radiusStr;
                    
                    radiusStr = (char*) childElement->Attribute("radius");
                    
                    if(!radiusStr || (StringParsing::FloatReader(radiusStr, radius)) != 1)
                    {
                        
                        // invalid radius
                        cout << node_names[SPHERE] << " radius: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid radius
                        cout << node_names[SPHERE] << " radius: " << radiusStr << ", processed." << endl;
                        
                    }
                    
                    // slices attribute
                    
                    int slices = 0;
                    int retSlices;
                    
                    retSlices = childElement->QueryIntAttribute("slices", &slices);
                    
                    if(slices <= 0 || (retSlices != TIXML_SUCCESS))
                    {
                        
                        // invalid slices
                        cout << node_names[SPHERE] << " slices: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid slices
                        cout << node_names[SPHERE] << " slices: " << slices << ", processed." << endl;
                        
                    }
                    
                    // stacks attribute
                    
                    int stacks = 0;
                    int retStacks;
                    
                    retStacks = childElement->QueryIntAttribute("stacks", &stacks);
                    
                    if(slices <= 0 || (retStacks != TIXML_SUCCESS))
                    {
                        
                        // invalid stacks
                        cout << node_names[SPHERE] << " stacks: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid stacks
                        cout << node_names[SPHERE] << " stacks: " << stacks << ", processed." << endl;
                        
                    }


                    
                }
                else
                // if the element is "torus"
                if(strcmp(childElement->Value(), "torus") == 0)
                {
                    // inner attribute
                    
                    float inner[1];
                    char *innerStr;
                    
                    innerStr = (char*) childElement->Attribute("inner");
                    
                    if(!innerStr || (StringParsing::FloatReader(innerStr, inner)) != 1)
                    {
                        
                        // invalid inner
                        cout << node_names[TORUS] << " inner: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid inner
                        cout << node_names[TORUS] << " inner: " << innerStr << ", processed." << endl;
                        
                    }
                    
                    // outer attribute
                    
                    float outer[1];
                    char *outerStr;
                    
                    outerStr = (char*) childElement->Attribute("outer");
                    
                    if(!outerStr || (StringParsing::FloatReader(outerStr, outer)) != 1)
                    {
                        
                        // invalid outer
                        cout << node_names[TORUS] << " outer: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid outer
                        cout << node_names[TORUS] << " outer: " << outerStr << ", processed." << endl;
                        
                    }
                    
                    // slices attribute
                    
                    int slices = 0;
                    int retSlices;
                    
                    retSlices = childElement->QueryIntAttribute("slices", &slices);
                    
                    if(slices <= 0 || (retSlices != TIXML_SUCCESS))
                    {
                        
                        // invalid slices
                        cout << node_names[TORUS] << " slices: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid slices
                        cout << node_names[TORUS] << " slices: " << slices << ", processed." << endl;
                        
                    }
                    
                    // loops attribute
                    
                    int loops = 0;
                    int retLoops;
                    
                    retLoops = childElement->QueryIntAttribute("loops", &loops);
                    
                    if(loops <= 0 || (retLoops != TIXML_SUCCESS))
                    {
                        
                        // invalid loops
                        cout << node_names[TORUS] << " loops: " << " has invalid field(s), ignoring.\n";
                        
                    }
                    else{
                        
                        // valid loops
                        cout << node_names[TORUS] << " loops: " << loops << ", processed." << endl;
                        
                    }

                }
                else
                // if the element is "noderef"
                if(strcmp(childElement->Value(), "noderef") == 0)
                {
                    char *noderef_id;
                    
                    // id attribute of the element noderef
                    
                    noderef_id = (char*) childElement->Attribute("id");
                    
                    if(!noderef_id){
                        
                        // invalid noderef_id
                        cout << node_names[NODEREF] << " id: " << " has invalid field(s), ignoring.\n";
                    }
                    else{
                        // valid noderef_id
                        cout << node_names[NODEREF] << " id: " << noderef_id << ", processed." << endl;
                        
                    }
         
                }
                
                // next child
                childElement = childElement->NextSiblingElement();
                
            }
            
            
            
            // next node
			nodeElement = nodeElement->NextSiblingElement();
			count ++;
            
        }
        
        // print how many where read
		cout << "Found " << count << " node(s).\n\n";
        
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
//
//  YafParser.cpp
//  LAIG - P1
//

#include "YafParser.h"
#include "Scene.h"


namespace StringParsing {
    
    const int _ERROR = 0;
    int FloatReader(const char *, float *);
    
} //StringParsing


namespace Parser {
    
    const char attribute_not_found[] = "No such attribute";
    const char element_not_found[] = "No such element";
    const char *node_names[24] = {"globals", "cameras", "lighting", "omni",
        "spot", "perspective", "ortho", "texture", "appearances", "appearance",
        "graph", "node", "transforms", "translate", "rotate", "scale", "appearanceref",
        "children", "rectangle", "triangle", "cylinder", "sphere", "torus", "noderef"};
    
    YafParser::YafParser() {
        this->_filename = "yaf.xml";
    }
    
    YafParser::YafParser(string filename) {
        this->_filename = filename;
        loadYaf();
    }
    
    YafParser::~YafParser(void) {
        delete(doc);
    }
    
    int YafParser::loadYaf(void) {
        
        // Read XML from file
        doc = new TiXmlDocument(_filename.c_str());
        
        bool loadOkay = doc->LoadFile();
        
        if (!loadOkay) {
            return file_not_found;
        }
        
        TiXmlElement* yafElement = doc->FirstChildElement("yaf");
        
        if (yafElement == NULL) {
            printf("Main yaf block element not found! Exiting!\n");
            exit(1);
        }
        
        globalsElement = yafElement->FirstChildElement("globals");
        camerasElement = yafElement->FirstChildElement("cameras");
        lightingElement = yafElement->FirstChildElement("lighting");
        texturesElement = yafElement->FirstChildElement("textures");
        appearancesElement = yafElement->FirstChildElement("appearances");
        graphElement = yafElement->FirstChildElement("graph");
        
        if (!loadGlobals(globalsElement)) return globals_error;
        //make output readable
        cout << "---------------\n";
        cout << "- globals OK. -\n";
        cout << "---------------\n\n";
        if (!loadCameras(camerasElement)) return cameras_error;
        cout << "---------------\n";
        cout << "- cameras OK. -\n";
        cout << "---------------\n\n";
        if (!loadLighting(lightingElement)) return lighting_error;
        cout << "-----------------\n";
        cout << "- lighting OK. -\n";
        cout << "-----------------\n\n";
        if (!loadTextures(texturesElement)) return textures_error;
        cout << "----------------\n";
        cout << "- textures OK. -\n";
        cout << "----------------\n\n";
        if (!loadAppearances(appearancesElement)) return appearances_error;
        cout << "-------------------\n";
        cout << "- appearances OK. -\n";
        cout << "-------------------\n\n";
        if (!loadGraph(graphElement)) return graph_error;
        cout << "----------------\n";
        cout << "-   graph OK.  -\n";
        cout << "----------------\n\n";
        
        return 0;
    }
    
    bool YafParser::loadGlobals(TiXmlElement* globalsElement) {
        
        if (globalsElement == NULL) {
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
        
        StringParsing::FloatReader(attributeStr, backgroundFloatValues);
        memcpy(this->background, backgroundFloatValues, 4 * sizeof (float));
        
        // drawmode attribute
        attributeStr = (char*) globalsElement->Attribute("drawmode");
        
        if (strcmp(attributeStr, "fill") != 0 && strcmp(attributeStr, "line") != 0 && strcmp(attributeStr, "point") != 0) {
            cout << "Invalid drawmode..." << endl;
            error = true;
        } else {
            this->drawmode = attributeStr;
        }
        
        // shading attribute
        attributeStr = (char*) globalsElement->Attribute("shading");
        
        if (strcmp(attributeStr, "flat") != 0 && strcmp(attributeStr, "gouraud") != 0) {
            cout << "Invalid shading..." << endl;
            error = true;
        } else {
            this->shading = attributeStr;
        }
        
        // cullface attribute
        attributeStr = (char*) globalsElement->Attribute("cullface");
        
        if (strcmp(attributeStr, "none") != 0 && strcmp(attributeStr, "back") != 0 && strcmp(attributeStr, "front") != 0 && strcmp(attributeStr, "both") != 0) {
            cout << "Invalid cullface..." << endl;
            error = true;
        } else {
            this->cullface = attributeStr;
        }
        
        // cullorder attribute
        attributeStr = (char*) globalsElement->Attribute("cullorder");
        if (strcmp(attributeStr, "CCW") != 0 && strcmp(attributeStr, "CW") != 0) {
            cout << "Invalid cullorder..." << endl;
            error = true;
        } else {
            this->cullorder = attributeStr;
        }
        
        if (error) {
            return false;
        } else {
            return true;
        }
    }
    
    bool YafParser::loadCameras(TiXmlElement* camerasElement) {
        
        if (camerasElement == NULL) {
            cout <<
		    element_not_found <<
		    node_names[CAMERAS] <<
		    endl;
            return false;
        }
        
        TiXmlElement *cameraElement = camerasElement->FirstChildElement();
        
        if (cameraElement == NULL) {
            cout << element_not_found <<
		    node_names[PERSPECTIVE] <<
		    "," <<
		    node_names[ORTHO] <<
		    endl;
            return false;
        }
        
        char *initialElementStr = (char*) camerasElement->Attribute("initial");
        if (initialElementStr == NULL) {
            cout << "Initial camera not found, using first read."
		    << endl;
        }
        else{
            this->initial = initialElementStr;
        }
        
        // perspective element
        
        bool error = true;
        char *id;
        scene::Camera* newCamera;
        
        //TiXmlNode *x = camerasElement->FirstChild("perspective");
        
        while (cameraElement) {
            
            float near = 0, far = 0, angle = 0, pos[3], target[3], left = 0, right = 0, top = 0, bottom = 0;
            
            id = (char*) cameraElement->Attribute("id");
            //int number = perspectiveElement->QueryFloatAttribute("angle", &angle);
            //BUG ---->   if((char*) perspectiveElement->ToText() == node_names[PERSPECTIVE]){ ??
            //if (strcmp(perspectiveElement->Value(), node_names[PERSPECTIVE]) == 0) {
            if (cameraElement->QueryFloatAttribute("angle", &angle) == TIXML_SUCCESS) {
                //perspective found
                if (!id ||
                    cameraElement->QueryFloatAttribute("near", &near) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("far", &far) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("angle", &angle) != TIXML_SUCCESS ||
                    StringParsing::FloatReader(cameraElement->Attribute("pos"), pos) != 3 ||
                    StringParsing::FloatReader(cameraElement->Attribute("target"), target) != 3) {
                    //bad perspective found
                    cout << node_names[PERSPECTIVE] << " id: " << id << " has invalid field(s), FAIL.\n";
                } else {
                    cout << node_names[PERSPECTIVE] <<
                    " id: " << id << ", OK." << endl;
                    //pre-requesite, at least one so, flag off
                    if (error) error = false;
                    
                    // save perpective camera
                    newCamera = new scene::Camera(id, "perspective", near, far);
                    
                    newCamera->setAngle(angle);
                    newCamera->setPos(pos);
                    newCamera->setTarget(target);
                    
                }
                //} else if (strcmp(perspectiveElement->Value(), node_names[ORTHO]) == 0) {
            } else if (cameraElement->QueryFloatAttribute("left", &left) == TIXML_SUCCESS) {
                //ortho found
                if (!id ||
                    cameraElement->QueryFloatAttribute("near", &near) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("far", &far) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("left", &left) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("right", &right) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("top", &top) != TIXML_SUCCESS ||
                    cameraElement->QueryFloatAttribute("bottom", &bottom) != TIXML_SUCCESS) {
                    //bad ortho found
                    cout << node_names[ORTHO] <<
                    " id: " <<
                    id <<
                    " has invalid field(s), FAIL.\n";
                } else {
                    cout << node_names[ORTHO] <<
                    " id: " <<
                    id <<
                    ", OK." <<
                    endl;
                    //pre-requesite, at least one so, flag off
                    if (error) error = false;
                    
                    // save ortho camera
                    newCamera = new scene::Camera(id, "ortho", near, far);
                    
                    newCamera->setLeft(left);
                    newCamera->setRight(right);
                    newCamera->setTop(top);
                    newCamera->setBottom(bottom);
                }
            }
            
            // save camera
            camerasMap.insert(std::pair<string, scene::Camera*>(newCamera->getId(), newCamera));
            
            //next sibling camera
            cameraElement = cameraElement->NextSiblingElement();
        }
        if (error)return false;
        cout << endl;
        return true;
    }
    
    bool YafParser::loadLighting(TiXmlElement *lightingElement) {
        if (lightingElement == NULL) {
            cout <<
		    element_not_found <<
		    node_names[LIGHTING] <<
		    endl;
            return false;
        }
        TiXmlElement *lightElement = lightingElement->FirstChildElement();
        if (!lightElement) {
            cout << element_not_found <<
		    node_names[OMNI] <<
		    "," <<
		    node_names[SPOT] <<
		    endl;
            return false;
        }
        
        // initialize lighting map
        this->lightingMap = map<string, Lighting*>();
        
        
        // lighting element
        this->doublesided = false;
        this->local = false;
        this->enabled = false;
        
        float ambient[4];
        
        if (!strcmp(lightingElement->Attribute("doublesided"), "true")) {
            this->doublesided = true;
        }
        
        if (!strcmp(lightingElement->Attribute("enabled"), "true")) {
            this->enabled = true;
        }
        
        if (!strcmp(lightingElement->Attribute("local"), "true")) {
            this->local = true;
        }
        
        if (StringParsing::FloatReader(lightingElement->Attribute("ambient"), ambient) != 4) {
            //error ambient attr does not have at least 4 values
            cout << "Bad ambient attribute\n";
        } else {
            //memcpy(this->ambient, ambient, 4*sizeof(float));
            for(unsigned int i = 0; i < 4; i++)
            {
                this->ambient[i] = ambient[i];
            }
        }
        
        // omni/spot lights
        
        Lighting* newLighting = new Lighting();
        int count = 0;
        
        while (lightElement) {
            
            char *id;
            bool enabledLight = false;
            float location[3], ambientLight[4], diffuse[4], specular[4], angle = 0, exponent = 0, direction[3];
            
            for(unsigned int i = 0; i < 3; i++)
            {
                direction[i] = 0;
            }
            
            bool error = false, spot = false;
            id = (char*) lightElement->Attribute("id");
            
            if (!strcmp(lightElement->Attribute("enabled"), "true")) {
                enabledLight = true;
            }
            
            if (!id ||
                StringParsing::FloatReader(lightElement->Attribute("location"), location) != 3 ||
                StringParsing::FloatReader(lightElement->Attribute("ambient"), ambientLight) != 4 ||
                StringParsing::FloatReader(lightElement->Attribute("diffuse"), diffuse) != 4 ||
                StringParsing::FloatReader(lightElement->Attribute("specular"), specular) != 4) {
                //bad base attributes
                error = true;
            }
            
            char* type = (char*) lightElement->Value();
            
            if (!error && !strcmp(type, node_names[SPOT])) {
                
                //it is a spot camera
                //extra attr to parse
                spot = true;
                if (lightElement->QueryFloatAttribute("angle", &angle) != TIXML_SUCCESS ||
                    lightElement->QueryFloatAttribute("exponent", &exponent) != TIXML_SUCCESS ||
                    StringParsing::FloatReader(lightElement->Attribute("direction"), direction) != 3) {
                    //bad spot light
                    error = true;
                } else {
                    
                    // create spot light
                    newLighting = new Lighting("spot", id, enabledLight, location, ambientLight, diffuse, specular);
                    
                    newLighting->setAngle(angle);
                    newLighting->setExponent(exponent);
                    newLighting->setDirection(direction);
                }
            } else
                if (!error && !strcmp(type, node_names[OMNI])) {
                    //create omni light
                    
                    newLighting = new Lighting("omni", id, enabledLight, location, ambientLight, diffuse, specular);
                    
                    newLighting->setDirection(direction);
                }
            
            if (!error) {
                
                cout << type << " id: " << id << " OK.\n";
                
                //save light
                lightingMap.insert(std::pair<string, Lighting*>(newLighting->getId(), newLighting));
                
                count++;
                
            } else {
                cout << type <<
                " id: " <<
                id <<
                " has invalid field(s), FAIL.\n";
            }
            
            lightElement = lightElement->NextSiblingElement();
        }
        
        cout << "Found " <<
		count <<
		" light(s)\n\n";
        return true;
    }
    
    bool YafParser::loadTextures(TiXmlElement *texturesElement) {
        if (texturesElement == NULL) {
            cout <<
		    element_not_found <<
		    node_names[TEXTURE] <<
		    endl;
            return false;
        }
        int count = 0;
        char *id, *file;
        TiXmlElement* textureElement = texturesElement->FirstChildElement();
        
        // initialize textures map
        this->texturesMap = map<string, Texture*>();
        
        while (textureElement) {
            id = (char*) textureElement->Attribute("id");
            file = (char*) textureElement->Attribute("file");
            if (!id || !file) {
                //Bad texture
                cout << node_names[TEXTURE] <<
                " id: " <<
                " has invalid field(s), FAIL.\n";
            } else {
                //valid texture
                //this id must be saved, for cross-reference
                //with an appearance with same id
                cout << node_names[TEXTURE] <<
                " id: " <<
                id <<
                ", OK." <<
                endl;
                count++;
                
                // create and save texture
                Texture *newTexture = new Texture(id, file);
                
                texturesMap.insert(std::pair<string, Texture*>(newTexture->getId(), newTexture));
                
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
    
    bool YafParser::loadAppearances(TiXmlElement *appearancesElement) {
        
        if (appearancesElement == NULL) {
            cout <<
		    element_not_found <<
		    node_names[TEXTURE] <<
		    endl;
            return false;
        }
        
        // initialize appearances map
        this->appearancesMap = map<string, Appearance*>();
        
        int count = 0; // number of appearance elements
        char *id, *textureref;
        float emissive[4];
        float ambientApp[4];
        float diffuse[4];
        float specular[4];
        char *emissiveStr;
        char *ambientStr;
        char *diffuseStr;
        char *specularStr;
        char *shininessStr;
        char *texlength_sStr;
        char *texlength_tStr;
        
        float shininess = 0, texlength_s = 0, texlength_t = 0;
        
        TiXmlElement* appearanceElement = appearancesElement->FirstChildElement();
        
        // check if there is at least one appearance element
        if (appearanceElement == NULL) {
            cout << element_not_found <<
		    node_names[APPEARANCES] <<
		    "," <<
		    node_names[APPEARANCE] <<
		    endl;
            return false;
        }
        
        while (appearanceElement) {
            bool error = false;
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
            
            if (!id) {
                
                // invalid id
                cout << node_names[APPEARANCE] << " id: " << " has invalid field(s), FAIL.\n";
                error = true;
            } else {
                // valid id
                cout << node_names[APPEARANCE] << " id: " << id << ", OK." << endl;
                
            }
            
            
            // emissive attribute
            
            if (!emissiveStr || (StringParsing::FloatReader(emissiveStr, emissive) != 4)) {
                error = true;
                // invalid emission
                cout << node_names[APPEARANCE] << " emissive: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid emission
                cout << node_names[APPEARANCE] << " emissive: " << emissiveStr << ", OK." << endl;
                
            }
            
            // ambient attribute
            
            if (!ambientStr || (StringParsing::FloatReader(ambientStr, ambientApp)) != 4) {
                error = true;
                // invalid ambient
                cout << node_names[APPEARANCE] << " ambient: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid ambient
                cout << node_names[APPEARANCE] << " ambient: " << ambientStr << ", OK." << endl;
                
            }
            
            // diffuse attribute
            
            if (!diffuseStr || (StringParsing::FloatReader(diffuseStr, diffuse)) != 4) {
                error = true;
                // invalid diffuse
                cout << node_names[APPEARANCE] << " diffuse: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid diffuse
                cout << node_names[APPEARANCE] << " diffuse: " << diffuseStr << ", OK." << endl;
                
            }
            
            // specular attribute
            
            if (!specularStr || (StringParsing::FloatReader(specularStr, specular)) != 4) {
                error = true;
                // invalid specular
                cout << node_names[APPEARANCE] << " specular: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid specular
                cout << node_names[APPEARANCE] << " specular: " << specularStr << ", OK." << endl;
                
            }
            
            // shininess attribute
            
            // if (!shininessStr || (StringParsing::FloatReader(shininessStr, shininess)) != 1) {
            if (appearanceElement->QueryFloatAttribute("shininess", &shininess) != TIXML_SUCCESS) {
                error = true;
                // invalid shininess
                cout << node_names[APPEARANCE] << " shininess: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid shininess
                cout << node_names[APPEARANCE] << " shininess: " << shininessStr << ", OK." << endl;
                
            }
            
            // textureref attribute TODO: se não existir textura na appearance, textureref, texlength_s e texlength_s são opcionais
            
            bool noTexture = false;
            
            if (!textureref) {
                // invalid textureref
                //cout << node_names[APPEARANCE] << " textureref: " << " has invalid field(s), FAIL.\n";
                // TEXTURE DOESN't EXISTS
                noTexture = true;
                
            } else {
                
                // valid textureref
                cout << node_names[APPEARANCE] << " textureref: " << textureref << ", OK." << endl;
                
            }
            
            
            if(noTexture == false)
            {
            // texlength_s attribute
            
            int ret1 = appearanceElement->QueryFloatAttribute("texlength_s", &texlength_s);
            //if (!texlength_sStr || (StringParsing::FloatReader(texlength_sStr, texlength_s)) != 1) {
            if (ret1 != TIXML_SUCCESS) {
                // invalid texlength_s
                cout << node_names[APPEARANCE] << " texlength_s: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid texlength_s
                cout << node_names[APPEARANCE] << " texlength_s: " << texlength_sStr << ", OK." << endl;
                
            }
            
            // texlength_t attribute
            int ret2 = appearanceElement->QueryFloatAttribute("texlength_t", &texlength_t);
            //if (!texlength_tStr || (StringParsing::FloatReader(texlength_tStr, texlength_t)) != 1) {
            if (ret2 != TIXML_SUCCESS) {
                // invalid texlength_t
                cout << node_names[APPEARANCE] << " texlength_t: " << " has invalid field(s), FAIL.\n";
                
            } else {
                
                // valid texlength_t
                cout << node_names[APPEARANCE] << " texlength_t: " << texlength_tStr << ", OK." << endl;
                
            }
                
            }
            
            // next appearance
            appearanceElement = appearanceElement->NextSiblingElement();
            
            if (!error) {
                
                // valid block
                
                Appearance * newAppearance;
                
                // create and save appearance
                if (textureref) {
                    newAppearance = new Appearance(id, emissive, ambientApp, diffuse,
                                                   specular, shininess, textureref,
                                                   texlength_s, texlength_t);
                } else {
                    newAppearance = new Appearance(id, emissive, ambientApp, diffuse,
                                                   specular, shininess, "",
                                                   1.0, 1.0);
                }
                
                appearancesMap.insert(std::pair<string, Appearance*>(newAppearance->getId(), newAppearance));
                
                count++;
                
            }
            
            // print how many where read
            cout << "Found " << count << " appearance(s).\n\n";
            
        }
        
        return true;
    }
    
    bool YafParser::loadGraph(TiXmlElement * graphElement) {
        if (graphElement == NULL) {
            cout << element_not_found
		    << node_names[GRAPH]
		    << endl;
            return false;
        }
        
        char *rootid;
        
        // rootid attribute
        rootid = (char*) graphElement->Attribute("rootid");
        
        if (!rootid) {
            
            // invalid rootid
            cout << node_names[GRAPH] << " rootid: " << " has invalid field(s), FAIL.\n";
        } else {
            // valid rootid
            cout << node_names[GRAPH] << " rootid: " << rootid << ", OK." << endl;
            
            
            // create graph with the rootid
            this->sceneGraph = new Graph(rootid);
            
            
            if (this->sceneGraph->getRootId() == rootid) {
                cout << "Saving rootid OK." << endl;
            } else {
                cout << "Saving rootid FAILED." << endl;
            }
            
        }
        
        int count = 0; // number of node elements
        
        TiXmlElement* nodeElement = graphElement->FirstChildElement();
        
        // check if there is at least one node element
        if (nodeElement == NULL) {
            cout << element_not_found <<
		    node_names[GRAPH] <<
		    "," <<
		    node_names[NODE] <<
		    endl;
            return false;
        }
        
        
        while (nodeElement) {
            
            char *node_id;
            
            // id attribute of the element node
            node_id = (char*) nodeElement->Attribute("id");
            
            if (!node_id) {
                
                // invalid id
                cout << node_names[NODE] << " id: " << " has invalid field(s), FAIL.\n";
            } else {
                // valid id
                cout << node_names[NODE] << " id: " << node_id << ", OK." << endl;
                
            }
            
            // create node with the id
            Node* newNode = new Node(node_id);
            
            
            if (this->sceneGraph->getRootId() == rootid) {
                cout << "Saving rootid OK." << endl;
            } else {
                cout << "Saving rootid FAILED." << endl;
            }
            
            
            // transforms element
            
            TiXmlElement* transformsElement = nodeElement->FirstChildElement("transforms");
            
            if (transformsElement == NULL) {
                cout << element_not_found
                << node_names[TRANSFORMS]
                << endl;
                return false;
            }
            
            // check all transformations (translate, rotate or scale)
            
            TiXmlElement* transformationElement = transformsElement->FirstChildElement();
            
            glMatrixMode(GL_MODELVIEW);
            
            glPushMatrix();
            //glLoadIdentity();
            
            while (transformationElement) {
                
                // if the element is "translate"
                if (strcmp(transformationElement->Value(), "translate") == 0) {
                    // to attribute
                    
                    float to[3];
                    char *toStr;
                    
                    toStr = (char*) transformationElement->Attribute("to");
                    
                    
                    if (!toStr || (StringParsing::FloatReader(toStr, to) != 3)) {
                        
                        // invalid to
                        cout << node_names[TRANSLATE] << " to: " << " has invalid field(s), FAIL.\n";
                        
                    } else {
                        
                        // valid to
                        cout << node_names[TRANSLATE] << " to: " << toStr << ", OK." << endl;
                        
                        glTranslated(to[0], to[1], to[2]);
                        
                    }
                    
                }// if the element is "rotate"
                else
                    if (strcmp(transformationElement->Value(), "rotate") == 0) {
                        // axis attribute
                        
                        bool error = false;
                        
                        char* axis = (char*) transformationElement->Attribute("axis");
                        
                        // the axis has to be "x, y or z"
                        if (axis || (strcmp("x", axis) == 0) || (strcmp("y", axis) == 0) || (strcmp("z", axis) == 0)) {
                            
                            // valid axis
                            cout << node_names[ROTATE] << " axis: " << axis << ", OK." << endl;
                            
                            
                        } else {
                            
                            // invalid axis
                            cout << node_names[ROTATE] << " axis: " << " has invalid field(s), FAIL.\n";
                            
                            error = true;
                        }
                        
                        // angle attribute
                        
                        float angle[1];
                        char *angleStr;
                        
                        angleStr = (char*) transformationElement->Attribute("angle");
                        
                        if (!angleStr || (StringParsing::FloatReader(angleStr, angle)) != 1) {
                            
                            // invalid angle
                            cout << node_names[ROTATE] << " angle: " << " has invalid field(s), FAIL.\n";
                            error = true;
                            
                        } else {
                            
                            // valid angle
                            cout << node_names[ROTATE] << " angle: " << angleStr << ", OK." << endl;
                            
                        }
                        
                        if (!error) {
                            if (axis[0] == 'x') {
                                glRotated(angle[0], 1.0, 0.0, 0.0);
                            } else
                                
                                if (axis[0] == 'y') {
                                    glRotated(angle[0], 0.0, 1.0, 0.0);
                                } else
                                    if (axis[0] == 'z') {
                                        glRotated(angle[0], 0.0, 0.0, 1.0);
                                    }
                        }
                        
                        
                        
                    }// if the element is "scale"
                    else
                        if (strcmp(transformationElement->Value(), "scale") == 0) {
                            
                            // factor attribute
                            
                            float factor[3];
                            char *factorStr;
                            
                            factorStr = (char*) transformationElement->Attribute("factor");
                            
                            
                            if (!factorStr || (StringParsing::FloatReader(factorStr, factor) != 3)) {
                                
                                // invalid factor
                                cout << node_names[SCALE] << " factor: " << " has invalid field(s), FAIL.\n";
                                
                                
                            } else {
                                
                                // valid factor
                                cout << node_names[SCALE] << " factor: " << factorStr << ", OK." << endl;
                                
                                glScaled(factor[0], factor[1], factor[2]);
                                
                            }
                            
                            
                        }
                
                // next transformation
                transformationElement = transformationElement->NextSiblingElement();
                
            }
            
            // save transforms in the node
            glGetFloatv(GL_MODELVIEW_MATRIX, m);
            newNode->setMatrix(m);
            
            cout << "Saving transform matrix OK." << endl;
            
            glPopMatrix();
            
            // appearanceref element
            
            TiXmlElement* appearancerefElement = nodeElement->FirstChildElement("appearanceref");
            
            char *appearanceref_id;
            
            // id attribute of the element appearanceref
            if (appearancerefElement) {
                appearanceref_id = (char*) appearancerefElement->Attribute("id");
                if (!appearanceref_id) {
                    
                    // invalid appearanceref_id
                    cout << node_names[APPEARANCEREF] << " id: " << " has invalid field(s), FAIL.\n";
                } else {
                    // valid appearanceref_id
                    cout << node_names[APPEARANCEREF] << " id: " << appearanceref_id << ", OK." << endl;
                    
                    newNode->setAppearanceRef(appearanceref_id);
                    
                }
                
            }
            
            
            // children element
            
            vector<scene::Primitive*> primitives; // vector to save the primitives
            
            vector<string> childrenNodeRef; // vector to save the references to other nodes
            
            TiXmlElement* childrenElement = nodeElement->FirstChildElement("children");
            
            if (childrenElement == NULL) {
                cout << element_not_found
                << node_names[CHILDREN]
                << endl;
                return false;
            }
            
            
            // check all children (rectangle, triangle, cylinder, sphere, torus or noderef)
            
            TiXmlElement* childElement = childrenElement->FirstChildElement();
            
            
            while (childElement) {
                
                // if the element is "rectangle"
                if (strcmp(childElement->Value(), "rectangle") == 0) {
                    // xy1 attribute
                    
                    float xy1[2];
                    char *xy1Str;
                    
                    xy1Str = (char*) childElement->Attribute("xy1");
                    
                    if (!xy1Str || (StringParsing::FloatReader(xy1Str, xy1)) != 2) {
                        
                        // invalid xy1
                        cout << node_names[RECTANGLE] << " xy1: " << " has invalid field(s), FAIL.\n";
                        
                    } else {
                        
                        // valid xy1
                        cout << node_names[RECTANGLE] << " xy1: " << xy1Str << ", OK." << endl;
                        
                    }
                    
                    // xy2 attribute
                    
                    float xy2[2];
                    char *xy2Str;
                    
                    xy2Str = (char*) childElement->Attribute("xy2");
                    
                    if (!xy2Str || (StringParsing::FloatReader(xy2Str, xy2)) != 2) {
                        
                        // invalid xy2
                        cout << node_names[RECTANGLE] << " xy2: " << " has invalid field(s), FAIL.\n";
                        
                    } else {
                        
                        // valid xy2
                        cout << node_names[RECTANGLE] << " xy2: " << xy2Str << ", OK." << endl;
                        
                    }
                    
                    // create and save child/primitive
                    scene::Primitive* newPrimitive = new scene::Rectangle(node_id, xy1[0], xy1[1], xy2[0], xy2[1]);
                    
                    primitives.push_back(newPrimitive);
                    
                    cout << "Children saved: rectangle." << endl;
                    
                    
                }// if the element is "triangle"
                else
                    if (strcmp(childElement->Value(), "triangle") == 0) {
                        // xyz1 attribute
                        
                        float xyz1[3];
                        char *xyz1Str;
                        
                        xyz1Str = (char*) childElement->Attribute("xyz1");
                        
                        if (!xyz1Str || (StringParsing::FloatReader(xyz1Str, xyz1)) != 3) {
                            
                            // invalid xyz1
                            cout << node_names[TRIANGLE] << " xyz1: " << " has invalid field(s), FAIL.\n";
                            
                        } else {
                            
                            // valid xyz1
                            cout << node_names[TRIANGLE] << " xyz1: " << xyz1Str << ", OK." << endl;
                            
                        }
                        
                        // xyz2 attribute
                        
                        float xyz2[3];
                        char *xyz2Str;
                        
                        xyz2Str = (char*) childElement->Attribute("xyz2");
                        
                        if (!xyz2Str || (StringParsing::FloatReader(xyz2Str, xyz2)) != 3) {
                            
                            // invalid xyz2
                            cout << node_names[TRIANGLE] << " xyz2: " << " has invalid field(s), FAIL.\n";
                            
                        } else {
                            
                            // valid xyz2
                            cout << node_names[TRIANGLE] << " xyz2: " << xyz2Str << ", OK." << endl;
                            
                        }
                        
                        // xyz3 attribute
                        
                        float xyz3[3];
                        char *xyz3Str;
                        
                        xyz3Str = (char*) childElement->Attribute("xyz3");
                        
                        if (!xyz3Str || (StringParsing::FloatReader(xyz3Str, xyz3)) != 3) {
                            
                            // invalid xyz3
                            cout << node_names[TRIANGLE] << " xyz3: " << " has invalid field(s), FAIL.\n";
                            
                        } else {
                            
                            // valid xyz3
                            cout << node_names[TRIANGLE] << " xyz3: " << xyz3Str << ", OK." << endl;
                            
                        }
                        
                        // create and save child/primitive
                        scene::Primitive* newPrimitive = new scene::Triangle(node_id, xyz1[0], xyz1[1], xyz1[2], xyz2[0], xyz2[1], xyz2[2], xyz3[0], xyz3[1], xyz3[0]);
                        
                        primitives.push_back(newPrimitive);
                        
                        cout << "Children saved: triangle." << endl;
                        
                    }// if the element is "cylinder"
                    else
                        if (strcmp(childElement->Value(), "cylinder") == 0) {
                            // base attribute
                            
                            float base[1];
                            char *baseStr;
                            
                            baseStr = (char*) childElement->Attribute("base");
                            
                            if (!baseStr || (StringParsing::FloatReader(baseStr, base)) != 1) {
                                
                                // invalid base
                                cout << node_names[CYLINDER] << " base: " << " has invalid field(s), FAIL.\n";
                                
                            } else {
                                
                                // valid base
                                cout << node_names[CYLINDER] << " base: " << baseStr << ", OK." << endl;
                                
                            }
                            
                            // top attribute
                            
                            float top[1];
                            char *topStr;
                            
                            topStr = (char*) childElement->Attribute("top");
                            
                            if (!topStr || (StringParsing::FloatReader(topStr, top)) != 1) {
                                
                                // invalid top
                                cout << node_names[CYLINDER] << " top: " << " has invalid field(s), FAIL.\n";
                                
                            } else {
                                
                                // valid top
                                cout << node_names[CYLINDER] << " top: " << topStr << ", OK." << endl;
                                
                            }
                            
                            // height attribute
                            
                            float height[1];
                            char *heightStr;
                            
                            heightStr = (char*) childElement->Attribute("height");
                            
                            if (!heightStr || (StringParsing::FloatReader(heightStr, height)) != 1) {
                                
                                // invalid height
                                cout << node_names[CYLINDER] << " height: " << " has invalid field(s), FAIL.\n";
                                
                            } else {
                                
                                // valid height
                                cout << node_names[CYLINDER] << " height: " << heightStr << ", OK." << endl;
                                
                            }
                            
                            // slices attribute
                            
                            int slices = 0;
                            int retSlices;
                            
                            retSlices = childElement->QueryIntAttribute("slices", &slices);
                            
                            if (slices <= 0 || (retSlices != TIXML_SUCCESS)) {
                                
                                // invalid slices
                                cout << node_names[CYLINDER] << " slices: " << " has invalid field(s), FAIL.\n";
                                
                            } else {
                                
                                // valid slices
                                cout << node_names[CYLINDER] << " slices: " << slices << ", OK." << endl;
                                
                            }
                            
                            // stacks attribute
                            
                            int stacks = 0;
                            int retStacks;
                            
                            retStacks = childElement->QueryIntAttribute("stacks", &stacks);
                            
                            if (slices <= 0 || (retStacks != TIXML_SUCCESS)) {
                                
                                // invalid stacks
                                cout << node_names[CYLINDER] << " stacks: " << " has invalid field(s), FAIL.\n";
                                
                            } else {
                                
                                // valid stacks
                                cout << node_names[CYLINDER] << " stacks: " << stacks << ", OK." << endl;
                                
                            }
                            
                            // create and save child/primitive
                            scene::Primitive* newPrimitive =
                            new scene::Cylinder(node_id, base[0], top[0], height[0], slices, stacks);
                            
                            
                            primitives.push_back(newPrimitive);
                            
                            cout << "Children saved: cylinder." << endl;
                            
                        } else
                            // if the element is "sphere"
                            if (strcmp(childElement->Value(), "sphere") == 0) {
                                
                                // radius attribute
                                
                                float radius[1];
                                char *radiusStr;
                                
                                radiusStr = (char*) childElement->Attribute("radius");
                                
                                if (!radiusStr || (StringParsing::FloatReader(radiusStr, radius)) != 1) {
                                    
                                    // invalid radius
                                    cout << node_names[SPHERE] << " radius: " << " has invalid field(s), FAIL.\n";
                                    
                                } else {
                                    
                                    // valid radius
                                    cout << node_names[SPHERE] << " radius: " << radiusStr << ", OK." << endl;
                                    
                                }
                                
                                // slices attribute
                                
                                int slices = 0;
                                int retSlices;
                                
                                retSlices = childElement->QueryIntAttribute("slices", &slices);
                                
                                if (slices <= 0 || (retSlices != TIXML_SUCCESS)) {
                                    
                                    // invalid slices
                                    cout << node_names[SPHERE] << " slices: " << " has invalid field(s), FAIL.\n";
                                    
                                } else {
                                    
                                    // valid slices
                                    cout << node_names[SPHERE] << " slices: " << slices << ", OK." << endl;
                                    
                                }
                                
                                // stacks attribute
                                
                                int stacks = 0;
                                int retStacks;
                                
                                retStacks = childElement->QueryIntAttribute("stacks", &stacks);
                                
                                if (slices <= 0 || (retStacks != TIXML_SUCCESS)) {
                                    
                                    // invalid stacks
                                    cout << node_names[SPHERE] << " stacks: " << " has invalid field(s), FAIL.\n";
                                    
                                } else {
                                    
                                    // valid stacks
                                    cout << node_names[SPHERE] << " stacks: " << stacks << ", OK." << endl;
                                    
                                }
                                
                                // create and save child/primitive
                                scene::Primitive* newPrimitive =
                                new scene::Sphere(node_id, radius[0], slices, stacks);
                                
                                
                                primitives.push_back(newPrimitive);
                                
                                cout << "Children saved: sphere." << endl;
                                
                            } else
                                // if the element is "torus"
                                if (strcmp(childElement->Value(), "torus") == 0) {
                                    // inner attribute
                                    
                                    float inner[1];
                                    char *innerStr;
                                    
                                    innerStr = (char*) childElement->Attribute("inner");
                                    
                                    if (!innerStr || (StringParsing::FloatReader(innerStr, inner)) != 1) {
                                        
                                        // invalid inner
                                        cout << node_names[TORUS] << " inner: " << " has invalid field(s), FAIL.\n";
                                        
                                    } else {
                                        
                                        // valid inner
                                        cout << node_names[TORUS] << " inner: " << innerStr << ", OK." << endl;
                                        
                                    }
                                    
                                    // outer attribute
                                    
                                    float outer[1];
                                    char *outerStr;
                                    
                                    outerStr = (char*) childElement->Attribute("outer");
                                    
                                    if (!outerStr || (StringParsing::FloatReader(outerStr, outer)) != 1) {
                                        
                                        // invalid outer
                                        cout << node_names[TORUS] << " outer: " << " has invalid field(s), FAIL.\n";
                                        
                                    } else {
                                        
                                        // valid outer
                                        cout << node_names[TORUS] << " outer: " << outerStr << ", OK." << endl;
                                        
                                    }
                                    
                                    // slices attribute
                                    
                                    int slices = 0;
                                    int retSlices;
                                    
                                    retSlices = childElement->QueryIntAttribute("slices", &slices);
                                    
                                    if (slices <= 0 || (retSlices != TIXML_SUCCESS)) {
                                        
                                        // invalid slices
                                        cout << node_names[TORUS] << " slices: " << " has invalid field(s), FAIL.\n";
                                        
                                    } else {
                                        
                                        // valid slices
                                        cout << node_names[TORUS] << " slices: " << slices << ", OK." << endl;
                                        
                                    }
                                    
                                    // loops attribute
                                    
                                    int loops = 0;
                                    int retLoops;
                                    
                                    retLoops = childElement->QueryIntAttribute("loops", &loops);
                                    
                                    if (loops <= 0 || (retLoops != TIXML_SUCCESS)) {
                                        
                                        // invalid loops
                                        cout << node_names[TORUS] << " loops: " << " has invalid field(s), FAIL.\n";
                                        
                                    } else {
                                        
                                        // valid loops
                                        cout << node_names[TORUS] << " loops: " << loops << ", OK." << endl;
                                        
                                    }
                                    
                                    // create and save child/primitive
                                    scene::Primitive* newPrimitive =
                                    new scene::Torus(node_id, inner[0], outer[0], slices, loops);
                                    
                                    
                                    primitives.push_back(newPrimitive);
                                    
                                    cout << "Children saved: torus." << endl;
                                    
                                } else
                                    // if the element is "noderef"
                                    if (strcmp(childElement->Value(), "noderef") == 0) {
                                        char *noderef_id;
                                        
                                        // id attribute of the element noderef
                                        
                                        noderef_id = (char*) childElement->Attribute("id");
                                        
                                        if (!noderef_id) {
                                            
                                            // invalid noderef_id
                                            cout << node_names[NODEREF] << " id: " << " has invalid field(s), FAIL.\n";
                                        } else {
                                            // valid noderef_id
                                            cout << node_names[NODEREF] << " id: " << noderef_id << ", OK." << endl;
                                            
                                        }
                                        
                                        // save child/noderef
                                        childrenNodeRef.push_back(noderef_id);
                                        
                                        cout << "Children saved: noderef." << endl;
                                        
                                    }
                
                
                // next child
                childElement = childElement->NextSiblingElement();
                
            }
            
            // save children in the node
            newNode->setChildrenNodeRef(childrenNodeRef);
            newNode->setPrimitives(primitives);
            cout << "Saving children OK." << endl;
            
            // save node in the graph
            this->sceneGraph->addNode(newNode);
            
            // next node
            nodeElement = nodeElement->NextSiblingElement();
            count++;
            
        }
        
        // print how many where read
        cout << "Found " << count << " node(s).\n\n";
        
        return true;
        
    }
    
    Graph* YafParser::getGraph() {
        return this->sceneGraph;
    }
    
    map<string, Appearance*> YafParser::getAppearances() {
        return this->appearancesMap;
    }
    
    map<string, Texture*> YafParser::getTextures() {
        return this->texturesMap;
    }
    
    map<string, Lighting*> YafParser::getLights() {
        return this->lightingMap;
    }
    
    map<string,scene::Camera*> YafParser::getCameras()
    {
        return this->camerasMap;
    }
    
    string YafParser::getInitial()
    {
        return this->initial;
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
    bool negative = false;
    for (;;) {
        value = text[i++];
        if (value >= 48 && value <= 57) {
            //number
            f[v++] = value;
            continue;
        }
        if (value == 45) {
            f[v++] = value;
            //negative = true;
            continue;
        }
        if (value == 46) {
            //found decimal marker
            f[v++] = value;
            continue;
        }
        if (value == 32) {
            //space found
            f[v] = value;
            floatNumbers[n] = (float) atof(f);
            if (negative) {
                floatNumbers[n] = -1 * floatNumbers[n];
            }
            negative = false;
            n++;
            v = 0;
        }
        if (value == 0) {
            //reached end
            f[v] = value;
            floatNumbers[n] = (float) atof(f);
            if (negative) {
                floatNumbers[n] = -1 * floatNumbers[n];
            }
            n++;
            return n;
        }
        if ((value < 48 || value > 57) && value != 32) {
            //not a valid character
            return _ERROR;
        }
    }
}

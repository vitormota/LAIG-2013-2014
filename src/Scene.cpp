//
//  Scene.cpp
//  LAIG - P1
//

#include "Scene.h"

void Scene::init() {

    // Uncomment below to enable normalization of lighting normal vectors
    glEnable(GL_NORMALIZE);

    /* ------- Initialization of variables ------- */

    // --- globals attributes -------------------------------- BEGIN

    // background attribute
    glClearColor(this->background[0], this->background[1], this->background[2], this->background[3]);

    // drawmode attribute
    if (this->drawmode == "fill") {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (this->drawmode == "line") {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (this->drawmode == "point") {
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    // shading attribute
    if (this->shading == "flat") {
	glShadeModel(GL_FLAT); // Define the shade model
    } else if (this->shading == "gouraud") {
	glShadeModel(GL_SMOOTH); // Define the shade model
    }

    // cullface attribute
    glEnable(GL_CULL_FACE);

    if (this->cullface == "none") {
	glDisable(GL_CULL_FACE);
    } else if (this->cullface == "back") {
	glCullFace(GL_BACK);
    } else if (this->cullface == "front") {
	glCullFace(GL_FRONT);
    } else if (this->cullface == "both") {
	glCullFace(GL_FRONT_AND_BACK);
    }

    // cullorder attribute
    glEnable(GL_CULL_FACE);

    if (this->cullorder == "CCW") {
	glFrontFace(GL_CCW);
    } else if (this->cullorder == "CW") {
	glFrontFace(GL_CW);
    }

    // --- globals attributes -------------------------------- END

    // --- lighting attributes ------------------------------ BEGIN

    // doublesided attribute
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, this->doublesided);

    // local attribute
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, this->local);

    // enabled attribute
    if (this->enabled == true) {
	// enables lighting computations
	glEnable(GL_LIGHTING);
    } else {
	// disables lighting computations
	glDisable(GL_LIGHTING);
    }

//    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
//    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
//
//    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//    glEnable(GL_LIGHT0);

//    GLfloat light1_ambient[] = {0.2, 0.2, 0.2, 1.0};
//    GLfloat light1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light1_specular[] = {1.0, 1.0, 1.0, 1.0};
//    GLfloat light1_position[] = {-2.0, 2.0, 1.0, 1.0};
//    GLfloat spot_direction[] = {-1.0, -1.0, 0.0};
//
//    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
//    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
//    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
//    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
//    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
//    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
//
//    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);

    // ambient attribute
    if (this->ambient != NULL) {
	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambient);
    }

    // --- lighting attributes ------------------------------ END

    // create and save CGFLights

    map<string, Lighting*>::const_iterator itL = lightingMap.begin();

    CGFlight* newLight;

    GLenum light_id = GL_LIGHT0;

        for (itL = lightingMap.begin(); itL != lightingMap.end(); itL++) {
    	Lighting* light = (itL)->second;
    	newLight = new CGFlight(light_id, light->getLocation());
    	newLight->setAmbient(light->getAmbient());
    	newLight->setDiffuse(light->getDiffuse());
    	newLight->setSpecular(light->getSpecular());
    
    	if (light->getType() == "spot") {
    	    newLight->setAngle(light->getAngle());
    	    glLightfv(light_id, GL_SPOT_DIRECTION, light->getDirection());
    	    glLightf(light_id, GL_SPOT_EXPONENT, light->getExponent());
    	}
    
    	if (light->isEnabled()) {
    	    newLight->enable();
    	} else {
    	    newLight->disable();
    	}
    
    	// save light
    	lights.push_back(newLight);
    
    	light_id++;
    
        }

    // create and save CGFappearances

    map<string, Appearance*>::const_iterator itA = appearancesMap.begin();

    CGFappearance* newAppearance;

    for (itA = appearancesMap.begin(); itA != appearancesMap.end(); itA++) {
	Appearance* appearance = (itA)->second;
	newAppearance = new CGFappearance(appearance->getAmbient(), appearance->getDiffuse(), appearance->getSpecular(), appearance->getShininess());

	// emissive attribute of the CGFappearance
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, appearance->getEmissive());

	// TODO : texlength_s and texlength_t

	// find the texture with the textureref
	string textureref = appearance->getTextureref();

	if (!textureref.empty()) // check if there is a textureref to apply
	{
	    Texture* textureFound = new Texture();
	    map<string, Texture*>::const_iterator itTex = texturesMap.find(textureref);

	    if (itTex == texturesMap.end()) {
		// texture not found
		cout << "Texture with the textureref '" << textureref << "' not found" << endl;

	    } else {
		// texture found
		textureFound = itTex->second;

		// sets texture's wrap
		newAppearance->setTextureWrap(GL_CLAMP, GL_CLAMP);

		// set texture to appearance
		newAppearance->setTexture(textureFound->getFile());

	    }
	}

	// save CGFappearance
	appearances.insert(std::pair<string, CGFappearance*>(appearance->getId(), newAppearance));

    }

    // ------- Initialization of variables ------- END

}

void Scene::display() {

    // ---- BEGIN Background, camera and axis setup
    // Clear image and depth buffer everytime we update the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Model-View matrix as identity
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply transformations corresponding to the camera position relative to the origin
    CGFscene::activeCamera->applyView();

    // Uncomment below to enable normalization of lighting normal vectors
    glEnable(GL_NORMALIZE);

    // Draw axis
    axis.draw();

    // ---- END Background, camera and axis setup

    // ---- BEGIN Primitive drawing section


    // draw lights

    vector<CGFlight*>::const_iterator itL = lights.begin();

    for (itL = lights.begin(); itL != lights.end(); itL++) {
	(*itL)->draw();
	(*itL)->enable();
    }

    processGraph();

    // ---- END Primitive drawing section

    // We have been drawing in a memory area that is not visible - the back buffer,
    // while the graphics card is showing the contents of another buffer - the front buffer
    // glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
    glutSwapBuffers();
}

void Scene::processGraph() {

    // process graph

    string rootid = sceneGraph->getRootId();

    glPushMatrix();
    processNode(rootid);
    glPopMatrix();
}

void Scene::processNode(string id) {

    // IR BUSCAR NÓ DE ROOT/ACTUAL (com o id = id)
    Node* currentNode = sceneGraph->getNodeById(id);

    if (currentNode == NULL) {
	cout << "Invalid yaf??? The node with the id '" << id << "' doesn't exist?" << endl;
    } else {

	// 
	glMultMatrixf(currentNode->getMatrix());

	// search appearance
	string appearanceref = currentNode->getAppearanceRef();


	if (appearancesMap.find(appearanceref) != appearancesMap.end()) // check if there is a appearanceref to apply
	{
	    // apply appearance
	    appearances[appearanceref]->apply();
	}

	// Draw all the primitives of the current node
	vector<scene::Primitive*> primitives = currentNode->getPrimitives();

	vector<scene::Primitive*>::const_iterator itP;

	for (itP = primitives.begin(); itP != primitives.end(); itP++) {
	    (*itP)->draw();
	}

	// CHAMAR ESTA FUNÇÃO ATÉ PERCORRER TODOS OS NÓS REFERENCIADOS NESTE NÓ
	vector<string> childrenNodeRef = currentNode->getChildrenNodeRef();

	vector<string>::const_iterator itRef;

	for (itRef = childrenNodeRef.begin(); itRef != childrenNodeRef.end(); itRef++) {
	    string childId = (*itRef);
	    glPushMatrix();
	    processNode(childId);
	    glPopMatrix();
	}

    }
}

Scene::~Scene() {

}

void Scene::setGraph(Graph* sceneGraph) {
    this->sceneGraph = sceneGraph;
}

void Scene::setAppearances(map<string, Appearance*> appearancesMap) {
    this->appearancesMap = map<string, Appearance*>();
    this->appearancesMap.insert(appearancesMap.begin(), appearancesMap.end());
}

void Scene::setTextures(map<string, Texture*> texturesMap) {
    this->texturesMap = map<string, Texture*>();
    this->texturesMap.insert(texturesMap.begin(), texturesMap.end());
}

void Scene::setLights(map<string, Lighting*> lightingMap) {
    this->lightingMap = map<string, Lighting*>();
    this->lightingMap.insert(lightingMap.begin(), lightingMap.end());
}

void Scene::setBackground(float* background) {
    memcpy(this->background, background, 4 * sizeof (float));
}

void Scene::setDrawmode(string drawmode) {
    this->drawmode = drawmode;
}

void Scene::setShading(string shading) {
    this->shading = shading;
}

void Scene::setCullface(string cullface) {
    this->cullface = cullface;
}

void Scene::setCullorder(string cullorder) {
    this->cullorder = cullorder;
}

void Scene::setDoublesided(bool doublesided) {
    this->doublesided = doublesided;
}

void Scene::setLocal(bool local) {
    this->local = local;
}

void Scene::setEnabled(bool enabled) {
    this->enabled = enabled;
}

void Scene::setAmbient(float* ambient) {
    memcpy(this->ambient, ambient, 4 * sizeof (float));
}

map<string, Appearance*> Scene::getAppearances() {
    return this->appearancesMap;
}

map<string, Texture*> Scene::getTextures() {
    return this->texturesMap;
}

map<string, Lighting*> Scene::getLights() {
    return this->lightingMap;
}

Graph* Scene::getGraph() {
    return this->sceneGraph;
}

float* Scene::getBackground() {
    return this->background;
}

string Scene::getDrawmode() {
    return this->drawmode;
}

string Scene::getShading() {
    return this->shading;
}

string Scene::getCullface() {
    return this->cullface;
}

string Scene::getCullorder() {
    return this->cullorder;
}

bool Scene::getDoublesided() {
    return this->doublesided;
}

bool Scene::getLocal() {
    return this->local;
}

bool Scene::getEnabled() {
    return this->enabled;
}

float* Scene::getAmbient() {
    return this->ambient;
}


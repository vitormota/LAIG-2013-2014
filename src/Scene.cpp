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
		this->mode = 0;
	} else if (this->drawmode == "line") {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		this->mode = 1;
	} else if (this->drawmode == "point") {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		this->mode = 2;
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
		// disables lighting computations*/
		glDisable(GL_LIGHTING);
	}

	// ambient attribute
	// Define ambient light (do not confuse with ambient component of individual lights)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, this->ambient);

	// --- lighting attributes ------------------------------ END

	// Initialization of light variables
	this->light0Exists = false;
	this->light1Exists = false;
	this->light2Exists = false;
	this->light3Exists = false;
	this->light4Exists = false;
	this->light5Exists = false;
	this->light6Exists = false;
	this->light7Exists = false;

	light_0 = new int;
	light_1 = new int;
	light_2 = new int;
	light_3 = new int;
	light_4 = new int;
	light_5 = new int;
	light_6 = new int;
	light_7 = new int;

	*light_0 = 1;
	*light_1 = 1;
	*light_2 = 1;
	*light_3 = 1;
	*light_4 = 1;
	*light_5 = 1;
	*light_6 = 1;
	*light_7 = 1;

	// create and save lights

	this->lightsId = vector<string>();
	map<string, Lighting*>::const_iterator itL = lightingMap.begin();

	GLenum light_id = GL_LIGHT0;

	unsigned int lightCount = 0;

	for (itL = lightingMap.begin(); itL != lightingMap.end(); itL++) {

		// OpenGL allows a maximum of 8 light sources in a scene at once
		if (lightCount == 0) {
			light_id = GL_LIGHT0;
			this->light0Exists = true;
		} else
			if (lightCount == 1) {
				light_id = GL_LIGHT1;
				this->light1Exists = true;
			} else
				if (lightCount == 2) {
					light_id = GL_LIGHT2;
					this->light2Exists = true;
				} else
					if (lightCount == 3) {
						light_id = GL_LIGHT3;
						this->light3Exists = true;
					} else
						if (lightCount == 4) {
							light_id = GL_LIGHT4;
							this->light4Exists = true;
						} else
							if (lightCount == 5) {
								light_id = GL_LIGHT5;
								this->light5Exists = true;

							} else
								if (lightCount == 6) {
									light_id = GL_LIGHT6;
									this->light6Exists = true;

								} else
									if (lightCount == 7) {
										light_id = GL_LIGHT7;
										this->light7Exists = true;

									}

									Lighting* light = (itL)->second;

									this->lightsId.push_back(light->getId());

									// light values
									glLightfv(light_id, GL_POSITION, light->getLocation()); // position
									glLightfv(light_id, GL_AMBIENT, light->getAmbient()); // ambient
									glLightfv(light_id, GL_DIFFUSE, light->getDiffuse()); // diffuse
									glLightfv(light_id, GL_SPECULAR, light->getSpecular()); // specular

									if (light->getType() == "spot") {
										glLightf(light_id, GL_SPOT_CUTOFF, light->getAngle()); // angle
										glLightfv(light_id, GL_SPOT_DIRECTION, light->getDirection()); // direction
										glLightf(light_id, GL_SPOT_EXPONENT, light->getExponent()); // exponent
									}

									if (light->isEnabled()) {
										glEnable(light_id);
									} else {
										glDisable(light_id);

										// disable the lights with enabled = false
										if(light_id == GL_LIGHT0)
										{
											*this->light_0 = 0;
										}
										else
											if(light_id == GL_LIGHT1)
											{
												*this->light_1 = 0;
											}
											else
												if(light_id == GL_LIGHT2)
												{
													*this->light_2 = 0;
												}
												else
													if(light_id == GL_LIGHT3)
													{
														*this->light_3 = 0;
													}
													else
														if(light_id == GL_LIGHT4)
														{
															*this->light_4 = 0;
														}
														else
															if(light_id == GL_LIGHT5)
															{
																*this->light_5 = 0;
															}
															else
																if(light_id == GL_LIGHT6)
																{
																	*this->light_6 = 0;
																}
																else
																	if(light_id == GL_LIGHT7)
																	{
																		*this->light_7 = 0;
																	}
									}

									lightCount++;

	}

	// create and save CGFappearances

	map<string, Appearance*>::const_iterator itA = appearancesMap.begin();

	CGFappearance* newAppearance;

	for (itA = appearancesMap.begin(); itA != appearancesMap.end(); itA++) {
		Appearance* appearance = (itA)->second;
		newAppearance = new CGFappearance(appearance->getAmbient(), appearance->getDiffuse(), appearance->getSpecular(), appearance->getShininess());

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
				newAppearance->setTextureWrap(GL_REPEAT, GL_REPEAT);


				// set texture to appearance
				newAppearance->setTexture(textureFound->getFile());

			}
		}

		// save CGFappearance
		appearances.insert(std::pair<string, CGFappearance*>(appearance->getId(), newAppearance));

	}

	// initialize cameras id's

	unsigned int id = 1;

	map<string, Camera*>::const_iterator itC;
	Camera* currentCamera;

	camerasId["activeCGFcamera0"] = 0; // default camera

	for (itC = camerasMap.begin(); itC != camerasMap.end(); itC++) {
		currentCamera = (itC)->second;
		camerasId[currentCamera->getId()] = id; // assotiate camera with the id (unsigned int) with the id (string) attribute
		id++;
	}

	if(this->initial == "")
	{
		this->currentCameraId = "activeCGFcamera0"; // default camera
	}
	else
	{
		this->currentCameraId = this->initial; // set the id of the current camera to the initial camera id
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

	// change to the current camera
	this->cameraAspect = CGFapplication::xy_aspect;
	changeCamera(this->currentCameraId);

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup

	// ---- BEGIN Primitive drawing section

	// enable/disable lights
	if (light0Exists && (*this->light_0 == 1)){
		glEnable(GL_LIGHT0);
	} else {
		glDisable(GL_LIGHT0);
	}

	if (light1Exists && (*this->light_1 == 1)) {
		glEnable(GL_LIGHT1);
	} else {
		glDisable(GL_LIGHT1);
	}

	if (light2Exists && (*this->light_2 == 1)){
		glEnable(GL_LIGHT2);
	} else {
		glDisable(GL_LIGHT2);
	}

	if (light3Exists && (*this->light_3 == 1)) {
		glEnable(GL_LIGHT3);
	} else {
		glDisable(GL_LIGHT3);
	}

	if (light4Exists && (*this->light_4 == 1)) {
		glEnable(GL_LIGHT4);
	} else {
		glDisable(GL_LIGHT4);
	}

	if (light5Exists && (*this->light_5 == 1)) {
		glEnable(GL_LIGHT5);
	} else {
		glDisable(GL_LIGHT5);
	}

	if (light6Exists && (*this->light_6 == 1)) {
		glEnable(GL_LIGHT6);
	} else {
		glDisable(GL_LIGHT6);
	}

	if (light7Exists && (*this->light_7 == 1)) {
		glEnable(GL_LIGHT7);
	} else {
		glDisable(GL_LIGHT7);
	}

	// Process all the nodes of the graph (depth-first search)
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
	this->current_list_index = 0;

	glPushMatrix();
	processNode(rootid);
	glPopMatrix();
}

void Scene::processNode(string id) {

	bool pop = false;
	//----> NEW (TP02-Display Lists)
	bool display_list,created=false;
	//----> END NEW

	// Search current node (with id = id)
	Node* currentNode = sceneGraph->getNodeById(id);
	display_list = currentNode->use_list;

	if (currentNode == NULL) {
		cout << "Invalid yaf??? The node with the id '" << id << "' doesn't exist?" << endl;
	} else {

		// 
		glMultMatrixf(currentNode->getMatrix());

		// set drawing mode
		if (mode == 0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // fill
		} else if (mode == 1) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // line
		} else if (mode == 2) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // point
		}
		// search appearance
		string appearanceref = currentNode->getAppearanceRef();

		if (appearancesMap.find(appearanceref) != appearancesMap.end()) // check if there is a appearanceref to apply
		{
			//new appearance for the stack
			pop = true;
			// apply appearance
			glMaterialfv(GL_FRONT, GL_EMISSION, appearancesMap[appearanceref]->getEmissive()); // emissive
			appearances[appearanceref]->apply();
			app_stack.push(appearances[appearanceref]);
			app_refStack.push(appearanceref);
			txt_s = appearancesMap[appearanceref]->getTexlength_s();
			txt_t = appearancesMap[appearanceref]->getTexlength_t();
		}
		//----> NEW (TP02-Display Lists)
		if(!display_list || (display_list && currentNode->the_object==0x0)){
			//if the node does not use a list OR 
			//uses one but it is not defined so
			if(display_list){
				//initialize list
				created =true;
				currentNode->the_object=glGenLists(current_list_index);
				glNewList(currentNode->the_object,GL_COMPILE);
			}
			//draw goes here
			// Draw all the primitives of the current node
			vector<scene::Primitive*> primitives = currentNode->getPrimitives();
			vector<scene::Primitive*>::const_iterator itP;

			for (itP = primitives.begin(); itP != primitives.end(); itP++) {
				if (txt_t && txt_s) {
					(*itP)->setTexlength_s(txt_s);
					(*itP)->setTexlength_t(txt_t);
				}
				(*itP)->draw();
			}
			// Call this function untill all the nodes with the children ref are visited
			vector<string> childrenNodeRef = currentNode->getChildrenNodeRef();
			vector<string>::const_iterator itRef;

			for (itRef = childrenNodeRef.begin(); itRef != childrenNodeRef.end(); itRef++) {
				string childId = (*itRef);
				glPushMatrix();
				processNode(childId);
				glPopMatrix();
			}
			if(created){
				//end list only if it was created
				//during this flow
				glEndList();
			}
		}else if(display_list && currentNode->the_object){
			//node uses a list and it is defined
			glCallList(current_list_index);
		}
		//next list
		current_list_index++;
		//----> END NEW



		//Reaching here means all children are processed
		//so we need previous appearance
		if (pop && app_stack.size() > 1) {
			app_stack.pop();
			app_refStack.pop();
			app_stack.top()->apply(); // apply appearance

			glMaterialfv(GL_FRONT, GL_EMISSION, appearancesMap[app_refStack.top()]->getEmissive()); // emissive
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

void Scene::setCameras(map<string, Camera*> camerasMap) {
	this->camerasMap = map<string, Camera*>();
	this->camerasMap.insert(camerasMap.begin(), camerasMap.end());
}

void Scene::setCamerasId(map<string, unsigned int> camerasId) {
	this->camerasId = map<string, unsigned int>();
	this->camerasId.insert(camerasId.begin(), camerasId.end());
}

void Scene::setAnimations(map<string,Animation*> animations)
{
    this->animations = map<string,Animation*>();
	this->animations.insert(animations.begin(), animations.end());
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

void Scene::setInitial(string initial) {
	this->initial = initial;
}

void Scene::setDrawingMode(unsigned int mode) {
	this->mode = mode;
}

void Scene::setCurrentCameraId(string currentCameraId)
{
	this->currentCameraId = currentCameraId;
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

map<string, Camera*> Scene::getCameras() {
	return this->camerasMap;
}

map<string, unsigned int> Scene::getCamerasId() {
	return this->camerasId;
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

string Scene::getInitial() {
	return this->initial;
}

unsigned int Scene::getDrawingMode() {
	return this->mode;
}

void Scene::changeCamera(string cameraId) {
	if (camerasId.find(cameraId) != camerasId.end()) // check if the camera exists
	{

		if(cameraId != "activeCGFcamera0")
		{
			Camera* currentCamera = camerasMap[cameraId];
			currentCamera->setAspect(this->cameraAspect);

			CGFcamera* currentCGFcamera = currentCamera;
			currentCGFcamera->updateProjectionMatrix(1.0, 1.0);

			activeCamera = currentCamera;
			// Apply transformations corresponding to the camera position relative to the origin
			CGFscene::activeCamera->applyView();
			CGFapplication::activeApp->forceRefresh();
		}
		else{
			// Initialize Model-View matrix as identity
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum(-(this->cameraAspect)*0.04, (this->cameraAspect)*0.04, -0.04, 0.04, 0.1, 500.0);

			activeCamera = CGFscene::scene_cameras[0];
			// Apply transformations corresponding to the camera position relative to the origin
			CGFscene::activeCamera->applyView();

			// Initialize Model-View matrix as identity
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	}
}
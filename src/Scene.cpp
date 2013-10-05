//
//  Scene.cpp
//  LAIG - P1
//

#include "Scene.h"

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4] = {1.0, 1.0, 1.0, 1.0};

void Scene::init() {
    // Enables lighting computations
    glEnable(GL_LIGHTING);
    
    // Sets up some lighting parameters
    // Computes lighting only using the front face normals and materials
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    
    // Define ambient light (do not confuse with ambient component of individual lights)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
    
    // Uncomment below to enable normalization of lighting normal vectors
    glEnable(GL_NORMALIZE);
    
    // ------- Initialization of variables -------
    
    // globals attributes
    
    // drawmode attribute
    if(this->drawmode == "fill")
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else if(this->drawmode == "line")
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else if(this->drawmode == "point")
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    
    // shading attribute
    if(this->shading == "flat")
    {
        glShadeModel(GL_FLAT); // Define the shade model
    }
    else if(this->shading == "gouraud")
    {
        glShadeModel(GL_SMOOTH); // Define the shade model
    }
    
    // cullface attribute
    glEnable(GL_CULL_FACE);
    
    if(this->cullface == "none")
    {
        glDisable(GL_CULL_FACE);
    }
    else if(this->cullface == "back")
    {
        glCullFace(GL_BACK);
    }
    else if(this->cullface == "front")
    {
        glCullFace(GL_FRONT);
    }
    else if(this->cullface == "both")
    {
        glCullFace(GL_FRONT_AND_BACK);
    }
    
    // cullorder attribute
    glEnable(GL_CULL_FACE);
    
    if(this->cullorder == "CCW")
    {
        glFrontFace(GL_CCW);
    }
    else if(this->cullorder == "CW")
    {
         glFrontFace(GL_CW);
    }
    
    // create and save CGFLights
    
    map<string, Lightning*>::const_iterator itL = lightningMap.begin();
    
    CGFlight* newLight;
    
    GLenum light_id = GL_LIGHT0;
    
    for(itL = lightningMap.begin(); itL != lightningMap.end(); itL++)
    {
        Lightning* light = (itL)->second;
        newLight = new CGFlight(light_id, light->getLocation());
        newLight->setAmbient(light->getAmbient());
        newLight->setDiffuse(light->getDiffuse());
        newLight->setSpecular(light->getSpecular());
        
        if(light->getType() == "spot")
        {
            newLight->setAngle(light->getAngle());
            glLightfv(light_id, GL_SPOT_DIRECTION, light->getDirection());
            glLightf(light_id, GL_SPOT_EXPONENT, light->getExponent());
        }
        
        if(light->isEnabled())
        {
            newLight->enable();
        }
        else
        {
            newLight->disable();
        }
        
        // save light
        lights.push_back(newLight);
        
        light_id++;
        
    }
    
    // create and save CGFappearances
    
    map<string, Appearance*>::const_iterator itA = appearancesMap.begin();
    
    CGFappearance* newAppearance;
    
    for(itA = appearancesMap.begin(); itA != appearancesMap.end(); itA++)
    {
        Appearance* appearance = (itA)->second;
        newAppearance = new CGFappearance(appearance->getAmbient(), appearance->getDiffuse(), appearance->getSpecular(), appearance->getShininess());
        
        // emissive attribute of the CGFappearance
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
                     appearance->getEmissive());
        
        // TODO : texlength_s and texlength_t
        
        // find the texture with the textureref
        string textureref = appearance->getTextureref();
        
        if(!textureref.empty()) // check if there is a textureref to apply
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
        appearances.insert(std::pair<string,CGFappearance*>(appearance->getId(),newAppearance));
        
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
    
    for(itL = lights.begin(); itL != lights.end(); itL++)
    {
        (*itL)->draw();
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
    
    processNode(rootid);
}

void Scene::processNode(string id) {
    
    // IR BUSCAR NÓ DE ROOT/ACTUAL (com o id = id)
    Node* currentNode = sceneGraph->getNodeById(id);
    
    if (currentNode == NULL) {
        cout << "Invalid yaf??? The node with the id '" << id << "' doesn't exist?" << endl;
    } else {
        
        // search appearance
        string appearanceref = currentNode->getAppearanceRef();
        
        if(!appearanceref.empty()) // check if there is a appearanceref to apply
        {
            // apply appearance
            appearances[appearanceref]->apply();
        }
        
        // Draw all the primitives of the current node
        vector<scene::Primitive*> primitives = currentNode->getPrimitives();
        
        vector<scene::Primitive*>::const_iterator itP;
        
        for (itP = primitives.begin(); itP != primitives.end(); itP++) {
            p = (*itP);
            p->draw();
        }
        
        float m[4][4];
        
        memcpy(&m, currentNode->matrix, 4*4*sizeof(float));
        glMultMatrixf(m[0]);
        
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

Scene::~Scene(){
    
}

void Scene::setGraph(Graph* sceneGraph) {
    this->sceneGraph = sceneGraph;
}

void Scene::setAppearances(map<string,Appearance*> appearancesMap)
{
    this->appearancesMap = map<string,Appearance*>();
    this->appearancesMap.insert(appearancesMap.begin(),appearancesMap.end());
}

void Scene::setTextures(map<string,Texture*> texturesMap)
{
    this->texturesMap = map<string,Texture*>();
    this->texturesMap.insert(texturesMap.begin(),texturesMap.end());
}

void Scene::setLights(map<string,Lightning*> lightningMap)
{
    this->lightningMap = map<string,Lightning*>();
    this->lightningMap.insert(lightningMap.begin(),lightningMap.end());
}

void Scene::setBackground(float* background)
{
    memcpy(this->background, background, 4*sizeof(float));
}

void Scene::setDrawmode(string drawmode)
{
    this->drawmode = drawmode;
}

void Scene::setShading(string shading)
{
    this->shading = shading;
}

void Scene::setCullface(string cullface)
{
    this->cullface = cullface;
}

void Scene::setCullorder(string cullorder)
{
    this->cullorder = cullorder;
}

map<string,Appearance*> Scene::getAppearances()
{
    return this->appearancesMap;
}

map<string,Texture*> Scene::getTextures()
{
    return this->texturesMap;
}

map<string,Lightning*> Scene::getLights()
{
    return this->lightningMap;
}

Graph* Scene::getGraph() {
    return this->sceneGraph;
}

float* Scene::getBackground()
{
    return this->background;
}

string Scene::getDrawmode()
{
    return this->drawmode;
}

string Scene::getShading()
{
    return this->shading;
}

string Scene::getCullface()
{
    return this->cullface;
}

string Scene::getCullorder()
{
    return this->cullorder;
}

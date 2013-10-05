//
//  Scene.cpp
//  LAIG - P1
//

#include "Scene.h"
//#if __APPLE__
//#include "CGFapplication.h"
//#elif __unix
//#include <CGF/CGFapplication.h>
//#endif


// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4] = {1.0, 1.0, 1.0, 1.0};

/*TESTING*/
// Positions for lights
float light0_pos[4] = {4, 6.0, 1.0, 1.0};
float light1_pos[4] = {10.5, 6.0, 1.0, 1.0};
float ambientNull[4] = {0, 0, 0, 1};

// Coefficients for material slidesAppearance - Board A
float ambSlides[3] = {0.2, 0.2, 0.2};
float difSlides[3] = {0.6, 0.6, 0.6};
float specSlides[3] = {0.5, 0.4, 0.4};
float shininessSlides = 100.0f;

void Scene::init() {
    // Enables lighting computations
    glEnable(GL_LIGHTING);

    // Sets up some lighting parameters
    // Computes lighting only using the front face normals and materials
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

    // Define ambient light (do not confuse with ambient component of individual lights)
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

    // Define the shade model
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

    // Initialization of variables
    
    // create and save CGFLights
    
    map<string, Lightning*>::const_iterator itL = lightningMap.begin();
    
    CGFlight* newLight;
    
    unsigned int light_id = GL_LIGHT0;
    
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
                          
                                          // emissive attribute of the appearance
                                          glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
                                                       appearance->getEmissive());
                
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
                                                  
                                                  // Sets texture's wrap
                                                  newAppearance->setTextureWrap(GL_CLAMP, GL_CLAMP);
                                                  
                                                  // set texture to appearance
                                                  newAppearance->setTexture(textureFound->getFile());
                                                  
                                                  
                                              }
                                              
                                          }
                                          
        // save appearance
         appearances.insert(std::pair<string,CGFappearance*>(appearance->getId(),newAppearance));
        
    }

    // Uncomment below to enable normalization of lighting normal vectors
    glEnable(GL_NORMALIZE);

}

void Scene::display() {

    // ---- BEGIN Background, camera and axis setup
    // Clear image and depth buffer everytime we update the scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Apply transformations corresponding to the camera position relative to the origin
    CGFscene::activeCamera->applyView();

    // Uncomment below to enable normalization of lighting normal vectors
    glEnable(GL_NORMALIZE);

    /*TESTING*/

    // Declares scene elements
    //p = new scene::Torus("t1", 0.05, 0.1, 8, 8);

    // Declares materials
    //appearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);

    // Sets texture's wrap
    //appearance->setTextureWrap(GL_CLAMP, GL_CLAMP);

    // Sets texture
    //slidesAppearance->setTexture("../data/slides.png");

    /*TESTING*/

    // Draw axis
    axis.draw();

    // ---- END Background, camera and axis setup

    // ---- BEGIN Primitive drawing section

    

     // create and save CGFappearances
    
    /*appearance = new CGFappearance(CGFappearance(nodeAppearance->getAmbient(), nodeAppearance->getDiffuse(), nodeAppearance->getSpecular(), nodeAppearance->getShininess()));*/

    
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
        appearances[appearanceref]->apply();
        }
        
        /*
        if(!appearanceref.empty()) // check if there is a appearanceref to apply
        {
        map<string, Appearance*>::const_iterator itApp = appearancesMap.find(appearanceref);
        
        if (itApp == appearancesMap.end()) {
            // appearance not found
            cout << "Appearance with the ref '" << appearanceref << "' not found" << endl;
            
        } else {
            // appearance found
            nodeAppearance = itApp->second; // the appearance with the wanted ref
        }

 
            
            }
 
            
            // apply appearance
            appearance->apply();
 
        }*/
        
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

Graph* Scene::getGraph() {
    return this->sceneGraph;
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

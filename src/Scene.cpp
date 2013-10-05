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

    // Define the shade model - Exercise 1
    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);

    // Initialization of variables

    // Declares two lights, with null ambient component
    light0 = new CGFlight(GL_LIGHT0, light0_pos);
    light0->setAmbient(ambientNull);

    light1 = new CGFlight(GL_LIGHT1, light1_pos);
    light1->setAmbient(ambientNull);

    // light2 Attenuation
    light1->setKc(0.0);
    light1->setKl(1.0);
    light1->setKq(0.0);


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

    // Draw
    // Draw lights
    light0->draw();
    light1->draw();

    // Uncomment below to enable normalization of lighting normal vectors
    glEnable(GL_NORMALIZE);

    /*TESTING*/

    // Declares scene elements
    //p = new scene::Torus("t1", 0.05, 0.1, 8, 8);

    // Declares materials
    appearance = new CGFappearance(ambSlides, difSlides, specSlides, shininessSlides);

    // Sets texture's wrap
    //appearance->setTextureWrap(GL_CLAMP, GL_CLAMP);

    // Sets texture
    //slidesAppearance->setTexture("../data/slides.png");

    /*TESTING*/

    // Draw axis
    axis.draw();

    // ---- END Background, camera and axis setup

    // ---- BEGIN Primitive drawing section

    appearance->apply();
    //p->draw();

    //p = new scene::Triangle("t1", 0.0, 0.0, 0.0, 1.1, 1.1, 0.0, 1.1, 1.1, 1.1);
    //p->draw();

    //p = new scene::Rectangle("r1", 0.0, 0.0, 10.0, 10.0);
    //p->draw();

    //p = new scene::Sphere("s1", 3.0, 10, 10);
    //p->draw();

    //p = new scene::Cylinder("c1", 1.0, 1.0, 2.0, 10, 10);
    //p->draw();

    processGraph();


    // ---- END Primitive drawing section

    // We have been drawing in a memory area that is not visible - the back buffer,
    // while the graphics card is showing the contents of another buffer - the front buffer
    // glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
    glutSwapBuffers();
}

void Scene::processGraph() {
    string rootid = sceneGraph->getRootId();

    processNode(rootid);
}

void Scene::processNode(string id) {
    //map<string, Node*> nodesMap = sceneGraph->getNodes();

    //map<string, Node*>::const_iterator nodesIterator = nodesMap.begin();

    // IR BUSCAR NÓ DE ROOT/ACTUAL (com o id = id)
    Node* currentNode = sceneGraph->getNodeById(id);

    if (currentNode == NULL) {
        cout << "Invalid yaf??? The nome with the id '" << id << "' doesn't exist?" << endl;
    } else {

        // search and apply appearence
        /*string appearanceref = currentNode->getAppearanceRef();
        Appearance* nodeAppearance = new Appearance();
        
        
        map<string, Appearance*>::const_iterator pos = appearancesMap.find(appearanceref);
        
        if (pos == appearancesMap.end()) {
            // appearance not found
            cout << "Appearance with the ref '" << appearanceref << "' not found" << endl;
            
        } else {
            // appearance found
            nodeAppearance = pos->second; // the appearance with the wanted ref
        }

        
        appearance = new CGFappearance(CGFappearance(nodeAppearance->getAmbient(), nodeAppearance->getDiffuse(), nodeAppearance->getSpecular(), nodeAppearance->getShininess()));
        
                                       
        appearance->apply();
                                       
        // emissive attribute of the appearance
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,
                                                    nodeAppearance->getEmissive());
        
        */
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

Scene::~Scene() {

}

void Scene::setGraph(Graph* sceneGraph) {
    this->sceneGraph = sceneGraph;
}

Graph* Scene::getGraph() {
    return this->sceneGraph;
}

void Scene::setAppearances(map<string,Appearance*> appearancesMap)
{
    this->appearancesMap = appearancesMap;
}

map<string,Appearance*> Scene::getAppearances()
{
    return this->appearancesMap;
}

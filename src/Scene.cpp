//
//  Scene.cpp
//  LAIG - P1
//

#include "Scene.h"
#include "CGFapplication.h"

// Global ambient light (do not confuse with ambient component of individual lights)
float globalAmbientLight[4]= {1.0,1.0,1.0,1.0};

void Scene::init()
{
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
    
    
	// Uncomment below to enable normalization of lighting normal vectors
	glEnable (GL_NORMALIZE);
    
}


void Scene::display()
{
    
    // ---- BEGIN Background, camera and axis setup
    // Clear image and depth buffer everytime we update the scene
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    // Initialize Model-View matrix as identity (no transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Apply transformations corresponding to the camera position relative to the origin
    CGFscene::activeCamera->applyView();
    
    // Draw lights

    
    // Draw axis
    axis.draw();
    
    // ---- END Background, camera and axis setup
    
    // ---- BEGIN Primitive drawing section
    

    
    // ---- END Primitive drawing section
    
    // We have been drawing in a memory area that is not visible - the back buffer,
    // while the graphics card is showing the contents of another buffer - the front buffer
    // glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
    glutSwapBuffers();
}

Scene::~Scene()
{
    
}

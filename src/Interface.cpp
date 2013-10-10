//
//  Interface.cpp
//  LAIG - P1
//

#include "Interface.h"

#include "Scene.h"

Interface::Interface()
{
	viewID = 0;
    cameraID = 0;
}

void Interface::processKeyboard(unsigned char key, int x, int y)
{
	// Uncomment below if you would like to process the default keys (e.g. 's' for snapshot, 'Esc' for exiting, ...)
    CGFinterface::processKeyboard(key, x, y);
    
	switch(key)
	{
		case 'c':
		{
			break;
		}
	}
}

void Interface::initGUI()
{
    // Main panel
    GLUI_Panel *mainPanel= addPanel("Options", 1);
    
    // Lights
    GLUI_Panel *lightsPanel= addPanelToPanel(mainPanel, "Lights", 1);
    
    if(((Scene *) scene)->light0Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 1", ((Scene *) scene)->light_0, 2);
    }
    
    if(((Scene *) scene)->light1Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 2", ((Scene *) scene)->light_1, 3);
    }
    
    if(((Scene *) scene)->light2Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 3", ((Scene *) scene)->light_2, 4);
    }
    
    if(((Scene *) scene)->light3Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 4", ((Scene *) scene)->light_3, 5);
    }
    
    if(((Scene *) scene)->light4Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 5", ((Scene *) scene)->light_4, 6);
    }
    
    if(((Scene *) scene)->light5Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 6", ((Scene *) scene)->light_5, 7);
    }
    
    if(((Scene *) scene)->light6Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 7", ((Scene *) scene)->light_6, 8);
    }
    
    if(((Scene *) scene)->light7Exists)
    {
    addCheckboxToPanel(lightsPanel, "Light 8", ((Scene *) scene)->light_7, 9);
    }

    
    addColumnToPanel(mainPanel);
    
    // Cameras
    GLUI_Panel *camerasPanel= addPanelToPanel(mainPanel, "Cameras", GLUI_PANEL_EMBOSSED);
     
    GLUI_Listbox *cameraListBox = addListboxToPanel(camerasPanel, "Choose camera: ",&this->cameraID, 10);
    
    cameraListBox->add_item(0,"Default"); // default active camera
    
    map<string, scene::Camera*> cameras = ((Scene *) scene)->getCameras();
    map<string, unsigned int> camerasId = ((Scene *) scene)->getCamerasId();
    
    map<string, scene::Camera*>::const_iterator itC;
    scene::Camera* currentCamera;
    
    // fixed cameras
    for (itC = cameras.begin(); itC != cameras.end(); itC++)
    {
        currentCamera = (itC)->second;
        string currentCameraId = currentCamera->getId();
        cameraListBox->add_item(camerasId[currentCamera->getId()], currentCameraId.c_str());
        
        if(currentCameraId == ((Scene *) scene)->getInitial())
        {
            this->cameraID = camerasId[currentCamera->getId()];
        }
    }
    
    addColumnToPanel(mainPanel);
    
    // Drawing Mode
    GLUI_Panel *viewPanel= addPanelToPanel(mainPanel, "Drawing Mode", GLUI_PANEL_EMBOSSED);
    GLUI_RadioGroup *viewMode = addRadioGroupToPanel(viewPanel, &viewID, 11);
    
    addRadioButtonToGroup(viewMode, "Fill");
    addRadioButtonToGroup(viewMode, "Line");
    addRadioButtonToGroup(viewMode, "Point");
}

void Interface::processGUI(GLUI_Control *ctrl)
{
	
    printf ("GUI control id: %d\n  ",ctrl->user_id);
    
	switch (ctrl->user_id)
	{
        case 10:
        {
            if(cameraID > 0)
            {
                
            map<string, unsigned int> camerasId = ((Scene *) scene)->getCamerasId();
            
                string cameraIDStr;
                
                map<string, unsigned int>::const_iterator itC;
                
                for(itC = camerasId.begin(); itC != camerasId.end(); itC++)
                {
                    if((itC)->second == cameraID)
                    {
                        cameraIDStr = (itC)->first;
                    }
                }
                
            ((Scene *) scene)->setCurrentCameraId(cameraIDStr);
            }
            else {
                ((Scene *) scene)->setCurrentCameraId("activeCGFcamera0");
            }
            break;
        };
            
        case 11:
        {
            if((viewID == 0) || (viewID == 1) || (viewID == 2))
            {
                ((Scene *) scene)->setDrawingMode(viewID);
                
            }
            break;
        };
            
        case 12:
        {
            break;
        };
            
            
	};
    
}


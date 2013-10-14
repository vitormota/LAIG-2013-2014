#include "Interface.h"

#include "Scene.h"
#include <sstream>

Interface::Interface()
{
	this->viewID = 0;
    this->cameraID = 0;
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
        string lightStr = "Light 1: ";
        string id = ((Scene *) scene)->lightsId[0];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_0, 2);
    }
    
    if(((Scene *) scene)->light1Exists)
    {
        string lightStr = "Light 2: ";
        string id = ((Scene *) scene)->lightsId[1];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_1, 3);
    }
    
    if(((Scene *) scene)->light2Exists)
    {
        string lightStr = "Light 3: ";
        string id = ((Scene *) scene)->lightsId[2];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_2, 4);
    }
    
    if(((Scene *) scene)->light3Exists)
    {
        string lightStr = "Light 4: ";
        string id = ((Scene *) scene)->lightsId[3];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_3, 5);
    }
    
    if(((Scene *) scene)->light4Exists)
    {
        string lightStr = "Light 5: ";
        string id = ((Scene *) scene)->lightsId[4];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_4, 6);
    }
    
    if(((Scene *) scene)->light5Exists)
    {
        string lightStr = "Light 6: ";
        string id = ((Scene *) scene)->lightsId[5];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_5, 7);
    }
    
    if(((Scene *) scene)->light6Exists)
    {
        string lightStr = "Light 7: ";
        string id = ((Scene *) scene)->lightsId[6];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_6, 8);
    }
    
    if(((Scene *) scene)->light7Exists)
    {
        string lightStr = "Light 8: ";
        string id = ((Scene *) scene)->lightsId[7];
        stringstream tmp;
        tmp << lightStr << id;
        
        addCheckboxToPanel(lightsPanel, (char*) tmp.str().c_str(), ((Scene *) scene)->light_7, 9);
    }
    
    addColumnToPanel(mainPanel);
    
    // Cameras
    GLUI_Panel *camerasPanel= addPanelToPanel(mainPanel, "Cameras", GLUI_PANEL_EMBOSSED);
    
    GLUI_Listbox *cameraListBox = addListboxToPanel(camerasPanel, "Choose camera: ",&this->cameraID, 10);
    
    cameraListBox->add_item(0,"Default"); // default active camera
    
    map<string, Camera*> cameras = ((Scene *) scene)->getCameras();
    map<string, unsigned int> camerasId = ((Scene *) scene)->getCamerasId();
    
    map<string, Camera*>::const_iterator itC;
    Camera* currentCamera;
    
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
	
    // Uncomment to see if the id's of the elements of the GUI are correct
    //printf ("GUI control id: %d\n  ",ctrl->user_id);
    
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
	};
}


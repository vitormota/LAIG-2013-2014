//
//  Interface.h
//  LAIG - P1
//

#ifndef Interface_H
#define Interface_H

#if __APPLE__
#include "CGFinterface.h"
#elif __unix
#include <CGF/CGFinterface.h>
#endif
#include <string>
#include <map>

/*using std::string;
using std::map;*/

class Interface: public CGFinterface {
public:
    Interface();
    
    virtual void initGUI();
    virtual void processGUI(GLUI_Control *ctrl);
    
    virtual void processKeyboard(unsigned char key, int x, int y);

    int cameraID;
    int viewID;
    
    //map<string, unsigned int> camerasId;
};


#endif


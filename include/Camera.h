//
//  Camera.h
//  LAIG - P1
//

#ifndef _CAMERAS_H
#define _CAMERAS_H

#include <string>
#include <cstring>
#if __APPLE__
#include "CGFcamera.h"
#elif __unix
#include <CGF/CGFcamera.h>
#elif _WIN32
#include "CGFcamera.h"
#endif

namespace scene{
    
    using namespace std;
    
    class Camera
    {
    public:
        Camera();
        Camera(string id, string type, float near, float far);
        ~Camera();
        
        void setId(string id);
        void setNear(float near);
        void setFar(float far);
        void setType(string type);
        
        void setAngle(float angle);
        void setPos(float* pos);
        void setTarget(float* target);
        
        void setLeft(float left);
        void setRight(float right);
        void setTop(float top);
        void setBottom(float bottom);
        
        string getId();
        float getNear();
        float getFar();
        string getType();
        
        float getAngle();
        float* getPos();
        float* getTarget();
        
        float getLeft();
        float getRight();
        float getTop();
        float getBottom();
        
    private:
        string id, type;
        float near, far;
        
        /* perspective camera */
        float angle;
        float pos[3];
        float target[3];
        
        /* ortho camera */
        float left;
        float right;
        float top;
        float bottom;
    };
    
}//scene

#endif

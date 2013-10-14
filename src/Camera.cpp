#include "Camera.h"
#include "Scene.h"

Camera::Camera(): CGFcamera()
{
    
}

Camera::Camera(string id, string type, float near, float far): CGFcamera()
{
    setId(id);
    setType(type);
    setNear(near);
    setFar(far);
    
    setAngle(0);
    
    for(unsigned int i = 0; i < 3; i++)
    {
        this->pos[i] = 0;
        this->target[i] = 0;
    }
    
    setLeft(0);
    setRight(0);
    setTop(0);
    setBottom(0);
    setAspect(0);
    
}

Camera::~Camera()
{
    
}

void Camera::setId(string id)
{
    this->id = id;
}

void Camera::setType(string type)
{
    this->type = type;
}

void Camera::setNear(float near)
{
    this->near = near;
}

void Camera::setFar(float far)
{
    this->far = far;
}

void Camera::setAngle(float angle)
{
    this->angle = angle;
}

void Camera::setPos(float* pos)
{
    memcpy(this->pos, pos, 3*sizeof(float));
}

void Camera::setTarget(float* target)
{
    memcpy(this->target, target, 3*sizeof(float));
}

void Camera::setLeft(float left)
{
    this->left = left;
}

void Camera::setRight(float right)
{
    this->right = right;
}

void Camera::setTop(float top)
{
    this->top = top;
}

void Camera::setBottom(float bottom)
{
    this->bottom = bottom;
}

void Camera::setAspect(float aspect)
{
    this->aspect = aspect;
}

string Camera::getId()
{
    return this->id;
}

string Camera::getType()
{
    return this->type;
}

float Camera::getNear()
{
    return this->near;
}

float Camera::getFar()
{
    return this->far;
}

float Camera::getAngle()
{
    return this->angle;
}

float* Camera::getPos()
{
    return this->pos;
}

float* Camera::getTarget()
{
    return this->target;
}

float Camera::getLeft()
{
    return this->left;
}

float Camera::getRight()
{
    return this->right;
}

float Camera::getTop()
{
    return this->top;
}

float Camera::getBottom()
{
    return this->bottom;
}

void Camera::updateProjectionMatrix(int, int)
{
    if (this->type == "perspective") {
        
        // Clear image and depth buffer everytime we update the scene
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(this->angle, this->aspect, this->near, this->far);
        
        float* pos = this->pos;
        float* target = this->target;
        
        gluLookAt(pos[0], pos[1], pos[2], target[0], target[1], target[2], 0.0, 1.0, 0.0);
        
    } else
        if (this->type == "ortho") {
            // Clear image and depth buffer everytime we update the scene
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            
            //glOrtho(this->left*this->aspect, this->right*this->aspect, this->bottom, this->top, this->near, this->far);
            
            glOrtho(this->left, this->right, this->bottom, this->top
                    , this->near, this->far);
        }
    
    // Clear image and depth buffer everytime we update the scene
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Initialize Model-View matrix as identity
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}
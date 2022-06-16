#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;

class Camera
{
    public:
        glm::vec3 position;
        glm::vec3 direction;
        GLfloat speedMovement;

        Camera(glm::vec3 position);
        glm::mat4 getViewMatrix();
        void update(glm::vec2 offset);
};

#endif

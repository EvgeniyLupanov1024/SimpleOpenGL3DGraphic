#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    public:
        glm::vec3 position;
        glm::vec3 direction;

        Camera(glm::vec3 position);
        glm::mat4 getViewMatrix();
};

#endif

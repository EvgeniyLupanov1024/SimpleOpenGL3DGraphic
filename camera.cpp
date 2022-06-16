#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::translate(glm::mat4(1.f), position);
}

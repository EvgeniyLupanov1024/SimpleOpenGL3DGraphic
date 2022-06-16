#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;

    this->speedMovement = 0.05;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::translate(glm::mat4(1.f), position);
}

void Camera::update(glm::vec2 offset)
{
    if (offset.x || offset.y) {
        offset = glm::normalize(offset);
    }

    position.x += offset.x * speedMovement;
    position.y += offset.y * speedMovement;
}

#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;
    this->target = glm::vec3(0.f, 0.f, 0.f);

    this->updateDirection();

    this->speedMovement = 0.05;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, target, directionUp);
}

void Camera::update(glm::vec2 offset)
{
    if (offset.x || offset.y) {
        offset = glm::normalize(offset);
    }

    position.x += offset.x * speedMovement;
    position.y += offset.y * speedMovement;

    this->updateDirection();
}

void Camera::updateDirection()
{
    this->directionFront = glm::normalize(this->position - this->target);
    this->directionRight = glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), this->directionFront);
    this->directionUp = glm::cross(this->directionRight, this->directionFront);
}

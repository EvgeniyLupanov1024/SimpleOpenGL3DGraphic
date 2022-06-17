#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;
    this->target = glm::vec3(0.f, 0.f, 0.f);

    this->updateDirection();

    this->speedMovement = 0.15f;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, target, directionUp);
}

void Camera::update(glm::vec3 offsetPosition)
{
    if (offsetPosition.x || offsetPosition.y || offsetPosition.z) {
        offsetPosition = glm::normalize(offsetPosition);
    }

    position += offsetPosition * speedMovement;

    this->updateDirection();
}

void Camera::updateDirection()
{
    this->directionFront = glm::normalize(this->position - this->target);
    this->directionRight = glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), this->directionFront);
    this->directionUp = glm::cross(this->directionRight, this->directionFront);
}

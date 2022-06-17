#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;
    this->angles = glm::vec3(0.0f, 0.0f, 0.0f);

    this->speedMovement = 0.1f;
    this->speedRotstion = 0.005f;

    this->updateDirection();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + directionFront, directionUp);
}

void Camera::update(glm::vec3 offsetPosition, glm::vec2 offsetDirection)
{
    if (offsetPosition.x || offsetPosition.y || offsetPosition.z) {
        offsetPosition = glm::normalize(offsetPosition);
        position += offsetPosition * speedMovement;
    }

    offsetDirection *= speedRotstion;
    angles.x -= offsetDirection.x;
    angles.y -= offsetDirection.y;

    updateDirection();
}

void Camera::updateDirection()
{
    directionFront.x = cos(angles.x) * cos(angles.y);
    directionFront.y = sin(angles.x);
    directionFront.z = sin(angles.y);

    directionRight = glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), directionFront);
    directionUp = glm::cross(directionRight, directionFront);
}

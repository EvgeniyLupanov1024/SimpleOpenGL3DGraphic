#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;
    this->angles = glm::vec3(0.f);

    this->speedMovement = glm::vec3(0.f);
    this->speedRotation = glm::vec3(0.f);

    this->mass = 100.f;
    this->resistanceMovement = 1.1f;
    this->momentInertia = 1000.f;
    this->resistanceRotation = 1.15f;

    this->updateDirection();
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + directionFront, directionUp);
}

void Camera::update(glm::vec3 offsetPosition, glm::vec2 offsetDirection)
{
    if (offsetPosition.x || offsetPosition.y || offsetPosition.z) {

        offsetPosition = glm::normalize(offsetPosition) / mass;
        
        speedMovement.x += offsetPosition.x * cos(angles.x) - offsetPosition.y * sin(angles.x);
        speedMovement.y += offsetPosition.y * cos(angles.x) + offsetPosition.x * sin(angles.x);
        speedMovement.z += offsetPosition.z;
    }

    if (offsetDirection.x || offsetDirection.y) {

        offsetDirection /= 1000.f;

        speedRotation.x -= offsetDirection.x;
        speedRotation.y -= offsetDirection.y;
    }

    speedMovement /= resistanceMovement;
    speedRotation /= resistanceRotation;

    position += speedMovement;
    angles += speedRotation;

    if (angles.y > glm::radians(89.9f)) {
        angles.y = glm::radians(89.9f);

    } else if (angles.y < glm::radians(-89.9f)) {
        angles.y = glm::radians(-89.9f);
    }

    updateDirection();
}

void Camera::updateDirection()
{
    directionFront.x = cos(angles.x) * cos(angles.y);
    directionFront.y = sin(angles.x) * cos(angles.y);
    directionFront.z = sin(angles.y);

    directionRight = glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), directionFront);
    directionUp = glm::cross(directionRight, directionFront);
}

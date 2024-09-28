// Camera.cpp
#include "Camera.h"

Camera::Camera()
    : position(glm::vec3(3.0f, 3.0f, 3.0f)), // Starting position
      front(glm::vec3(0.0f, 0.0f, 0.0f)),    // Looking at the origin
      up(glm::vec3(0.0f, 1.0f, 0.0f)),        // Up vector
      yaw(-90.0f),                           // Yaw angle
      pitch(0.0f)                            // Pitch angle
{
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    // Adjust camera angles based on mouse movement
    yaw += xoffset;
    pitch -= yoffset;

    // Constrain pitch to prevent flipping
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Update front vector
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);
}

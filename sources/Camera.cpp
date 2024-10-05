// Camera.cpp
#include "Camera.h"
#include "EventState.h"
#include "ShaderHandler.h"
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(EventState& eventState)
    : eventState_(eventState), 
      position_(glm::vec3(2.0f, 2.0f, 2.0f)), // Camera at (2, 2, 2)
      target_(glm::vec3(0.0f, 0.0f, 0.0f)),  // Looking at the origin
      orientation_(glm::vec3(0.0f, 1.0f, 0.0f)) // Up direction is positive Y-axis
{
    // No more glMatrixMode or gluLookAt

    // You can calculate the view matrix once in the constructor
    view_ = glm::lookAt(position_, target_, orientation_);

    // Set up projection matrix using glm::perspective (adjust based on window size)
    projection_ = glm::perspective(glm::radians(45.0f), 1200.0f / 1200.0f, 0.1f, 100.0f); 
}

void 
Camera::update(ShaderHandler& shader)
{ 
    // Update the camera view matrix based on user input if needed
    // For now, it's static, but you can add movement here later
    
    // Pass the view matrix to the shader
    shader.setMat4("view", view_);
    
    // Also pass the projection matrix (typically this doesn't change unless the window is resized)
    shader.setMat4("projection", projection_);
}

void 
Camera::processMouseMovement() 
{
    // Only process movement if the left mouse button is pressed
    if (eventState_.mouse.leftButtonDown) {
        const float sensitivity = 0.1f; // Adjust sensitivity as needed

        // Use relative mouse movements
        float xoffset = eventState_.mouse.xRel * sensitivity;
        float yoffset = eventState_.mouse.yRel * sensitivity;

        // Adjust camera angles based on mouse movement
        yaw_ += xoffset;
        pitch_ -= yoffset;

        // Constrain pitch to prevent flipping
        if (pitch_ > 89.0f) pitch_ = 89.0f;
        if (pitch_ < -89.0f) pitch_ = -89.0f;

        // Update front vector
        orientation_.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        orientation_.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        orientation_ = glm::normalize(orientation_);
        orientation_.y = sin(glm::radians(pitch_));
    }
}

glm::mat4&
Camera::getViewMatrix()
{
    return view_;
}

glm::mat4&
Camera::getProjectionMatrix()
{
    return projection_;
}

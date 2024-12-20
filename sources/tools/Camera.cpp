#include "Camera.h"
#include "EventState.h"
#include "Settings.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(EventState& eventState, Settings& settings)
    : eventState_(eventState),
      settings_(settings),
      position_(glm::vec3(0.0f, 2.0f, -2.0f)), 
      target_(glm::vec3(0.0f, 0.0f, 0.0f)), 
      orientation_(glm::vec3(0.0f, 1.0f, 0.0f)) 
{
    glm::vec3 direction = glm::normalize(position_ - target_);
    yaw_   = glm::degrees(atan2(direction.x, direction.z));
    pitch_ = glm::degrees(asin(direction.y)); 

    view_ = glm::lookAt(position_, target_, orientation_);
    projection_ = glm::perspective(glm::radians(45.0f), 1200.0f / 1200.0f, 0.1f, 100.0f); 
}

void 
Camera::update()
{ 
    move();
    zoom();
    view_ = glm::lookAt(position_, target_, orientation_);
}

void 
Camera::move()
{
    processMouseMovement();
}


void 
Camera::zoom()
{
    if (eventState_.keyboard.ctrl)
    {
        float sensitivity = settings_.camera.sensitivity;

        float wheelOffset = eventState_.mouse.wheelRel * sensitivity;
        glm::vec3 front = glm::normalize(target_ - position_);
        position_ += front * wheelOffset;
    }
}


void 
Camera::processMouseMovement()
{
    if (eventState_.mouse.leftButtonDown) 
    {
        float sensitivity = settings_.camera.sensitivity;

        float xoffset = eventState_.mouse.xRel * sensitivity;
        float yoffset = eventState_.mouse.yRel * sensitivity;

        if (eventState_.keyboard.ctrl)
        {
            sensitivity *= glm::distance(target_, position_)*0.04;
            // Calculate right and up vectors
            glm::vec3 front = glm::normalize(target_ - position_);
            glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))); // Right vector
            glm::vec3 up = glm::cross(right, front); // Up vector

            // Update position based on mouse movement
            position_ -= right * xoffset * sensitivity;  // Move left/right
            position_ += up * yoffset * sensitivity;     // Move up/down (inverted for screen coordinates)

            target_ -= right * xoffset * sensitivity;  // Move left/right
            target_ += up * yoffset * sensitivity; 
        }
        else
        {   
            yaw_   -= xoffset;
            pitch_ += yoffset;

            float roll = 0.0;
            if (pitch_ > 89.0f) 
            {
                pitch_ = 89.0f;
            }
            if (pitch_ < -89.0f) 
            {
                pitch_ = -89.0f;
            }

            float radius = glm::length(position_ - target_);

            position_.x = target_.x + radius * cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
            position_.y = target_.y + radius * sin(glm::radians(pitch_));
            position_.z = target_.z + radius * cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
        }
    }
}

const glm::mat4&
Camera::getViewMatrix() const
{
    return view_;
}

const glm::mat4&
Camera::getProjectionMatrix() const 
{
    return projection_;
}

const glm::vec3& 
Camera::getPosition() const
{
    return position_;
}

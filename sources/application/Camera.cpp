#include "Camera.h"
#include "EventState.h"
#include "Settings.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera()
    : eventState_(EventState::getInstance()),
      settings_(Settings::getInstance()),
      position_(glm::vec3(2.0f, 0.0f, 0.0f)), 
      target_(glm::vec3(0.0f, 0.0f, 0.0f)), 
      orientation_(glm::vec3(0.0f, 0.0f, -1.0f)) 
{
    glm::vec3 direction = glm::normalize(position_ - target_);
    pitch_ = glm::degrees(atan2(direction.z, direction.x));
    yaw_   = glm::degrees(atan2(direction.y, -direction.x)); 

    view_          = glm::lookAt(position_, target_, orientation_);
    projection_    = glm::perspective(glm::radians(45.0f), 1200.0f / 1200.0f, 0.1f, 2000.0f); 
    viewDirection_ = glm::normalize(target_ - position_);
}


void 
Camera::update()
{
    move();
    zoom();
    view_          = glm::lookAt(position_, target_, orientation_);
    viewDirection_ = glm::normalize(target_ - position_);
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
            glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 0.0f, -1.0f))); // Right vector
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
            pitch_ -= yoffset;

            yaw_ = std::fmod(yaw_, 360.0); // remainder after division by 360
            if (yaw_ < 0)
                yaw_ += 360.0;

            if (pitch_ > 89.0f) {
                pitch_ = 89.0f;
            }
            if (pitch_ < -89.0f) {
                pitch_ = -89.0f;
            }

            float radius = glm::length(position_ - target_);
            
            glm::vec3 direction;
            direction.x = - cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
            direction.y =   cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
            direction.z =   sin(glm::radians(pitch_));

            direction = glm::normalize(direction);
            position_ = target_ + direction * radius;
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


const glm::vec3 
&Camera::getViewDirection() const
{
    return viewDirection_;
}

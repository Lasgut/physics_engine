#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include "EventState.h"
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Camera 
{
public:
    Camera(EventState& eventState);

    void update();

    const glm::mat4& getViewMatrix()       const;
    const glm::mat4& getProjectionMatrix() const;
    const glm::vec3& getPosition()         const;

private:
    EventState& eventState_;
    glm::vec3   position_;
    glm::vec3   target_;
    glm::vec3   orientation_;
    float       azimuthAngle_;
    float       polarAngle_;
    float       pitch_;
    float       yaw_;

    glm::mat4 view_;
    glm::mat4 projection_;

    void move();
    void processMouseMovement();
};

#endif 

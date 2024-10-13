// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include "EventState.h"
#include "ShaderHandler.h"
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Camera 
{
public:
    Camera(EventState& eventState);

    void update(ShaderHandler& shader);

    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();
    glm::vec3& getPosition();

private:
    EventState& eventState_;
    glm::vec3   position_;
    glm::vec3   target_;
    glm::vec3   orientation_;
    float       yaw_;
    float       pitch_;

    glm::mat4 view_;
    glm::mat4 projection_;

    void move();
    void processMouseMovement();
};

#endif // CAMERA_H

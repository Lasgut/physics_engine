// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include "EventState.h"
#include "ShaderHandler.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera 
{
public:
    Camera(EventState& eventState);

    void update(ShaderHandler& shader);
    void processMouseMovement();

    glm::mat4& getViewMatrix();
    glm::mat4& getProjectionMatrix();

private:
    EventState& eventState_;
    glm::vec3   position_;
    glm::vec3   target_;
    glm::vec3   orientation_;
    float       yaw_;
    float       pitch_;

    glm::mat4 view_;
    glm::mat4 projection_;
};

#endif // CAMERA_H

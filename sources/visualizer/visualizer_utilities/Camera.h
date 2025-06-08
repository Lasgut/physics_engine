#ifndef CAMERA_H
#define CAMERA_H

#pragma once
#include "EventState.h"
#include "Settings.h"
#include <glad/gl.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

class Camera 
{
    public:
        Camera();

        void update(const glm::vec3& targetPosition, const glm::quat& targetOrientation);

        void setLookAt(const glm::vec3& target);

        const glm::mat4& getViewMatrix()       const;
        const glm::mat4& getProjectionMatrix() const;
        const glm::vec3& getPosition()         const;
        const glm::vec3& getViewDirection()    const;

    private:
        void move();
        void zoom();
        void processMouseMovement();

        EventState& eventState_;
        Settings&   settings_;
        glm::vec3   position_;
        glm::vec3   target_;
        glm::vec3   orientation_;
        glm::vec3   viewDirection_;
        float       azimuthAngle_;
        float       polarAngle_;
        float       pitch_;
        float       yaw_;

        glm::mat4 view_;
        glm::mat4 projection_;
};

#endif 

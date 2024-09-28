// Camera.h
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera();
    glm::mat4 getViewMatrix() const;
    void processMouseMovement(float xoffset, float yoffset);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
};

#endif // CAMERA_H

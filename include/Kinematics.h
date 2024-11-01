#ifndef KINEMATICS_H
#define KINEMATICS_H

#pragma once
#include <glad/glad.h>

struct Kinematics 
{
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    glm::vec3 orientation{0.0f, 0.0f, 0.0f};
    float     mass;
};

#endif
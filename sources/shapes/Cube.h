#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <glad/glad.h>
#include "ShaderHandler.h"

class Cube 
{
public:
    Cube();
    ~Cube();

    void draw(ShaderHandler& shader);
    void update(float deltaTime, glm::vec3 force);
    glm::vec3 getPosition() const; 

private:
    GLuint VAO_;
    GLuint VBO_;

    float mass_{10};
    float length_{0.1};
    float width_{0.1};
    float height_{0.1};

    glm::vec3 position_{0.0f, 0.0f, 0.0f}; 
    glm::vec3 velocity_;      
    glm::vec3 force_;         
};

#endif

#ifndef SHAPE_H
#define SHAPE_H

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Shape
{
public:
    Shape();
    ~Shape();

protected:
    void      glStuff();
    glm::vec3 fromNEDtoCAMERA(const glm::vec3& vec);

    GLuint VAO_;
    GLuint VBO_;
    std::vector<float> vertices_;

};

#endif
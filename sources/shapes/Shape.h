#ifndef SHAPE_H
#define SHAPE_H

#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Shape
{
public:
    Shape();
    ~Shape();

protected:
    void      glStuff(int attributeCount = 6);
    glm::mat4 fromNED();
    glm::mat4 createModelMat(const glm::vec3& pos,
                             const glm::vec3& ori);

    GLuint VAO_;
    GLuint VBO_;
    std::vector<float> vertices_;

};

#endif
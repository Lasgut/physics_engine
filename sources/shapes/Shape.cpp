#include "Shape.h"
#include <glad/gl.h>
#include <iostream>

Shape::~Shape()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}


void 
Shape::glStuff(int attributeCount) 
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (attributeCount > 3) 
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(0);
}


void 
Shape::glStuffStl(int attributeCount, const std::vector<unsigned int>& triangleIndicies)
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers     (1, &VBO_);
    glGenBuffers     (1, &EBO_); 

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleIndicies.size() * sizeof(unsigned int), triangleIndicies.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (attributeCount > 3) 
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    glBindVertexArray(0);
}


void 
Shape::glDraw()
{
    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3);
    glBindVertexArray(0);
}


void 
Shape::glDrawStl(const std::vector<unsigned int>& triangleIndicies)
{
    // glEnable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, triangleIndicies.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}


glm::mat4
Shape::fromNED()
{
    glm::mat4 modelMat = glm::mat4(1.0f);
    return glm::rotate(modelMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}


glm::mat4
Shape::createModelMat(const glm::vec3& pos,
                      const glm::vec3& ori)
{
    auto modelMat = fromNED();

    modelMat = glm::translate(modelMat, pos);

    glm::mat4 rotationMat = glm::mat4(1.0f);
    rotationMat = glm::rotate(rotationMat, ori.z, glm::vec3(0.0f, 0.0f, 1.0f));
    rotationMat = glm::rotate(rotationMat, ori.y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMat = glm::rotate(rotationMat, ori.x, glm::vec3(1.0f, 0.0f, 0.0f));
    modelMat *= rotationMat;

    return modelMat;
}

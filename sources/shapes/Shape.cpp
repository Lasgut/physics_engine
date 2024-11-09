#include "Shape.h"
#include <glad/glad.h>
#include <iostream>

Shape::Shape()
{

}

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

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (attributeCount > 3) 
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attributeCount * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

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

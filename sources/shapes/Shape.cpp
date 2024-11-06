#include "Shape.h"
#include <glad/glad.h>

Shape::Shape()
{

}

Shape::~Shape()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void Shape::glStuff()
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size()*sizeof(float), vertices_.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

glm::vec3
Shape::fromNEDtoCAMERA(const glm::vec3 &vecNED)
{
    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec4 vecCamera = rotMat*glm::vec4(vecNED, 1);
    return glm::vec3(vecCamera);
}

glm::mat4
Shape::createModelMat(const glm::vec3& pos)
{
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, fromNEDtoCAMERA(pos));
    modelMat = glm::rotate(modelMat, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    return modelMat;
}

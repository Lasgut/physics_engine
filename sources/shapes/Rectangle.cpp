#include "Rectangle.h"
#include <glad/glad.h>
#include "ShaderHandler.h"

Rectangle::Rectangle()
{
    float vertices[] = {
        -length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
         length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
        -length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
        -length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
    };

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Rectangle::~Rectangle()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void 
Rectangle::draw(ShaderHandler& shaderHandler)
{
    shaderHandler.setVec3("objectColor", glm::vec3(0.1f, 0.1f, 0.1f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    shaderHandler.setMat4("model",model);

    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

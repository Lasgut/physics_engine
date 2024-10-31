#include "Cube.h"
#include <glad/glad.h>
#include "ShaderHandler.h"

Cube::Cube() 
{
    float vertices[] = {
        -length_, -width_, -height_,  0.0f,  0.0f, -1.0f,
         length_, -width_, -height_,  0.0f,  0.0f, -1.0f, 
         length_,  width_, -height_,  0.0f,  0.0f, -1.0f, 
         length_,  width_, -height_,  0.0f,  0.0f, -1.0f, 
        -length_,  width_, -height_,  0.0f,  0.0f, -1.0f, 
        -length_, -width_, -height_,  0.0f,  0.0f, -1.0f, 

        -length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
         length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
        -length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
        -length_, -width_,  height_,  0.0f,  0.0f, 1.0f,

        -length_,  width_,  height_, -1.0f,  0.0f,  0.0f,
        -length_,  width_, -height_, -1.0f,  0.0f,  0.0f,
        -length_, -width_, -height_, -1.0f,  0.0f,  0.0f,
        -length_, -width_, -height_, -1.0f,  0.0f,  0.0f,
        -length_, -width_,  height_, -1.0f,  0.0f,  0.0f,
        -length_,  width_,  height_, -1.0f,  0.0f,  0.0f,

         length_,  width_,  height_,  1.0f,  0.0f,  0.0f,
         length_,  width_, -height_,  1.0f,  0.0f,  0.0f,
         length_, -width_, -height_,  1.0f,  0.0f,  0.0f,
         length_, -width_, -height_,  1.0f,  0.0f,  0.0f,
         length_, -width_,  height_,  1.0f,  0.0f,  0.0f,
         length_,  width_,  height_,  1.0f,  0.0f,  0.0f,

        -length_, -width_, -height_,  0.0f, -1.0f,  0.0f,
         length_, -width_, -height_,  0.0f, -1.0f,  0.0f,
         length_, -width_,  height_,  0.0f, -1.0f,  0.0f,
         length_, -width_,  height_,  0.0f, -1.0f,  0.0f,
        -length_, -width_,  height_,  0.0f, -1.0f,  0.0f,
        -length_, -width_, -height_,  0.0f, -1.0f,  0.0f,

        -length_,  width_, -height_,  0.0f,  1.0f,  0.0f,
         length_,  width_, -height_,  0.0f,  1.0f,  0.0f,
         length_,  width_,  height_,  0.0f,  1.0f,  0.0f,
         length_,  width_,  height_,  0.0f,  1.0f,  0.0f,
        -length_,  width_,  height_,  0.0f,  1.0f,  0.0f,
        -length_,  width_, -height_,  0.0f,  1.0f,  0.0f
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

Cube::~Cube() 
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void 
Cube::draw(ShaderHandler& shaderHandler) 
{
    //update(0.1, glm::vec3(0.1f, 0.0f, 0.0f));
    shaderHandler.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position_);
    // model = glm::rotate(model, (float)SDL_GetTicks()/1000, glm::vec3(0.0f, 1.0f, 0.0f));
    shaderHandler.setMat4("model",model);

    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::update(float deltaTime, glm::vec3 force)
{
    glm::vec3 acceleration = force / mass_;

    velocity_ += acceleration * deltaTime;

    position_ += velocity_ * deltaTime;
}

glm::vec3 Cube::getPosition() const
{
    return position_;
}
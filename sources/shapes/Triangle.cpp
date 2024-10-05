#include "Triangle.h"

Triangle::Triangle()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,  
        0.5f, -0.5f, 0.0f, 
        0.0f,  0.5f, 0.0f  
    }; 

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
}

void 
Triangle::draw()
{
    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

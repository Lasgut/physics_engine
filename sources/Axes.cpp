#include "Axes.h"
#include "ShaderHandler.h"
#include <glad/glad.h>

Axes::Axes()
{
    setupAxes(); // Setup VBO and VAO
}

Axes::~Axes()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Axes::setupAxes()
{
    // Vertices for the X, Y, Z axes (positions followed by colors)
    float axesVertices[] = {
        // X axis (Red)
        -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, 0.0f, // Vertex 1 (position and color)
         1.0f,  0.0f,  0.0f,   1.0f, 0.0f, 0.0f, // Vertex 2
        // Y axis (Green)
         0.0f, -1.0f,  0.0f,   0.0f, 1.0f, 0.0f, // Vertex 3
         0.0f,  1.0f,  0.0f,   0.0f, 1.0f, 0.0f, // Vertex 4
        // Z axis (Blue)
         0.0f,  0.0f, -1.0f,   0.0f, 0.0f, 1.0f, // Vertex 5
         0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f  // Vertex 6
    };

    // Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axesVertices), axesVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind VAO for now
    glBindVertexArray(0);
}

void Axes::drawAxes(ShaderHandler& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    // Model matrix is identity for the axes (they are placed at the origin)
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    //shader.setMat4("model", modelMatrix);

    // Bind the VAO (the axes data)
    glBindVertexArray(VAO);

    // Draw the axes (6 vertices total, 2 for each axis)
    glDrawArrays(GL_LINES, 0, 6);

    // Unbind the VAO
    glBindVertexArray(0);
}

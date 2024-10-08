#ifndef AXES_H
#define AXES_H

#pragma once
#include "ShaderHandler.h"
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Axes {
public:
    Axes();  // Constructor to initialize the axes
    ~Axes(); // Destructor to clean up OpenGL resources

    // Function to draw the axes, takes shader and transformation matrices as parameters
    void drawAxes(ShaderHandler& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    unsigned int VAO, VBO; // Vertex Array Object and Vertex Buffer Object

    // Private function to set up the VBO and VAO for the axes
    void setupAxes();
};

#endif // AXES_H

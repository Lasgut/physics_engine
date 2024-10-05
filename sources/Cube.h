// Cube.h
#ifndef CUBE_H
#define CUBE_H

#pragma once
#include <glad/glad.h>

class Cube 
{
public:
    Cube();
    ~Cube();
    void draw();

private:
    GLuint VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    void setupCube();
};

#endif // CUBE_H

#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Triangle2D
{
public:
    Triangle2D();
    ~Triangle2D();

    void draw();

private:
    unsigned int VBO_;
    unsigned int VAO_;

};

#endif
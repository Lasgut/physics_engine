#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

class Triangle
{
public:
    Triangle();
    ~Triangle();

    void draw();

private:
    unsigned int VBO_;
    unsigned int VAO_;

};

#endif
#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include <glad/gl.h>

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
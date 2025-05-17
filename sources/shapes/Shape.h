#ifndef SHAPE_H
#define SHAPE_H

#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Shape
{
    public:
        Shape() = default;
        ~Shape();

    protected:
        void      glStuff   (int attributeCount = 6);
        void      glStuffStl(int attributeCount, const std::vector<unsigned int>& triangleIndicies);
        void      glDraw();
        void      glDrawStl(const std::vector<unsigned int>& triangleIndicies);
        glm::mat4 fromNED();
        glm::mat4 createModelMat(const glm::vec3& pos,
                                 const glm::quat& ori);

        GLuint VAO_;
        GLuint VBO_;
        GLuint EBO_;
        std::vector<double> vertices_;
};

#endif
#ifndef STLMESH_H
#define STLMESH_H

#pragma once
#include <glad/gl.h>
#include "Shape.h"
#include "ShaderHandler.h"

class StlMesh 
    : public Shape
{
    public:
        StlMesh(const std::string& meshPath);

        void draw(const ShaderHandler& shaderHandler, 
                  const glm::vec3&     position,
                  const glm::vec3&     orientation);
          
    private:
        void readStl(const std::string& meshPath);
        void dispModelDimensions();
        const glm::vec3 rotateToNed(const glm::vec3& orientation);

    private:
        std::vector<unsigned int> triangleIndices_;
};

#endif
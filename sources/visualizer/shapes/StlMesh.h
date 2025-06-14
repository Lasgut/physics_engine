#ifndef STLMESH_H
#define STLMESH_H

#pragma once
#include <glad/gl.h>
#include "Shape.h"
#include "visualizer_utilities/ShaderHandler.h"

class StlMesh 
    : public Shape
{
    public:
        StlMesh(const std::string& meshPath);

        void draw(const ShaderHandler& shaderHandler, 
                  const glm::vec3&     position,
                  const glm::quat&     orientation);
          
    private:
        void readStl(const std::string& meshPath);
        void dispModelDimensions();
        glm::quat rotateToNed(const glm::quat& orientation);

    private:
        std::vector<unsigned int> triangleIndices_;
};

#endif
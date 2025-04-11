#include "StlMesh.h"
#include <stl_reader.h>
#include <vector>
#include <string>

StlMesh::StlMesh(const std::string& meshPath)
{
    readStl(meshPath);
    dispModelDimensions();
    glStuffStl(6, triangleIndices_);
}


void 
StlMesh::draw(const ShaderHandler& shaderHandler, 
                    const glm::vec3&     position,
                    const glm::vec3&     orientation)
{
    shaderHandler.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

    glm::mat4 model = createModelMat(position, orientation);
    shaderHandler.setMat4("model",model);
    glDrawStl(triangleIndices_);
}


void 
StlMesh::readStl(const std::string &meshPath)
{
    std::vector<float>        normals;
    std::vector<unsigned int> solidRangesDummy;
    std::vector<float>        vertexPositions;
    try 
    {
        stl_reader::ReadStlFile<std::vector<float>, std::vector<float>, std::vector<unsigned int>, std::vector<unsigned int>>(
            meshPath.c_str(), vertexPositions, normals, triangleIndices_, solidRangesDummy);
    }
    catch (std::exception& e)
    {
        std::cerr << "Error reading STL file: " << e.what() << std::endl;
    }

    vertices_.clear();
    for (size_t i = 0; i < vertexPositions.size() / 3; ++i) 
    {
        vertices_.push_back(vertexPositions[i * 3 + 0] / 1000);
        vertices_.push_back(vertexPositions[i * 3 + 1] / 1000);
        vertices_.push_back(vertexPositions[i * 3 + 2] / 1000);

        vertices_.push_back(normals[i * 3 + 0]);
        vertices_.push_back(normals[i * 3 + 1]);
        vertices_.push_back(normals[i * 3 + 2]);
    }
}


void 
StlMesh::dispModelDimensions()
{
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();
    float maxZ = std::numeric_limits<float>::lowest();

    for (size_t i = 0; i < vertices_.size() / 3; ++i) {
        float x = vertices_[i * 3 + 0];
        float y = vertices_[i * 3 + 1];
        float z = vertices_[i * 3 + 2];

        minX = std::min(minX, x);
        minY = std::min(minY, y);
        minZ = std::min(minZ, z);
        maxX = std::max(maxX, x);
        maxY = std::max(maxY, y);
        maxZ = std::max(maxZ, z);
    }

    float width  = maxX - minX;
    float height = maxY - minY;
    float depth  = maxZ - minZ;

    std::cout << "Model dimensions: " 
            << "Width: " << width << ", Height: " << height << ", Depth: " << depth << std::endl;
}

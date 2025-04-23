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
    const glm::vec3 orientationRotated = rotateToNed(orientation);
    shaderHandler.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

    glm::mat4 model = createModelMat(position, orientationRotated);
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

    // Vector for smoothed normals (or flat normals)
    std::vector<glm::vec3> vertexNormals(vertexPositions.size() / 3, glm::vec3(0.0f));

    // Iterate through triangles to calculate normals
    for (size_t i = 0; i < triangleIndices_.size(); i += 3) {
        unsigned int i0 = triangleIndices_[i];
        unsigned int i1 = triangleIndices_[i + 1];
        unsigned int i2 = triangleIndices_[i + 2];

        glm::vec3 v0(vertexPositions[i0 * 3 + 0], vertexPositions[i0 * 3 + 1], vertexPositions[i0 * 3 + 2]);
        glm::vec3 v1(vertexPositions[i1 * 3 + 0], vertexPositions[i1 * 3 + 1], vertexPositions[i1 * 3 + 2]);
        glm::vec3 v2(vertexPositions[i2 * 3 + 0], vertexPositions[i2 * 3 + 1], vertexPositions[i2 * 3 + 2]);

        // Calculate face normal (triangle normal)
        glm::vec3 faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

        // Check if the face normal is similar for all three vertices (flat surface)
        auto epsilon = 2.0f;
        bool isFlatSurface = 
            glm::epsilonEqual(normals[i0 * 3 + 0], normals[i1 * 3 + 0], epsilon) &&
            glm::epsilonEqual(normals[i0 * 3 + 1], normals[i1 * 3 + 1], epsilon) &&
            glm::epsilonEqual(normals[i0 * 3 + 2], normals[i1 * 3 + 2], epsilon) &&
            glm::epsilonEqual(normals[i1 * 3 + 0], normals[i2 * 3 + 0], epsilon) &&
            glm::epsilonEqual(normals[i1 * 3 + 1], normals[i2 * 3 + 1], epsilon) &&
            glm::epsilonEqual(normals[i1 * 3 + 2], normals[i2 * 3 + 2], epsilon);

        if (isFlatSurface) 
        {
            // If it's a flat surface, assign the same normal to all three vertices
            vertexNormals[i0] = faceNormal;
            vertexNormals[i1] = faceNormal;
            vertexNormals[i2] = faceNormal;
        }
        else 
        {
            // Otherwise, apply smoothing (we accumulate the normal for each vertex)
            vertexNormals[i0] += faceNormal;
            vertexNormals[i1] += faceNormal;
            vertexNormals[i2] += faceNormal;
        }
    }

    // Normalize the accumulated normals (for smoothed surfaces)
    for (auto& normal : vertexNormals) {
        normal = glm::normalize(normal);
    }

    // Store vertices and corresponding normals (flat or smoothed)
    vertices_.clear();
    for (size_t i = 0; i < vertexPositions.size() / 3; ++i) 
    {
        vertices_.push_back(vertexPositions[i * 3 + 0] / 1000);
        vertices_.push_back(vertexPositions[i * 3 + 1] / 1000);
        vertices_.push_back(vertexPositions[i * 3 + 2] / 1000);

        vertices_.push_back(vertexNormals[i].x);
        vertices_.push_back(vertexNormals[i].y);
        vertices_.push_back(vertexNormals[i].z);
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


const glm::vec3
StlMesh::rotateToNed(const glm::vec3 &orientation)
{
    auto rotatedOrientation = orientation;
    rotatedOrientation.x = orientation.x + 3.14f;
    return rotatedOrientation;
}

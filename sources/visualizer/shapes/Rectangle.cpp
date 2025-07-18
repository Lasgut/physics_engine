#include "Rectangle.h"
#include <glad/gl.h>
#include "visualizer_utilities/ShaderHandler.h"

Rectangle::Rectangle()
{
    vertices_ = createVertices();
    glStuff();
}

Rectangle::Rectangle(double length, double width, double height)
    : length_(length)
    , width_(width)
    , height_(height)
{
    Rectangle();
}

void 
Rectangle::draw(const ShaderHandler& shaderHandler, 
                const glm::vec3&     position,
                const glm::vec3&     orientation)
{
    shaderHandler.setVec3("objectColor", glm::vec3(0.3f, 0.3f, 0.3f));

    glm::mat4 model = createModelMat(position, orientation);
    
    shaderHandler.setMat4("model",model);

    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

std::vector<double>
Rectangle::createVertices()
{
    return {
        -length_ / 2.0f, -width_ / 2.0f,  height_,  0.0f,  0.0f,  -1.0f, // Bottom-left
         length_ / 2.0f, -width_ / 2.0f,  height_,  0.0f,  0.0f,  -1.0f, // Bottom-right
         length_ / 2.0f,  width_ / 2.0f,  height_,  0.0f,  0.0f,  -1.0f, // Top-right
         length_ / 2.0f,  width_ / 2.0f,  height_,  0.0f,  0.0f,  -1.0f, // Top-right
        -length_ / 2.0f,  width_ / 2.0f,  height_,  0.0f,  0.0f,  -1.0f, // Top-left
        -length_ / 2.0f, -width_ / 2.0f,  height_,  0.0f,  0.0f,  -1.0f, // Bottom-left
    };
}

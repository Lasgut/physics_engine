#include "Line.h"
#include "ShaderHandler.h"
#include <glad/gl.h>

Line::Line()
{
    createVertices();
    glStuff(3);
}

Line::Line(float length, const glm::vec3 &color)
    : length_(length)
    , color_(color)
{
    createVertices();
    glStuff(3);
}

void
Line::createVertices()
{
    vertices_ =  {
           0.0f,  0.0f,  0.0f,
        length_,  0.0f,  0.0f,   
    };
}


void 
Line::draw(const ShaderHandler& shaderHandler, 
           const glm::vec3&     position,
           const glm::vec3&     orientation)
{
    shaderHandler.setVec3("color", color_);
    auto model = createModelMat(position, orientation);

    shaderHandler.setMat4("model", model);
    glLineWidth(3.0f);
    glBindVertexArray(VAO_);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);

}

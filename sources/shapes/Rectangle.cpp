#include "Rectangle.h"
#include <glad/glad.h>
#include "ShaderHandler.h"

Rectangle::Rectangle()
{
    vertices_ = createVertices();
    glStuff();
}

Rectangle::Rectangle(float length, float width, float height)
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

    glm::mat4 model = glm::mat4(1.0f);
    model = fromNEDtoCAMERA(model, position);
    
    shaderHandler.setMat4("model",model);

    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

std::vector<float>
Rectangle::createVertices()
{
    return {
        -length_, -width_,  height_,  0.0f,  0.0f, -1.0f,
         length_, -width_,  height_,  0.0f,  0.0f, -1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, -1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, -1.0f,
        -length_,  width_,  height_,  0.0f,  0.0f, -1.0f,
        -length_, -width_,  height_,  0.0f,  0.0f, -1.0f,
    };
}

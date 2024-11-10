#include "Cube.h"
#include <glad/gl.h>
#include "ShaderHandler.h"

Cube::Cube() 
{
    vertices_ = createVertices();
    glStuff();
}


Cube::Cube(float length, float width, float height)
    : length_(length)
    , width_ (width)
    , height_(height)
{
    vertices_ = createVertices();
    glStuff();
}


void 
Cube::draw(const ShaderHandler& shaderHandler, 
           const glm::vec3&     position,
           const glm::vec3&     orientation) 
{
    shaderHandler.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));

    glm::mat4 model = createModelMat(position, orientation);
    shaderHandler.setMat4("model",model);

    glBindVertexArray(VAO_); 
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


std::vector<float> 
Cube::createVertices()
{
    return {
        -length_, -width_, -height_,  0.0f,  0.0f, -1.0f,
         length_, -width_, -height_,  0.0f,  0.0f, -1.0f, 
         length_,  width_, -height_,  0.0f,  0.0f, -1.0f, 
         length_,  width_, -height_,  0.0f,  0.0f, -1.0f, 
        -length_,  width_, -height_,  0.0f,  0.0f, -1.0f, 
        -length_, -width_, -height_,  0.0f,  0.0f, -1.0f, 

        -length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
         length_, -width_,  height_,  0.0f,  0.0f, 1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
         length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
        -length_,  width_,  height_,  0.0f,  0.0f, 1.0f,
        -length_, -width_,  height_,  0.0f,  0.0f, 1.0f,

        -length_,  width_,  height_, -1.0f,  0.0f,  0.0f,
        -length_,  width_, -height_, -1.0f,  0.0f,  0.0f,
        -length_, -width_, -height_, -1.0f,  0.0f,  0.0f,
        -length_, -width_, -height_, -1.0f,  0.0f,  0.0f,
        -length_, -width_,  height_, -1.0f,  0.0f,  0.0f,
        -length_,  width_,  height_, -1.0f,  0.0f,  0.0f,

         length_,  width_,  height_,  1.0f,  0.0f,  0.0f,
         length_,  width_, -height_,  1.0f,  0.0f,  0.0f,
         length_, -width_, -height_,  1.0f,  0.0f,  0.0f,
         length_, -width_, -height_,  1.0f,  0.0f,  0.0f,
         length_, -width_,  height_,  1.0f,  0.0f,  0.0f,
         length_,  width_,  height_,  1.0f,  0.0f,  0.0f,

        -length_, -width_, -height_,  0.0f, -1.0f,  0.0f,
         length_, -width_, -height_,  0.0f, -1.0f,  0.0f,
         length_, -width_,  height_,  0.0f, -1.0f,  0.0f,
         length_, -width_,  height_,  0.0f, -1.0f,  0.0f,
        -length_, -width_,  height_,  0.0f, -1.0f,  0.0f,
        -length_, -width_, -height_,  0.0f, -1.0f,  0.0f,

        -length_,  width_, -height_,  0.0f,  1.0f,  0.0f,
         length_,  width_, -height_,  0.0f,  1.0f,  0.0f,
         length_,  width_,  height_,  0.0f,  1.0f,  0.0f,
         length_,  width_,  height_,  0.0f,  1.0f,  0.0f,
        -length_,  width_,  height_,  0.0f,  1.0f,  0.0f,
        -length_,  width_, -height_,  0.0f,  1.0f,  0.0f
    };
}

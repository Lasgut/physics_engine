#include "Terrain.h"
#include "glad/gl.h"
#include <iostream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Terrain::Terrain(char const *mapFile)
{
    loadHeightMap(mapFile);
    createVertices();
    glStuff();
}


Terrain::~Terrain()
{
    glDeleteVertexArrays(1, &terrainVAO_);
    glDeleteBuffers(1, &terrainVBO_);
    glDeleteBuffers(1, &terrainIBO_);
}


void 
Terrain::update(const ShaderHandler& shaderHandler)
{
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        shaderHandler.setMat4("model", model);
        
        // render the cube
        glBindVertexArray(terrainVAO_);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for(unsigned strip = 0; strip < numStrips_; strip++)
        {
            glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                           numTrisPerStrip_+2,   // number of indices to render
                           GL_UNSIGNED_INT,     // index data_ type
                           (void*)(sizeof(unsigned) * (numTrisPerStrip_+2) * strip)); // offset to starting index
        }
}


void 
Terrain::loadHeightMap(char const *mapFile)
{
    stbi_set_flip_vertically_on_load(true);
    data_ = stbi_load(mapFile, &width_, &height_, &nrChannels_, 0);
    if (data_)
    {
        std::cout << "Loaded height_map of size " << height_ << " x " << width_ << std::endl;
    }
    else
    {
        std::cout << "Failed to load height_map" << std::endl;
    }
}


void 
Terrain::createVertices()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = nrChannels_;

    // Variables to track the lowest and highest height values
    float minHeight = std::numeric_limits<float>::max();
    float maxHeight = std::numeric_limits<float>::lowest();

    for(int i = 0; i < height_; i++)
    {
        for(int j = 0; j < width_; j++)
        {
            unsigned char* pixelOffset = data_ + (j + width_ * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

                        // Calculate the actual height value
            float heightValue = (int)y * yScale - yShift;

            // Update min and max height
            if (heightValue < minHeight) minHeight = heightValue;
            if (heightValue > maxHeight) maxHeight = heightValue;

            // vertex
            vertices_.push_back( -height_/2.0f + height_*i/(float)height_ );   // vx
            vertices_.push_back( (int) y * yScale - yShift);   // vy
            vertices_.push_back( -width_/2.0f + width_*j/(float)width_ );   // vz
        }
    }

    // Print the lowest and highest height values
    std::cout << "Lowest height: " << minHeight << std::endl;
    std::cout << "Highest height: " << maxHeight << std::endl;

    stbi_image_free(data_);
    for(unsigned i = 0; i < height_-1; i += rez)
    {
        for(unsigned j = 0; j < width_; j += rez)
        {
            for(unsigned k = 0; k < 2; k++)
            {
                indices_.push_back(j + width_ * (i + k*rez));
            }
        }
    }

    numStrips_ = (height_-1)/rez;
    numTrisPerStrip_ = (width_/rez)*2-2;
}


void 
Terrain::glStuff()
{
    // first, configure the cube's VAO (and terrainVBO_ + terrainIBO_)
    glGenVertexArrays(1, &terrainVAO_);
    glBindVertexArray(terrainVAO_);

    glGenBuffers(1, &terrainVBO_);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), &vertices_[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &terrainIBO_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned), &indices_[0], GL_STATIC_DRAW);
}

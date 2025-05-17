#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once
#include "ShaderHandler.h"
#include <vector>

class Terrain
{
    public:
        Terrain(char const *mapFile);
        ~Terrain();

        void update(const ShaderHandler&);

    private:
        void loadHeightMap(char const *mapFile);
        void createVertices();
        void glStuff();

        unsigned int            terrainVAO_;
        unsigned int            terrainVBO_; 
        unsigned int            terrainIBO_;
        int                     numStrips_;
        int                     numTrisPerStrip_;
        int                     width_;
        int                     length_;
        int                     nrChannels_;
        unsigned char*          data_;
        std::vector<float>      vertices_;
        std::vector<unsigned>   indices_;
};

#endif
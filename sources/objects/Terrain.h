#ifndef TERRAIN_H
#define TERRAIN_H

#pragma once
#include "ShaderHandler.h"

class Terrain
{
public:
    Terrain(char const *mapFile);
    ~Terrain();

    void update(const ShaderHandler&);

private:
    unsigned int terrainVAO, terrainVBO, terrainIBO;
    int numStrips, numTrisPerStrip;

};

#endif
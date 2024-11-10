#ifndef SETTINGS_H
#define SETTINGS_H

#pragma once
#include <string>

struct Camera 
{
    std::string mode        = "spherical";
    float       sensitivity = 1.0;
};

struct Settings 
{
    Camera camera;
};

#endif
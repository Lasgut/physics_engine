#ifndef SETTINGS_H
#define SETTINGS_H

#pragma once
#include <string>

struct CameraSettings 
{
    std::string mode        = "spherical";
    float       sensitivity = 0.5;
};

struct Settings 
{
    CameraSettings camera;
};

#endif
#ifndef SETTINGS_H
#define SETTINGS_H

#pragma once
#include <string>

enum class CameraMode
{
    Spherical,
    FirstPerson,
    ThirdPerson
};

struct CameraSettings 
{
    CameraMode mode        = CameraMode::Spherical;
    float      sensitivity = 0.5;
};

struct SimulationSettings 
{
    bool isRunning = false;
};

struct Settings 
{
    public: 
        static Settings& getInstance()
        {
            static Settings instance;
            return instance;
        };

        CameraSettings     camera;
        SimulationSettings simulation;

    private:
        Settings()                           = default;
        ~Settings()                          = default;
        Settings(const Settings&)            = delete;
        Settings& operator=(const Settings&) = delete;
        Settings(Settings&&)                 = delete;
        Settings& operator=(Settings&&)      = delete;
};

#endif